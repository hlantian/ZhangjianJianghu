package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class TunaCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "tuna";
    }

    @Override
    public String getDescription() {
        return "吐纳恢复内力";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        long energy = player.getEnergy() != null ? player.getEnergy() : 0;
        long maxEnergy = player.getMaxEnergy() != null ? player.getMaxEnergy() : 100;

        if (energy < 10) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("你太累了，精力不足，无法吐纳。"));
            return;
        }

        long maxForce = player.getMaxInternalForce() != null ? player.getMaxInternalForce() : 0;
        long currentForce = player.getInternalForce() != null ? player.getInternalForce() : 0;

        if (currentForce >= maxForce) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你的内力已经满了。"));
            return;
        }

        // 消耗精力恢复内力
        long recover = Math.max(5, maxForce / 10);
        player.setInternalForce(Math.min(maxForce, currentForce + recover));
        player.setEnergy(energy - 10);
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你深吸一口气，精神好多了，内力恢复了" + recover + "点。"));

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
