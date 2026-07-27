package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class WhoCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "who";
    }

    @Override
    public String getDescription() {
        return "查看在线玩家列表";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        var onlinePlayers = engine.getPlayerManager().getAllOnlinePlayers();
        StringBuilder sb = new StringBuilder();
        sb.append("===== 在线玩家 =====\n");
        sb.append("当前在线: ").append(onlinePlayers.size()).append(" 人\n\n");

        for (var p : onlinePlayers) {
            sb.append("  ").append(p.getName());
            if (p.getTitle() != null && !p.getTitle().isEmpty()) {
                sb.append(" ").append(p.getTitle());
            }
            if (p.getSchool() != null && !p.getSchool().isEmpty()) {
                sb.append(" [").append(p.getSchool()).append("]");
            }
            sb.append("\n");
        }

        engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
    }
}
