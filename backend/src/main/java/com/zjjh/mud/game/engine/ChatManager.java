package com.zjjh.mud.game.engine;

import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.GameMessageService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Component;

import java.util.*;

@Slf4j
@Component
@RequiredArgsConstructor
public class ChatManager {

    private final GameMessageService messageService;
    private final RedisTemplate<String, Object> redisTemplate;
    private final PlayerManager playerManager;

    // 聊天频道
    public static final String CHANNEL_SAY = "say";       // 房间内说话
    public static final String CHANNEL_CHAT = "chat";     // 公共频道
    public static final String CHANNEL_RUMOR = "rumor";    // 谣言频道
    public static final String CHANNEL_NEWBIE = "newbie";  // 新手频道
    public static final String CHANNEL_PARTY = "party";   // 门派频道
    public static final String CHANNEL_FACTION = "faction"; // 帮派频道
    public static final String CHANNEL_WIZ = "wiz";        // 巫师频道
    public static final String CHANNEL_SYSTEM = "system";  // 系统频道
    public static final String CHANNEL_TELL = "tell";      // 密谈

    // 频道颜色
    private static final Map<String, String> channelColors = new HashMap<>();
    static {
        channelColors.put(CHANNEL_CHAT, "#0000ee");
        channelColors.put(CHANNEL_NEWBIE, "#999999");
        channelColors.put(CHANNEL_RUMOR, "green");
        channelColors.put(CHANNEL_PARTY, "#ee9a49");
        channelColors.put(CHANNEL_FACTION, "#ee9a49");
        channelColors.put(CHANNEL_WIZ, "red");
    }

    /**
     * 房间内说话
     */
    public void sayToRoom(Long playerId, String playerName, Long roomId, String message) {
        // 发送给房间内所有人
        messageService.sendActorSay(roomId, playerName, message);

        // 也发送给自己
        messageService.sendToPlayer(playerId, GameMessage.info(
                "你说道：" + message));
    }

    /**
     * 公共频道发言
     */
    public void chatOnChannel(Long playerId, String playerName, String channel, String message) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.CHAT, message);
        msg.setActorName(playerName);
        messageService.sendToChatChannel(channel, msg);

        // 同时发送给自己
        String color = channelColors.getOrDefault(channel, "#000000");
        messageService.sendToPlayer(playerId, GameMessage.info(
                String.format("【%s】%s：%s", channel, playerName, message)));
    }

    /**
     * 密谈
     */
    public boolean tellToPlayer(Long fromPlayerId, String fromName, Long toPlayerId, String toName, String message) {
        if (!playerManager.isOnline(toPlayerId)) {
            messageService.sendToPlayer(fromPlayerId, GameMessage.error(toName + " 不在线。"));
            return false;
        }

        // 发送给对方
        messageService.sendToPlayer(toPlayerId, GameMessage.info(
                fromName + " 密语你：" + message));

        // 发送给自己确认
        messageService.sendToPlayer(fromPlayerId, GameMessage.info(
                "你密语 " + toName + "：" + message));

        return true;
    }

    /**
     * 系统消息
     */
    public void systemMessage(String message) {
        messageService.sendSystemBroadcast(message);
    }

    /**
     * 门派频道发言
     */
    public void partyChat(Long playerId, String playerName, String school, String message) {
        if (school == null || school.isEmpty()) {
            messageService.sendToPlayer(playerId, GameMessage.error("你没有加入任何门派。"));
            return;
        }

        // 发送给同门派的所有在线玩家
        for (var player : playerManager.getAllOnlinePlayers()) {
            if (school.equals(player.getSchool())) {
                messageService.sendToPlayer(player.getId(), GameMessage.info(
                        String.format("【门派】%s：%s", playerName, message)));
            }
        }
    }

    /**
     * 帮派频道发言
     */
    public void factionChat(Long playerId, String playerName, Long factionId, String factionName, String message) {
        if (factionId == null) {
            messageService.sendToPlayer(playerId, GameMessage.error("你没有加入任何帮派。"));
            return;
        }

        // 发送给同帮派的所有在线玩家
        for (var player : playerManager.getAllOnlinePlayers()) {
            if (factionId.equals(player.getFactionId())) {
                messageService.sendToPlayer(player.getId(), GameMessage.info(
                        String.format("【%s】%s：%s", factionName, playerName, message)));
            }
        }
    }
}
