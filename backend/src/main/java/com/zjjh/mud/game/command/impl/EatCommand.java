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
public class EatCommand implements CommandHandler {

    private final PlayerThingMapper playerThingMapper;
    private final ThingMapper thingMapper;

    @Override
    public String getCommandName() {
        return "eat";
    }

    @Override
    public String getDescription() {
        return "吃东西 (eat <食物名>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要吃什么？");
            return;
        }

        String itemName = args.trim();
        LambdaQueryWrapper<Thing> thingWrapper = new LambdaQueryWrapper<>();
        thingWrapper.eq(Thing::getName, itemName)
                     .or().eq(Thing::getFontName, itemName)
                     .last("LIMIT 1");
        Thing thing = thingMapper.selectOne(thingWrapper);

        if (thing == null || !"food".equals(thing.getCategory())) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("这不是食物。"));
            return;
        }

        LambdaQueryWrapper<PlayerThing> ptWrapper = new LambdaQueryWrapper<>();
        ptWrapper.eq(PlayerThing::getPlayerId, player.getId())
                 .eq(PlayerThing::getThingId, thing.getId())
                 .eq(PlayerThing::getEquipped, 0);
        PlayerThing pt = playerThingMapper.selectOne(ptWrapper);

        if (pt == null || pt.getCount() <= 0) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("你没有这个食物。"));
            return;
        }

        // 消耗食物
        if (pt.getCount() > 1) {
            pt.setCount(pt.getCount() - 1);
            playerThingMapper.updateById(pt);
        } else {
            playerThingMapper.deleteById(pt.getId());
        }

        // 恢复食物值
        long foodValue = 50;
        long currentFood = player.getFood() != null ? player.getFood() : 0;
        long maxFood = player.getMaxFood() != null ? player.getMaxFood() : 200;
        player.setFood(Math.min(maxFood, currentFood + foodValue));
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你吃了" + thing.getFontName() + "，感觉饱了一些。"));

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
