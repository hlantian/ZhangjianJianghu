package com.zjjh.mud.game.command.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
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
public class GetCommand implements CommandHandler {

    private final PlayerThingMapper playerThingMapper;
    private final ThingMapper thingMapper;

    @Override
    public String getCommandName() {
        return "get";
    }

    @Override
    public String getDescription() {
        return "拾取物品 (get <物品名>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(), "你要拾取什么？");
            return;
        }

        String itemName = args.trim();
        LambdaQueryWrapper<Thing> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Thing::getName, itemName).or().eq(Thing::getFontName, itemName).last("LIMIT 1");
        Thing thing = thingMapper.selectOne(wrapper);

        if (thing == null) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("没有这个物品。"));
            return;
        }

        // 检查负重
        long totalWeight = (thing.getWeight() != null ? thing.getWeight() : 1) + (player.getWeight() != null ? player.getWeight() : 0);
        if (totalWeight > (player.getMaxWeight() != null ? player.getMaxWeight() : 0)) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("你的负重不够了。"));
            return;
        }

        // 添加到玩家物品
        LambdaQueryWrapper<PlayerThing> ptWrapper = new LambdaQueryWrapper<>();
        ptWrapper.eq(PlayerThing::getPlayerId, player.getId())
                 .eq(PlayerThing::getThingId, thing.getId())
                 .eq(PlayerThing::getEquipped, 0);
        PlayerThing existing = playerThingMapper.selectOne(ptWrapper);

        if (existing != null) {
            existing.setCount(existing.getCount() + 1);
            playerThingMapper.updateById(existing);
        } else {
            PlayerThing pt = new PlayerThing();
            pt.setPlayerId(player.getId());
            pt.setThingId(thing.getId());
            pt.setCount(1);
            pt.setEquipped(0);
            pt.setSlot("");
            playerThingMapper.insert(pt);
        }

        // 更新负重
        player.setWeight(totalWeight);
        engine.getPlayerManager().updateOnlinePlayer(player);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.info("你拾起了" + thing.getFontName() + "。"));
    }
}
