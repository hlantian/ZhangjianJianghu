package com.zjjh.mud.game;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.engine.PlayerManager;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;

@Slf4j
@Service
public class GameMessageService {

    private final SimpMessagingTemplate messagingTemplate;
    private final PlayerManager playerManager;

    @Autowired
    public GameMessageService(SimpMessagingTemplate messagingTemplate,
                               @Lazy PlayerManager playerManager) {
        this.messagingTemplate = messagingTemplate;
        this.playerManager = playerManager;
    }

    private static final String PLAYER_QUEUE = "/queue/messages";
    private static final String ROOM_TOPIC = "/topic/room/";
    private static final String CHAT_TOPIC = "/topic/chat/";
    private static final String SYSTEM_TOPIC = "/topic/system";

    /**
     * 向指定玩家推送消息
     * 注意: WebSocket会话用userId标识用户(StompPrincipal.getName()=userId)
     * 所以此处需将playerId转换为userId
     */
    public void sendToPlayer(Long playerId, GameMessage message) {
        Player player = playerManager.getOnlinePlayer(playerId);
        Long userId = (player != null && player.getUserId() != null) ? player.getUserId() : playerId;
        log.info("[推送->玩家] playerId={}, userId={}, type={}, content={}",
                playerId, userId, message.getType(),
                message.getContent() != null ? (message.getContent().length() > 100 ? message.getContent().substring(0,100)+"..." : message.getContent()) : "null");
        messagingTemplate.convertAndSendToUser(
                String.valueOf(userId),
                PLAYER_QUEUE,
                message
        );
    }

    /**
     * 向指定玩家推送文本消息
     */
    public void sendToPlayer(Long playerId, String content) {
        sendToPlayer(playerId, GameMessage.info(content));
    }

    /**
     * 向房间内所有玩家广播消息
     */
    public void sendToRoom(Long roomId, GameMessage message) {
        log.info("[广播->房间{}] type={}, content={}",
                roomId, message.getType(),
                message.getContent() != null ? (message.getContent().length() > 100 ? message.getContent().substring(0,100)+"..." : message.getContent()) : "null");
        messagingTemplate.convertAndSend(ROOM_TOPIC + roomId, message);
    }

    /**
     * 向房间内所有玩家广播文本消息
     */
    public void sendToRoom(Long roomId, String content) {
        sendToRoom(roomId, GameMessage.room(content));
    }

    /**
     * 向聊天频道广播消息
     */
    public void sendToChatChannel(String channel, GameMessage message) {
        log.info("[广播->频道{}] sender={}, content={}",
                channel, message.getActorName(), message.getContent());
        messagingTemplate.convertAndSend(CHAT_TOPIC + channel, message);
    }

    /**
     * 系统广播
     */
    public void sendSystemBroadcast(String content) {
        messagingTemplate.convertAndSend(SYSTEM_TOPIC, GameMessage.system(content));
    }

    /**
     * 向房间推送人物移动
     */
    public void sendActorMove(Long roomId, String actorName, int x, int y) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.ACTOR_MOVE, null);
        msg.setActorName(actorName);
        msg.setX(x);
        msg.setY(y);
        sendToRoom(roomId, msg);
    }

    /**
     * 向房间推送人物进入
     */
    public void sendActorEnter(Long roomId, String actorName, String displayName, int x, int y) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.ACTOR_ENTER, null);
        msg.setActorName(actorName);
        msg.setActorDisplayName(displayName);
        msg.setX(x);
        msg.setY(y);
        sendToRoom(roomId, msg);
    }

    /**
     * 向房间推送人物离开
     */
    public void sendActorLeave(Long roomId, String actorName) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.ACTOR_LEAVE, null);
        msg.setActorName(actorName);
        sendToRoom(roomId, msg);
    }

    /**
     * 向房间推送人物说话
     */
    public void sendActorSay(Long roomId, String actorName, String content) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.ACTOR_SAY, content);
        msg.setActorName(actorName);
        sendToRoom(roomId, msg);
    }

    /**
     * 向房间推送人物死亡
     */
    public void sendActorDie(Long roomId, String actorName) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.ACTOR_DIE, null);
        msg.setActorName(actorName);
        sendToRoom(roomId, msg);
    }

    /**
     * 向玩家推送气血更新
     */
    public void sendHpUpdate(Long playerId, long body, long maxBody, long energy, long maxEnergy,
                              long internalForce, long maxInternalForce, long food, long maxFood,
                              long drink, long maxDrink) {
        GameMessage msg = new GameMessage(GameMessage.MessageType.HP_UPDATE, null);
        msg.setContent(String.format("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                body, maxBody, energy, maxEnergy,
                internalForce, maxInternalForce, food, maxFood, drink, maxDrink));
        sendToPlayer(playerId, msg);
    }
}
