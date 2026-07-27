package com.zjjh.mud.game.command.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.entity.PlayerThing;
import com.zjjh.mud.entity.Thing;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.mapper.PlayerThingMapper;
import com.zjjh.mud.mapper.ThingMapper;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
public class WieldCommand implements CommandHandler {

    private final PlayerThingMapper playerThingMapper;
    private final ThingMapper thingMapper;

    @Override
    public String getCommandName() {
        return "wield";
    }

    @Override
    public String getDescription() {
        return "装备武器 (wield <武器名>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要装备什么武器？");
            return;
        }

        String itemName = args.trim();
        LambdaQueryWrapper<Thing> thingWrapper = new LambdaQueryWrapper<>();
        thingWrapper.eq(Thing::getName, itemName).or().eq(Thing::getFontName, itemName).last("LIMIT 1");
        Thing thing = thingMapper.selectOne(thingWrapper);

        if (thing == null) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("没有这个物品。"));
            return;
        }

        if (!"weapon".equals(thing.getCategory())) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("这不是武器。"));
            return;
        }

        // 查找玩家是否有该物品
        LambdaQueryWrapper<PlayerThing> ptWrapper = new LambdaQueryWrapper<>();
        ptWrapper.eq(PlayerThing::getPlayerId, player.getId())
                 .eq(PlayerThing::getThingId, thing.getId());
        PlayerThing pt = playerThingMapper.selectOne(ptWrapper);

        if (pt == null) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("你没有这个物品。"));
            return;
        }

        // 卸下当前武器
        if (player.getWeaponName() != null && !player.getWeaponName().isEmpty()) {
            LambdaQueryWrapper<PlayerThing> oldWrapper = new LambdaQueryWrapper<>();
            oldWrapper.eq(PlayerThing::getPlayerId, player.getId())
                      .eq(PlayerThing::getEquipped, 1)
                      .eq(PlayerThing::getSlot, "weapon");
            PlayerThing oldWeapon = playerThingMapper.selectOne(oldWrapper);
            if (oldWeapon != null) {
                oldWeapon.setEquipped(0);
                oldWeapon.setSlot("");
                playerThingMapper.updateById(oldWeapon);
            }
            // 减去旧武器攻击力
            // (简化处理: 直接设置新武器)
        }

        // 装备新武器
        pt.setEquipped(1);
        pt.setSlot("weapon");
        playerThingMapper.updateById(pt);

        player.setWeaponName(thing.getName());
        player.setWeaponType(thing.getSubType() != null ? thing.getSubType() : "sword");
        player.setWeaponAttack(thing.getAttack() != null ? thing.getAttack() : 0);
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你装备了" + thing.getFontName() + "。"));
    }
}
