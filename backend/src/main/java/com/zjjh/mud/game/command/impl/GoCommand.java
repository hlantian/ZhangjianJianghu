package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.entity.Room;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.game.engine.PlayerManager;
import com.zjjh.mud.game.engine.RoomManager;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
public class GoCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "go";
    }

    @Override
    public String getDescription() {
        return "前往指定方向 (go east/north/south/west/up/down)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    "你要去哪个方向？");
            return;
        }

        String direction = args.trim().toLowerCase();
        Long currentRoomId = player.getRoomId();
        if (currentRoomId == null) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    "你不在任何房间里。");
            return;
        }

        // 方向别名
        direction = switch (direction) {
            case "north", "n" -> "北";
            case "south", "s" -> "南";
            case "east", "e" -> "东";
            case "west", "w" -> "西";
            case "up", "u" -> "上";
            case "down", "d" -> "下";
            default -> direction;
        };

        RoomManager roomManager = engine.getRoomManager();
        Long targetRoomId = roomManager.moveActorToDirection(currentRoomId, direction);

        if (targetRoomId == null) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    "这个方向没有出路。");
            return;
        }

        // 移动玩家
        PlayerManager playerManager = engine.getPlayerManager();
        playerManager.movePlayerToRoom(player.getId(), targetRoomId);

        // 显示新房间信息
        Room room = roomManager.getRoom(targetRoomId);
        if (room != null) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你来到了" + room.getName() + "。"));
        }

        // 显示房间描述
        String desc = roomManager.getRoomDescription(targetRoomId);
        engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(desc));

        // 显示房间内人物
        var players = playerManager.getOnlinePlayersInRoom(targetRoomId);
        if (players.size() > 1) {
            StringBuilder sb = new StringBuilder("房间里还有：");
            for (var p : players) {
                if (!p.getId().equals(player.getId())) {
                    sb.append(p.getName()).append(" ");
                }
            }
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
        }

        // 显示NPC
        var npcs = roomManager.getRoomNpcs(targetRoomId);
        if (!npcs.isEmpty()) {
            StringBuilder sb = new StringBuilder("这里有：");
            for (var npc : npcs) {
                sb.append(npc.getName()).append(" ");
            }
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
        }
    }
}
