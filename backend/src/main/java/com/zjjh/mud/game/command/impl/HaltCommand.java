package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.combat.CombatService;
import com.zjjh.mud.game.engine.GameEngine;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

@Component
@RequiredArgsConstructor
public class HaltCommand implements CommandHandler {

    private final CombatService combatService;

    @Override
    public String getCommandName() {
        return "halt";
    }

    @Override
    public String getDescription() {
        return "停止战斗";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        combatService.halt(engine, player.getId());
    }
}
