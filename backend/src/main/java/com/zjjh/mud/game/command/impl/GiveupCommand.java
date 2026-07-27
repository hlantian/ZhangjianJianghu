package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class GiveupCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "giveup";
    }

    @Override
    public String getDescription() {
        return "放弃当前任务";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        String questList = player.getQuestList();
        if (questList == null || questList.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你目前没有任务。"));
            return;
        }

        player.setQuestList("");
        player.setExperience(Math.max(0, (player.getExperience() != null ? player.getExperience() : 0) - 50));
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你放弃了当前任务，损失了50点经验。"));
    }
}
