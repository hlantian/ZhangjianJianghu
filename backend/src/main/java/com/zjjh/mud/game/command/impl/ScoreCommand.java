package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class ScoreCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "score";
    }

    @Override
    public String getDescription() {
        return "查看人物状态";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        StringBuilder sb = new StringBuilder();
        sb.append("===== 人物状态 =====\n");
        sb.append("姓名: ").append(player.getName());
        if (player.getNick() != null && !player.getNick().isEmpty()) {
            sb.append(" ").append(player.getNick());
        }
        if (player.getTitle() != null && !player.getTitle().isEmpty()) {
            sb.append(" ").append(player.getTitle());
        }
        sb.append("\n");

        sb.append("性别: ").append("m".equals(player.getSex()) ? "男" : "女").append("\n");
        sb.append("年龄: ").append(player.getAge()).append("\n");
        sb.append("门派: ").append(player.getSchool() != null ? player.getSchool() : "无").append("\n");
        sb.append("师父: ").append(player.getTeacherName() != null && !player.getTeacherName().isEmpty() ? player.getTeacherName() : "无").append("\n");
        sb.append("\n");

        sb.append("【先天属性】\n");
        sb.append("臂力: ").append(player.getBeginArm()).append("  ");
        sb.append("悟性: ").append(player.getBeginLearn()).append("  ");
        sb.append("根骨: ").append(player.getBeginForce()).append("  ");
        sb.append("身法: ").append(player.getBeginDodge()).append("\n");

        sb.append("【后天属性】\n");
        sb.append("臂力: ").append(player.getLastArm()).append("  ");
        sb.append("悟性: ").append(player.getLastLearn()).append("  ");
        sb.append("根骨: ").append(player.getLastForce()).append("  ");
        sb.append("身法: ").append(player.getLastDodge()).append("\n");
        sb.append("\n");

        sb.append("【战斗属性】\n");
        sb.append("攻击力: ").append(player.getInhereAttack() + player.getWeaponAttack() + player.getAppendAttack() + player.getPowerupAttack()).append("\n");
        sb.append("防御力: ").append(player.getInhereDefense() + player.getAppendDefense() + player.getPowerupDefense()).append("\n");
        sb.append("逃跑系数: ").append(player.getWimpy()).append("%\n");
        sb.append("\n");

        sb.append("【容貌福缘】\n");
        sb.append("容貌: ").append(player.getFeature() + player.getAddFeature()).append("\n");
        sb.append("福缘: ").append(player.getLuck() + player.getAddLuck()).append("\n");
        sb.append("\n");

        sb.append("【声望】\n");
        sb.append("门派评价: ").append(player.getPartyValue()).append("\n");
        sb.append("朝廷声望: ").append(player.getCourtValue()).append("\n");
        sb.append("江湖声望: ").append(player.getSocietyValue()).append("\n");
        sb.append("\n");

        sb.append("【金钱】\n");
        sb.append("存款: ").append(player.getDeposit()).append(" 两白银\n");
        sb.append("\n");

        sb.append("【击杀统计】\n");
        sb.append("杀人: ").append(player.getKillTimes()).append("  ");
        sb.append("被杀: ").append(player.getBeKillTimes()).append("\n");
        sb.append("PK: ").append(player.getPkTimes()).append("  ");
        sb.append("被PK: ").append(player.getBePkTimes()).append("\n");

        // 装备
        sb.append("\n【装备】\n");
        sb.append("武器: ").append(player.getWeaponName() != null && !player.getWeaponName().isEmpty() ? player.getWeaponName() : "无").append("\n");
        sb.append("衣服: ").append(player.getClothName() != null && !player.getClothName().isEmpty() ? player.getClothName() : "无").append("\n");
        sb.append("盔甲: ").append(player.getArmor() != null && !player.getArmor().isEmpty() ? player.getArmor() : "无").append("\n");
        sb.append("帽子: ").append(player.getHat() != null && !player.getHat().isEmpty() ? player.getHat() : "无").append("\n");
        sb.append("鞋子: ").append(player.getShoe() != null && !player.getShoe().isEmpty() ? player.getShoe() : "无").append("\n");

        engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
    }
}
