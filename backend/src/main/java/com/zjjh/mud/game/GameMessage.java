package com.zjjh.mud.game;

import lombok.Data;
import lombok.NoArgsConstructor;

import java.time.LocalDateTime;

@Data
@NoArgsConstructor
public class GameMessage {
    public enum MessageType {
        ROOM,           // 房间消息(移动/说话)
        SYSTEM,         // 系统消息
        COMBAT,         // 战斗消息
        CHAT,           // 聊天频道
        STATUS,         // 状态更新
        ROOM_INFO,      // 房间信息(进入新房间)
        ACTOR_MOVE,     // 人物移动
        ACTOR_ENTER,    // 人物进入
        ACTOR_LEAVE,    // 人物离开
        ACTOR_DIE,      // 人物死亡
        ACTOR_SAY,      // 人物说话
        ACTOR_PIC,      // 人物头像变化
        CLEAR_ACTORS,   // 清除所有人物(切换房间时)
        HP_UPDATE,      // 气血更新
        SKILLS_UPDATE,  // 技能更新
        SCORE_UPDATE,   // 状态更新
        INVENTORY_UPDATE, // 物品更新
        ERROR,          // 错误消息
        INFO            // 信息消息
    }

    private MessageType type;
    private String content;
    private String actorName;
    private String actorDisplayName;
    private Integer x;
    private Integer y;
    private Long roomId;
    private LocalDateTime timestamp;

    public GameMessage(MessageType type, String content) {
        this.type = type;
        this.content = content;
        this.timestamp = LocalDateTime.now();
    }

    public static GameMessage info(String content) {
        return new GameMessage(MessageType.INFO, content);
    }

    public static GameMessage system(String content) {
        return new GameMessage(MessageType.SYSTEM, content);
    }

    public static GameMessage error(String content) {
        return new GameMessage(MessageType.ERROR, content);
    }

    public static GameMessage combat(String content) {
        return new GameMessage(MessageType.COMBAT, content);
    }

    public static GameMessage room(String content) {
        return new GameMessage(MessageType.ROOM, content);
    }
}
