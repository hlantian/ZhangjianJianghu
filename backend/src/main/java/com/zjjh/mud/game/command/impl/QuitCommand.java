package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class QuitCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "quit";
    }

    @Override
    public String getDescription() {
        return "退出游戏";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        // 通知房间内玩家
        Long roomId = player.getRoomId();
        if (roomId != null) {
            engine.getMessageService().sendToRoom(roomId,
                    GameMessage.info(player.getName() + " 离开了游戏。"));
        }

        // 玩家离线处理
        engine.getPlayerManager().playerOffline(player.getId());

        // 通知玩家
        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你已退出仗剑江湖，欢迎下次再来！"));
    }
}
