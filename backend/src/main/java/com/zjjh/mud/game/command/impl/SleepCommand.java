package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class SleepCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "sleep";
    }

    @Override
    public String getDescription() {
        return "睡觉恢复";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        long currentEnergy = player.getEnergy() != null ? player.getEnergy() : 0;
        long maxEnergy = player.getMaxEnergy() != null ? player.getMaxEnergy() : 100;

        if (currentEnergy < maxEnergy * 0.2) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你太累了，倒头便睡。"));
        } else {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你现在精神还好，不需要睡觉。"));
            return;
        }

        // 恢复气血和精力
        player.setBody(player.getMaxBody());
        player.setEnergy(player.getMaxEnergy());
        player.setInternalForce(player.getMaxInternalForce());
        player.setSleepTime(System.currentTimeMillis());
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你睡了一觉，精神焕发，气血充盈。"));

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
