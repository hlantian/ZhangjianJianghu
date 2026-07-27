package com.zjjh.mud.game.command.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.entity.Wugong;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.combat.CombatMessageService;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.mapper.WugongMapper;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
@RequiredArgsConstructor
public class SkillsCommand implements CommandHandler {

    private final WugongMapper wugongMapper;
    private final CombatMessageService combatMessageService;

    @Override
    public String getCommandName() {
        return "skills";
    }

    @Override
    public String getDescription() {
        return "查看武功列表";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        String allSkills = player.getAllSkillsList();
        if (allSkills == null || allSkills.trim().isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你还没有学会任何武功。"));
            return;
        }

        StringBuilder sb = new StringBuilder();
        sb.append("===== 武功列表 =====\n\n");

        // 基本武功
        sb.append("【基本武功】\n");
        sb.append("  基本拳法: ").append(getSkillLevel(player, "base_hand")).append("级\n");
        sb.append("  基本指法: ").append(getSkillLevel(player, "base_finger")).append("级\n");
        sb.append("  基本掌法: ").append(getSkillLevel(player, "base_sole")).append("级\n");
        sb.append("  基本腿法: ").append(getSkillLevel(player, "base_leg")).append("级\n");
        sb.append("  基本手法: ").append(getSkillLevel(player, "base_pub")).append("级\n");
        sb.append("  基本爪法: ").append(getSkillLevel(player, "base_clow")).append("级\n");
        sb.append("  基本轻功: ").append(getSkillLevel(player, "base_dodge")).append("级\n");
        sb.append("  基本内功: ").append(getSkillLevel(player, "base_force")).append("级\n");
        sb.append("  基本招架: ").append(getSkillLevel(player, "base_parry")).append("级\n");
        sb.append("  读书写字: ").append(getSkillLevel(player, "learn")).append("级\n");
        sb.append("\n");

        // 特殊武功
        sb.append("【特殊武功】\n");
        String[] skillNames = allSkills.trim().split("\\s+");
        boolean hasSpecial = false;
        for (String skillName : skillNames) {
            if (skillName.isEmpty()) continue;
            LambdaQueryWrapper<Wugong> wrapper = new LambdaQueryWrapper<>();
            wrapper.eq(Wugong::getName, skillName).last("LIMIT 1");
            Wugong w = wugongMapper.selectOne(wrapper);
            if (w != null) {
                int level = getSkillLevelFromList(allSkills, skillName);
                String levelDesc = combatMessageService.getWugongLevelDesc(level / 10);
                sb.append("  ").append(w.getName());
                sb.append(" [").append(w.getMenpai() != null ? w.getMenpai() : "").append("]");
                sb.append(" [").append(w.getLeixing() != null ? w.getLeixing() : "").append("]");
                sb.append(" 等级:").append(level);
                sb.append(" ").append(levelDesc);
                sb.append("\n");
                hasSpecial = true;
            }
        }
        if (!hasSpecial) {
            sb.append("  无\n");
        }

        // 当前启用的武功
        sb.append("\n【当前使用】\n");
        sb.append("  攻击: ").append(player.getWeaponType() != null && !player.getWeaponType().isEmpty() ? player.getWeaponType() : "空手").append("\n");
        sb.append("  内功: ").append("未启用").append("\n");
        sb.append("  轻功: ").append("未启用").append("\n");
        sb.append("  招架: ").append("未启用").append("\n");

        engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
    }

    private long getSkillLevel(Player player, String skillType) {
        // 简化: 从allSkillsList中查找
        return 0; // 后续从base_skills表获取
    }

    private int getSkillLevelFromList(String allSkills, String skillName) {
        // 简化: 返回固定值
        return 10;
    }
}
