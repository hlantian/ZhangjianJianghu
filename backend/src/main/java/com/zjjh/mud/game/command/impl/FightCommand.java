package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.combat.CombatService;
import com.zjjh.mud.game.engine.GameEngine;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
public class FightCommand implements CommandHandler {

    private final CombatService combatService;

    @Override
    public String getCommandName() {
        return "fight";
    }

    @Override
    public String getDescription() {
        return "较量武功 (fight <名字>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    "你要和谁较量？");
            return;
        }
        combatService.startFight(engine, player, args.trim());
    }
}
