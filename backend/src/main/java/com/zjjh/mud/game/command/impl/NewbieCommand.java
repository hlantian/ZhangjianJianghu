package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.ChatManager;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class NewbieCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "newbie";
    }

    @Override
    public String getDescription() {
        return "新手频道发言 (newbie 消息)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (player.getCloseNewbie() != null && player.getCloseNewbie() == 1) {
            engine.getMessageService().sendToPlayer(player.getId(), "你的新手频道是关闭的。");
            return;
        }
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你总得说点什么吧？");
            return;
        }
        engine.getChatManager().chatOnChannel(
                player.getId(), player.getName(),
                ChatManager.CHANNEL_NEWBIE, args);
    }
}
