package com.zjjh.mud.game.engine;

import com.zjjh.mud.game.GameMessageService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.context.event.ApplicationReadyEvent;
import org.springframework.context.event.EventListener;
import org.springframework.stereotype.Component;

@Slf4j
@Component
@RequiredArgsConstructor
public class GameEngine {

    private final PlayerManager playerManager;
    private final RoomManager roomManager;
    private final ChatManager chatManager;
    private final GameMessageService messageService;

    private volatile boolean running = false;

    @EventListener(ApplicationReadyEvent.class)
    public void start() {
        log.info("========== 仗剑江湖游戏引擎启动 ==========");
        running = true;
        chatManager.systemMessage("仗剑江湖游戏服务器已启动。");
        log.info("游戏引擎启动完成");
    }

    public void shutdown() {
        log.info("========== 仗剑江湖游戏引擎关闭 ==========");
        running = false;

        // 保存所有在线玩家数据
        for (var player : playerManager.getAllOnlinePlayers()) {
            try {
                playerManager.playerOffline(player.getId());
            } catch (Exception e) {
                log.error("玩家离线保存失败: {}", player.getName(), e);
            }
        }

        chatManager.systemMessage("仗剑江湖游戏服务器即将关闭。");
        log.info("游戏引擎已关闭");
    }

    public boolean isRunning() {
        return running;
    }

    public PlayerManager getPlayerManager() {
        return playerManager;
    }

    public RoomManager getRoomManager() {
        return roomManager;
    }

    public ChatManager getChatManager() {
        return chatManager;
    }

    public GameMessageService getMessageService() {
        return messageService;
    }
}
