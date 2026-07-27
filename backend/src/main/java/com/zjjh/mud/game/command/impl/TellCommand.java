package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class TellCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "tell";
    }

    @Override
    public String getDescription() {
        return "密谈 (tell <名字> <消息>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要和谁密谈？");
            return;
        }

        String[] parts = args.trim().split("\\s+", 2);
        if (parts.length < 2) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要说什么？");
            return;
        }

        String targetName = parts[0];
        String message = parts[1];

        // 查找在线玩家
        for (Player target : engine.getPlayerManager().getAllOnlinePlayers()) {
            if (target.getName().equals(targetName) || target.getName().contains(targetName)) {
                engine.getChatManager().tellToPlayer(
                        player.getId(), player.getName(),
                        target.getId(), target.getName(), message);
                return;
            }
        }

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.error(targetName + " 不在线。"));
    }
}
