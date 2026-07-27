package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class NickCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "nick";
    }

    @Override
    public String getDescription() {
        return "设置绰号 (nick <绰号>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            // 清除绰号
            player.setNick("");
            engine.getPlayerManager().updateOnlinePlayer(player);
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你清除了绰号。"));
            return;
        }

        String nick = args.trim();
        if (nick.length() > 20) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("绰号太长了。"));
            return;
        }

        player.setNick(nick);
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你设置了绰号：" + nick + "。"));
    }
}
