package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class SayCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "say";
    }

    @Override
    public String getDescription() {
        return "在房间内说话 (say 消息)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你总得说点什么吧？");
            return;
        }

        Long roomId = player.getRoomId();
        if (roomId == null) {
            return;
        }

        engine.getChatManager().sayToRoom(player.getId(), player.getName(), roomId, args);
    }
}
