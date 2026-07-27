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

import java.util.List;

@Component
@RequiredArgsConstructor
public class InventoryCommand implements CommandHandler {

    private final PlayerThingMapper playerThingMapper;
    private final ThingMapper thingMapper;

    @Override
    public String getCommandName() {
        return "inventory";
    }

    @Override
    public String getDescription() {
        return "查看身上物品";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        LambdaQueryWrapper<PlayerThing> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(PlayerThing::getPlayerId, player.getId());
        List<PlayerThing> playerThings = playerThingMapper.selectList(wrapper);

        if (playerThings.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你身上没有任何物品。"));
            return;
        }

        StringBuilder sb = new StringBuilder();
        sb.append("===== 身上物品 =====\n");

        // 已装备的物品
        sb.append("\n【已装备】\n");
        boolean hasEquipped = false;
        for (PlayerThing pt : playerThings) {
            if (pt.getEquipped() != null && pt.getEquipped() == 1) {
                Thing thing = thingMapper.selectById(pt.getThingId());
                if (thing != null) {
                    sb.append("  ").append(thing.getFontName() != null && !thing.getFontName().isEmpty() ? thing.getFontName() : thing.getName());
                    sb.append(" [").append(pt.getSlot()).append("]");
                    sb.append("\n");
                    hasEquipped = true;
                }
            }
        }
        if (!hasEquipped) {
            sb.append("  无\n");
        }

        // 背包物品
        sb.append("\n【背包】\n");
        boolean hasItems = false;
        for (PlayerThing pt : playerThings) {
            if (pt.getEquipped() == null || pt.getEquipped() == 0) {
                Thing thing = thingMapper.selectById(pt.getThingId());
                if (thing != null) {
                    sb.append("  ").append(thing.getFontName() != null && !thing.getFontName().isEmpty() ? thing.getFontName() : thing.getName());
                    sb.append(" x").append(pt.getCount());
                    sb.append(" (").append(thing.getQuantifier()).append(")");
                    sb.append("\n");
                    hasItems = true;
                }
            }
        }
        if (!hasItems) {
            sb.append("  无\n");
        }

        sb.append("\n负重: ").append(player.getWeight()).append("/").append(player.getMaxWeight()).append("\n");

        engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
    }
}
