package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Npc;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

@Component
public class QuestCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "quest";
    }

    @Override
    public String getDescription() {
        return "申请任务";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        Long roomId = player.getRoomId();
        if (roomId == null) return;

        // 检查是否已有任务
        String questList = player.getQuestList();
        if (questList != null && !questList.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你已经有任务在身了！\n当前任务：" + questList));
            return;
        }

        // 查找可发放任务的NPC
        for (Npc npc : engine.getRoomManager().getRoomNpcs(roomId)) {
            if (npc.getProvideQuest() != null && npc.getProvideQuest() == 1) {
                // 生成任务
                String questType = generateQuestType();
                String target = generateTarget(player);
                long rewardExp = 100 + ThreadLocalRandom.current().nextInt(900);
                long rewardPotential = 50 + ThreadLocalRandom.current().nextInt(450);
                long rewardMoney = 50 + ThreadLocalRandom.current().nextInt(200);

                String questDesc = String.format(
                        "【%s】%s要求你%s。完成后可获得经验%d、潜能%d、银子%d两。",
                        questType, npc.getName(), getQuestDesc(questType, target),
                        rewardExp, rewardPotential, rewardMoney);

                // 保存任务
                player.setQuestList(questDesc + "|" + questType + "|" + target + "|" +
                        rewardExp + "|" + rewardPotential + "|" + rewardMoney);
                engine.getPlayerManager().updateOnlinePlayer(player);

                // NPC说话
                String npcSay = npc.getNpcSayWhenNoQuest();
                if (npcSay != null && !npcSay.isEmpty()) {
                    engine.getMessageService().sendToPlayer(player.getId(),
                            GameMessage.info(npc.getName() + "说：" + npcSay));
                }

                engine.getMessageService().sendToPlayer(player.getId(),
                        GameMessage.info(questDesc));
                return;
            }
        }

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("这里没有可以给你任务的NPC。"));
    }

    private String generateQuestType() {
        String[] types = {"杀敌", "送信", "采集"};
        return types[ThreadLocalRandom.current().nextInt(types.length)];
    }

    private String generateTarget(Player player) {
        String[] targets = {"山贼", "土匪", "恶霸", "强盗", "流寇"};
        return targets[ThreadLocalRandom.current().nextInt(targets.length)];
    }

    private String getQuestDesc(String questType, String target) {
        return switch (questType) {
            case "杀敌" -> "去杀死" + target;
            case "送信" -> "把信送给" + target;
            case "采集" -> "去采集" + target + "的材料";
            default -> "完成" + target + "的任务";
        };
    }
}
