package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class HpCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "hp";
    }

    @Override
    public String getDescription() {
        return "查看气血状态";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        StringBuilder sb = new StringBuilder();
        sb.append("===== 体力状态 =====\n");
        sb.append("气血: ").append(player.getBody()).append("/").append(player.getMaxBody()).append("\n");
        sb.append("精力: ").append(player.getEnergy()).append("/").append(player.getMaxEnergy()).append("\n");
        sb.append("内力: ").append(player.getInternalForce()).append("/").append(player.getMaxInternalForce()).append("\n");
        sb.append("食物: ").append(player.getFood()).append("/").append(player.getMaxFood()).append("\n");
        sb.append("饮水: ").append(player.getDrink()).append("/").append(player.getMaxDrink()).append("\n");
        sb.append("经验: ").append(player.getExperience()).append("\n");
        sb.append("潜能: ").append(player.getPotential()).append("\n");
        sb.append("正气: ").append(player.getGoodnessCount()).append("\n");

        // 气血形容
        long bodyPercent = player.getMaxBody() > 0 ? player.getBody() * 100 / player.getMaxBody() : 0;
        String bodyDesc;
        if (bodyPercent >= 100) bodyDesc = "看上去气血充盈，没有受一点伤。";
        else if (bodyPercent >= 80) bodyDesc = "看上去气血充盈，受了一点小伤。";
        else if (bodyPercent >= 60) bodyDesc = "受了一点轻伤，没有什么关系。";
        else if (bodyPercent >= 40) bodyDesc = "的伤势有些严重了，要好好休息了。";
        else if (bodyPercent >= 20) bodyDesc = "的伤势很严重了，再不休息会死的啊。";
        else bodyDesc = "有如风中之烛，随时都有可能倒下。";
        sb.append("状态: ").append(bodyDesc).append("\n");

        engine.getMessageService().sendToPlayer(player.getId(),
                com.zjjh.mud.game.GameMessage.info(sb.toString()));

        // 同时推送HP更新到前端状态面板
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
