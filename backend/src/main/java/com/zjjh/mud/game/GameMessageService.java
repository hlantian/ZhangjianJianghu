package com.zjjh.mud.game;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;

@Slf4j
@Service
@RequiredArgsConstructor
public class GameMessageService {

    private final SimpMessagingTemplate messagingTemplate;

    private static final String PLAYER_QUEUE = "/queue/messages";
    private static final String ROOM_TOPIC = "/topic/room/";
    private static final String CHAT_TOPIC = "/topic/chat/";
    private static final String SYSTEM_TOPIC = "/topic/system";

    /**
     * 向指定玩家推送消息
     */
    public void sendToPlayer(Long playerId, GameMessage message) {
        messagingTemplate.convertAndSendToUser(
                String.valueOf(playerId),
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
