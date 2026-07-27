package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class PartyCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "party";
    }

    @Override
    public String getDescription() {
        return "门派频道发言 (party 消息)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (player.getCloseParty() != null && player.getCloseParty() == 1) {
            engine.getMessageService().sendToPlayer(player.getId(), "你的门派频道是关闭的。");
            return;
        }
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你总得说点什么吧？");
            return;
        }
        String school = player.getSchool();
        if (school == null || school.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你没有加入任何门派。");
            return;
        }
        engine.getChatManager().partyChat(
                player.getId(), player.getName(), school, args);
    }
}
