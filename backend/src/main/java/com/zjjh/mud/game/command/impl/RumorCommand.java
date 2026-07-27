package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.ChatManager;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class RumorCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "rumor";
    }

    @Override
    public String getDescription() {
        return "在谣言频道发言 (rumor 消息)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (player.getCloseRumor() != null && player.getCloseRumor() == 1) {
            engine.getMessageService().sendToPlayer(player.getId(), "你的谣言频道是关闭的。");
            return;
        }
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你总得说点什么吧？");
            return;
        }
        engine.getChatManager().chatOnChannel(
                player.getId(), player.getName(),
                ChatManager.CHANNEL_RUMOR, args);
    }
}
