package com.zjjh.mud.game.command.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.entity.Wugong;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.mapper.WugongMapper;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
public class LianCommand implements CommandHandler {

    private final WugongMapper wugongMapper;

    @Override
    public String getCommandName() {
        return "lian";
    }

    @Override
    public String getDescription() {
        return "练习武功 (lian <武功名>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要练习什么武功？");
            return;
        }

        String wugongName = args.trim();
        LambdaQueryWrapper<Wugong> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Wugong::getName, wugongName).last("LIMIT 1");
        Wugong wugong = wugongMapper.selectOne(wrapper);

        if (wugong == null) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("没有这个武功。"));
            return;
        }

        // 检查精力
        long energy = player.getEnergy() != null ? player.getEnergy() : 0;
        long jingliUsed = wugong.getJingliUsed() != null ? wugong.getJingliUsed() : 3;
        if (energy < jingliUsed) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("你的精力不够，无法练习。"));
            return;
        }

        // 检查潜能
        long potential = player.getPotential() != null ? player.getPotential() : 0;
        long qiannengUsed = wugong.getQiannengUsed() != null ? wugong.getQiannengUsed() : 1;
        if (potential < qiannengUsed) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.error("你的潜能不够，无法练习。"));
            return;
        }

        // 消耗精力和潜能
        player.setEnergy(energy - jingliUsed);
        player.setPotential(potential - qiannengUsed);
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你开始练习" + wugong.getName() + "，消耗了" +
                        jingliUsed + "点精力和" + qiannengUsed + "点潜能。"));

        // 推送HP更新
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
