package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class DazuoCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "dazuo";
    }

    @Override
    public String getDescription() {
        return "打坐恢复气血";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        long energy = player.getEnergy() != null ? player.getEnergy() : 0;

        if (energy < 10) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("你太累了，精力不足，无法打坐。"));
            return;
        }

        long maxBody = player.getMaxBody() != null ? player.getMaxBody() : 100;
        long currentBody = player.getBody() != null ? player.getBody() : 0;

        if (currentBody >= maxBody) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你的气血已经充盈了。"));
            return;
        }

        // 消耗精力恢复气血
        long recover = Math.max(5, maxBody / 10);
        player.setBody(Math.min(maxBody, currentBody + recover));
        player.setEnergy(energy - 10);
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你盘膝而坐，运功疗伤，气血恢复了" + recover + "点。"));

        engine.getMessageService().sendHpUpdate(
                player.getId(),
                player.getBody(), player.getMaxBody(),
                player.getEnergy(), player.getMaxEnergy(),
                player.getInternalForce(), player.getMaxInternalForce(),
                player.getFood(), player.getMaxFood(),
                player.getDrink(), player.getMaxDrink()
        );
    }
}
