package com.zjjh.mud.websocket;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandRouter;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.service.AuthService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.context.event.EventListener;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.Payload;
import org.springframework.messaging.simp.stomp.StompHeaderAccessor;
import org.springframework.messaging.simp.annotation.SubscribeMapping;
import org.springframework.stereotype.Controller;
import org.springframework.boot.context.event.ApplicationReadyEvent;

import java.security.Principal;
import java.util.Map;

@Slf4j
@Controller
@RequiredArgsConstructor
public class GameWebSocketController {

    private final GameEngine gameEngine;
    private final CommandRouter commandRouter;
    private final AuthService authService;

    @EventListener(ApplicationReadyEvent.class)
    public void init() {
        commandRouter.init();
    }

    /**
     * 处理玩家命令
     */
    @MessageMapping("/command")
    public void handleCommand(@Payload Map<String, String> payload, StompHeaderAccessor accessor) {
        String command = payload.get("command");
        if (command == null || command.trim().isEmpty()) {
            return;
        }

        Principal principal = accessor.getUser();
        if (principal == null || !(principal instanceof StompPrincipal stompPrincipal)) {
            log.warn("收到命令但未认证: {}", command);
            return;
        }

        Long userId = stompPrincipal.getUserId();
        Player player = authService.getPlayerByUserId(userId);
        if (player == null) {
            log.warn("收到命令但未找到玩家: userId={}", userId);
            return;
        }

        // 如果玩家未上线，先上线
        if (!gameEngine.getPlayerManager().isOnline(player.getId())) {
            gameEngine.getPlayerManager().playerOnline(player.getId());
        }

        // 更新在线玩家数据
        Player onlinePlayer = gameEngine.getPlayerManager().getOnlinePlayer(player.getId());
        if (onlinePlayer == null) {
            onlinePlayer = player;
            gameEngine.getPlayerManager().updateOnlinePlayer(onlinePlayer);
        }

        log.debug("处理命令: player={}, cmd={}", onlinePlayer.getName(), command);
        commandRouter.processCommand(gameEngine, onlinePlayer, command);

        // 更新玩家数据(命令可能修改了属性)
        gameEngine.getPlayerManager().updateOnlinePlayer(onlinePlayer);
    }

    /**
     * 玩家订阅房间频道
     */
    @MessageMapping("/subscribe/room")
    public void subscribeRoom(@Payload Map<String, Object> payload, StompHeaderAccessor accessor) {
        Principal principal = accessor.getUser();
        if (principal instanceof StompPrincipal stompPrincipal) {
            Player player = authService.getPlayerByUserId(stompPrincipal.getUserId());
            if (player != null && player.getRoomId() != null) {
                // 发送当前房间信息
                String desc = gameEngine.getRoomManager().getRoomDescription(player.getRoomId());
                gameEngine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(desc));

                // 发送房间内人物
                for (var p : gameEngine.getPlayerManager().getOnlinePlayersInRoom(player.getRoomId())) {
                    if (!p.getId().equals(player.getId())) {
                        gameEngine.getMessageService().sendActorEnter(
                                player.getRoomId(), p.getName(), p.getName(),
                                p.getPlayerX(), p.getPlayerY());
                    }
                }
            }
        }
    }
}
