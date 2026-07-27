package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Npc;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class BaiCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "bai";
    }

    @Override
    public String getDescription() {
        return "拜师 (bai <师父名>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要拜谁为师？");
            return;
        }

        String targetName = args.trim();
        Long roomId = player.getRoomId();
        if (roomId == null) return;

        Npc npc = engine.getRoomManager().getNpcByName(roomId, targetName);
        if (npc == null) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("这里没有 " + targetName + "。"));
            return;
        }

        if (npc.getAllowPrentice() == null || npc.getAllowPrentice() != 1) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info(npc.getName() + " 不收徒弟。"));
            return;
        }

        // 已有师父
        if (player.getTeacherName() != null && !player.getTeacherName().isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("你已经拜过师了。"));
            return;
        }

        // 拜师成功
        player.setTeacherName(npc.getName());
        player.setSchool(npc.getSchool());
        engine.getPlayerManager().updateOnlinePlayer(player);

        String answer = npc.getAnswerForAgreePrentice();
        if (answer != null && !answer.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info(npc.getName() + "说：" + answer));
        } else {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info(npc.getName() + "收你为徒了。"));
        }

        engine.getMessageService().sendToRoom(roomId,
                GameMessage.info(player.getName() + "拜" + npc.getName() + "为师了。"));
    }
}
