package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Npc;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.entity.Room;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class LookCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "look";
    }

    @Override
    public String getDescription() {
        return "查看周围环境或指定目标 (look [目标])";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        Long roomId = player.getRoomId();
        if (roomId == null) {
            engine.getMessageService().sendToPlayer(player.getId(), "你不在任何地方。");
            return;
        }

        if (args == null || args.isEmpty()) {
            // 查看房间
            String desc = engine.getRoomManager().getRoomDescription(roomId);
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(desc));

            // 显示房间内玩家
            var players = engine.getPlayerManager().getOnlinePlayersInRoom(roomId);
            if (players.size() > 1) {
                StringBuilder sb = new StringBuilder("房间里还有：\n");
                for (var p : players) {
                    if (!p.getId().equals(player.getId())) {
                        sb.append("  ").append(p.getName());
                        if (p.getStatus() != null && !p.getStatus().isEmpty()) {
                            sb.append(" ").append(p.getStatus());
                        }
                        sb.append("\n");
                    }
                }
                engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
            }

            // 显示NPC
            List<Npc> npcs = engine.getRoomManager().getRoomNpcs(roomId);
            if (!npcs.isEmpty()) {
                StringBuilder sb = new StringBuilder("这里有：\n");
                for (var npc : npcs) {
                    sb.append("  ").append(npc.getName());
                    if (npc.getTitle() != null && !npc.getTitle().isEmpty()) {
                        sb.append(" ").append(npc.getTitle());
                    }
                    sb.append("\n");
                    // 直接发送NPC头像到玩家画布
                    GameMessage npcMsg = new GameMessage(GameMessage.MessageType.ACTOR_ENTER, null);
                    npcMsg.setActorName(npc.getName());
                    npcMsg.setActorDisplayName(npc.getName());
                    npcMsg.setX(100 + npcs.indexOf(npc) * 50);
                    npcMsg.setY(150);
                    engine.getMessageService().sendToPlayer(player.getId(), npcMsg);
                }
                engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
            }

            // 发送玩家自己的头像到画布
            GameMessage selfMsg = new GameMessage(GameMessage.MessageType.ACTOR_ENTER, null);
            selfMsg.setActorName(player.getName());
            selfMsg.setActorDisplayName(player.getName() + "(你)");
            selfMsg.setX(player.getPlayerX());
            selfMsg.setY(player.getPlayerY());
            engine.getMessageService().sendToPlayer(player.getId(), selfMsg);

            // 发送房间内其他玩家头像到画布
            for (var p : players) {
                if (!p.getId().equals(player.getId())) {
                    GameMessage pMsg = new GameMessage(GameMessage.MessageType.ACTOR_ENTER, null);
                    pMsg.setActorName(p.getName());
                    pMsg.setActorDisplayName(p.getName());
                    pMsg.setX(p.getPlayerX());
                    pMsg.setY(p.getPlayerY());
                    engine.getMessageService().sendToPlayer(player.getId(), pMsg);
                }
            }
        } else {
            // 查看指定目标(NPC或玩家)
            String targetName = args.trim();

            // 查找NPC
            Npc npc = engine.getRoomManager().getNpcByName(roomId, targetName);
            if (npc != null) {
                StringBuilder sb = new StringBuilder();
                sb.append(npc.getName());
                if (npc.getTitle() != null && !npc.getTitle().isEmpty()) {
                    sb.append(" ").append(npc.getTitle());
                }
                sb.append("\n");
                if (npc.getNpcShow() != null && !npc.getNpcShow().isEmpty()) {
                    sb.append(npc.getNpcShow());
                }
                engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
                return;
            }

            // 查找玩家
            for (var p : engine.getPlayerManager().getOnlinePlayersInRoom(roomId)) {
                if (p.getName().contains(targetName)) {
                    StringBuilder sb = new StringBuilder();
                    sb.append(p.getName());
                    if (p.getNick() != null && !p.getNick().isEmpty()) {
                        sb.append(" ").append(p.getNick());
                    }
                    sb.append("\n");
                    if (p.getDescribe() != null && !p.getDescribe().isEmpty()) {
                        sb.append(p.getDescribe());
                    }
                    engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
                    return;
                }
            }

            engine.getMessageService().sendToPlayer(player.getId(),
                    "这里没有 " + targetName + "。");
        }
    }
}
