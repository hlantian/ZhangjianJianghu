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
public class DropCommand implements CommandHandler {

    private final PlayerThingMapper playerThingMapper;
    private final ThingMapper thingMapper;

    @Override
    public String getCommandName() {
        return "drop";
    }

    @Override
    public String getDescription() {
        return "丢弃物品 (drop <物品名>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要丢弃什么？");
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

        LambdaQueryWrapper<PlayerThing> ptWrapper = new LambdaQueryWrapper<>();
        ptWrapper.eq(PlayerThing::getPlayerId, player.getId())
                 .eq(PlayerThing::getThingId, thing.getId())
                 .eq(PlayerThing::getEquipped, 0);
        PlayerThing pt = playerThingMapper.selectOne(ptWrapper);

        if (pt == null || pt.getCount() <= 0) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("你没有这个物品。"));
            return;
        }

        // 减少数量
        if (pt.getCount() > 1) {
            pt.setCount(pt.getCount() - 1);
            playerThingMapper.updateById(pt);
        } else {
            playerThingMapper.deleteById(pt.getId());
        }

        // 更新负重
        long weight = (player.getWeight() != null ? player.getWeight() : 0) - (thing.getWeight() != null ? thing.getWeight() : 1);
        player.setWeight(Math.max(0, weight));
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你丢弃了" + thing.getFontName() + "。"));
    }
}
