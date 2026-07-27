package com.zjjh.mud.game.timer;

import com.zjjh.mud.game.combat.CombatService;
import com.zjjh.mud.game.engine.GameEngine;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Slf4j
@Component
@RequiredArgsConstructor
public class CombatRoundTask {

    private final GameEngine gameEngine;
    private final CombatService combatService;

    /**
     * 战斗回合 - 每5秒执行一次
     */
    @Scheduled(fixedDelay = 5000)
    public void combatRound() {
        if (!gameEngine.isRunning()) return;

        var combats = combatService.getActiveCombats();
        if (combats.isEmpty()) return;

        for (var entry : combats.entrySet()) {
            try {
                combatService.executeRound(gameEngine, entry.getValue());
            } catch (Exception e) {
                log.error("战斗回合异常: attacker={}", entry.getKey(), e);
                combatService.endCombat(entry.getKey());
            }
        }
    }
}
