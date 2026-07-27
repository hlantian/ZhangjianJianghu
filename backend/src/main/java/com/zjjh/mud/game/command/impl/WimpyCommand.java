package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class WimpyCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "wimpy";
    }

    @Override
    public String getDescription() {
        return "设置逃跑系数 (wimpy <0-100>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("当前逃跑系数: " + player.getWimpy() + "%"));
            return;
        }

        try {
            int wimpy = Integer.parseInt(args.trim());
            if (wimpy < 0 || wimpy > 100) {
                engine.getMessageService().sendToPlayer(player.getId(),
                        GameMessage.error("逃跑系数必须在0到100之间。"));
                return;
            }
            player.setWimpy((long) wimpy);
            engine.getPlayerManager().updateOnlinePlayer(player);
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你将逃跑系数设置为 " + wimpy + "%。"));
        } catch (NumberFormatException e) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("请输入0到100的数字。"));
        }
    }
}
