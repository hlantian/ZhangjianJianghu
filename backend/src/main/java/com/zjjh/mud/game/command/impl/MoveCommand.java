package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class MoveCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "move";
    }

    @Override
    public String getDescription() {
        return "在房间内移动 (move x y)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("用法: move x y"));
            return;
        }

        String[] parts = args.trim().split("\\s+");
        if (parts.length < 2) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("用法: move x y"));
            return;
        }

        try {
            int x = Integer.parseInt(parts[0]);
            int y = Integer.parseInt(parts[1]);

            // 检查坐标范围
            Long roomId = player.getRoomId();
            if (roomId != null) {
                var room = engine.getRoomManager().getRoom(roomId);
                if (room != null) {
                    int minX = room.getMinX() != null ? room.getMinX() : 10;
                    int maxX = room.getMaxX() != null ? room.getMaxX() : 365;
                    int minY = room.getMinY() != null ? room.getMinY() : 90;
                    int maxY = room.getMaxY() != null ? room.getMaxY() : 320;

                    if (x < minX || x > maxX || y < minY || y > maxY) {
                        engine.getMessageService().sendToPlayer(player.getId(),
                                GameMessage.error("你不能再往这个方向走了。"));
                        return;
                    }
                }
            }

            player.setPlayerX(x);
            player.setPlayerY(y);

            // 通知房间内所有人
            engine.getMessageService().sendActorMove(
                    player.getRoomId(), player.getName(), x, y);

        } catch (NumberFormatException e) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("坐标必须是数字。"));
        }
    }
}
