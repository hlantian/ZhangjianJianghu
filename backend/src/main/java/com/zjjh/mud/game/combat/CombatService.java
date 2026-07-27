package com.zjjh.mud.game.combat;

import com.zjjh.mud.entity.Npc;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.game.engine.PlayerManager;
import com.zjjh.mud.service.AuthService;
import lombok.Data;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.Map;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ThreadLocalRandom;

/**
 * 战斗服务 - 对应原项目 yactor.cpp 战斗逻辑
 */
@Slf4j
@Service
@RequiredArgsConstructor
public class CombatService {

    private final CombatMessageService messageService;
    private final AuthService authService;

    // 战斗状态: playerId -> CombatInfo
    private final Map<Long, CombatInfo> activeCombats = new ConcurrentHashMap<>();

    @Data
    public static class CombatInfo {
        public enum CombatType { FIGHT, KILL } // 较量 vs 对杀
        private Long attackerId;
        private String attackerName;
        private Long defenderId;     // NPC的id为负数区分
        private String defenderName;
        private boolean defenderIsNpc;
        private CombatType type;
        private long lastRoundTime;
        private int roundCount;
    }

    /**
     * 计算总攻击力
     */
    public long calcAttackPower(Player player) {
        return (player.getInhereAttack() != null ? player.getInhereAttack() : 0)
             + (player.getWeaponAttack() != null ? player.getWeaponAttack() : 0)
             + (player.getAppendAttack() != null ? player.getAppendAttack() : 0)
             + (player.getPowerupAttack() != null ? player.getPowerupAttack() : 0)
             + (player.getForceAttack() != null ? player.getForceAttack() : 0);
    }

    /**
     * 计算总防御力
     */
    public long calcDefensePower(Player player) {
        return (player.getInhereDefense() != null ? player.getInhereDefense() : 0)
             + (player.getAppendDefense() != null ? player.getAppendDefense() : 0)
             + (player.getPowerupDefense() != null ? player.getPowerupDefense() : 0);
    }

    /**
     * 计算NPC总攻击力
     */
    public long calcNpcAttackPower(Npc npc) {
        return npc.getInhereAttack() != null ? npc.getInhereAttack() : 150;
    }

    /**
     * 计算NPC总防御力
     */
    public long calcNpcDefensePower(Npc npc) {
        return npc.getInhereDefense() != null ? npc.getInhereDefense() : 150;
    }

    /**
     * 发起战斗(较量)
     */
    public boolean startFight(GameEngine engine, Player attacker, String targetName) {
        Long roomId = attacker.getRoomId();
        if (roomId == null) return false;

        // 检查房间是否禁止战斗
        var room = engine.getRoomManager().getRoom(roomId);
        if (room != null && room.getForbidFight() != null && room.getForbidFight() == 1) {
            engine.getMessageService().sendToPlayer(attacker.getId(),
                    "这里是和平区域，不允许战斗。");
            return false;
        }

        // 检查是否已在战斗中
        if (activeCombats.containsKey(attacker.getId())) {
            engine.getMessageService().sendToPlayer(attacker.getId(),
                    "你已经在战斗中了！");
            return false;
        }

        // 查找目标NPC
        Npc npc = engine.getRoomManager().getNpcByName(roomId, targetName);
        if (npc != null) {
            CombatInfo info = new CombatInfo();
            info.setAttackerId(attacker.getId());
            info.setAttackerName(attacker.getName());
            info.setDefenderId(-npc.getId()); // NPC用负数
            info.setDefenderName(npc.getName());
            info.setDefenderIsNpc(true);
            info.setType(CombatInfo.CombatType.FIGHT);
            info.setLastRoundTime(System.currentTimeMillis());
            info.setRoundCount(0);
            activeCombats.put(attacker.getId(), info);

            engine.getMessageService().sendToPlayer(attacker.getId(),
                    GameMessage.combat("你向" + npc.getName() + "发起了较量！"));
            engine.getMessageService().sendToRoom(roomId,
                    GameMessage.combat(attacker.getName() + "向" + npc.getName() + "发起了较量！"));
            return true;
        }

        // 查找目标玩家
        for (Player target : engine.getPlayerManager().getOnlinePlayersInRoom(roomId)) {
            if (target.getName().contains(targetName) && !target.getId().equals(attacker.getId())) {
                CombatInfo info = new CombatInfo();
                info.setAttackerId(attacker.getId());
                info.setAttackerName(attacker.getName());
                info.setDefenderId(target.getId());
                info.setDefenderName(target.getName());
                info.setDefenderIsNpc(false);
                info.setType(CombatInfo.CombatType.FIGHT);
                info.setLastRoundTime(System.currentTimeMillis());
                info.setRoundCount(0);
                activeCombats.put(attacker.getId(), info);

                engine.getMessageService().sendToPlayer(attacker.getId(),
                        GameMessage.combat("你向" + target.getName() + "发起了较量！"));
                engine.getMessageService().sendToPlayer(target.getId(),
                        GameMessage.combat(attacker.getName() + "向你发起了较量！"));
                return true;
            }
        }

        engine.getMessageService().sendToPlayer(attacker.getId(),
                "这里没有 " + targetName + "。");
        return false;
    }

    /**
     * 发起对杀
     */
    public boolean startKill(GameEngine engine, Player attacker, String targetName) {
        if (startFight(engine, attacker, targetName)) {
            CombatInfo info = activeCombats.get(attacker.getId());
            if (info != null) {
                info.setType(CombatInfo.CombatType.KILL);
                engine.getMessageService().sendToPlayer(attacker.getId(),
                        GameMessage.combat("你决定要杀死" + targetName + "！"));
            }
            return true;
        }
        return false;
    }

    /**
     * 执行一个战斗回合
     */
    public CombatResult executeRound(GameEngine engine, CombatInfo info) {
        Random random = ThreadLocalRandom.current();
        CombatResult result = new CombatResult();

        Player attacker = engine.getPlayerManager().getOnlinePlayer(info.getAttackerId());
        if (attacker == null) {
            endCombat(info.getAttackerId());
            return CombatResult.miss();
        }

        long attackPower = calcAttackPower(attacker);
        long defensePower;

        if (info.isDefenderIsNpc()) {
            Npc npc = engine.getRoomManager().getRoomNpcs(attacker.getRoomId())
                    .stream()
                    .filter(n -> n.getName().equals(info.getDefenderName()))
                    .findFirst()
                    .orElse(null);
            if (npc == null) {
                engine.getMessageService().sendToPlayer(attacker.getId(),
                        GameMessage.combat(info.getDefenderName() + " 已经不在了。"));
                endCombat(info.getAttackerId());
                return CombatResult.miss();
            }

            defensePower = calcNpcDefensePower(npc);
            long npcAttack = calcNpcAttackPower(npc);

            // 计算伤害
            long damage = Math.max(1, attackPower - defensePower / 2 + random.nextInt(20) - 10);
            damage = (long)(damage * (0.8 + random.nextDouble() * 0.4)); // 80%-120%浮动

            // NPC闪避/招架
            int dodgeChance = 15;
            if (random.nextInt(100) < dodgeChance) {
                result = CombatResult.dodged();
                result.setAttackerMessage(info.getDefenderName() + "身形一闪，躲过了你的攻击！");
                result.setObserverMessage(info.getDefenderName() + "闪身躲过了" + info.getAttackerName() + "的攻击。");
                engine.getMessageService().sendToPlayer(attacker.getId(),
                        GameMessage.combat(result.getAttackerMessage()));
                return result;
            }

            // 命中
            npc.setBody(npc.getBody() - damage);
            result.setDamage(damage);
            result.setDefenderBody(npc.getBody());
            result.setDefenderDead(npc.getBody() <= 0);

            // 生成描述
            String weaponType = attacker.getWeaponType() != null ? attacker.getWeaponType() : "";
            String damageType = messageService.getDamageType(weaponType);
            String attackDesc = messageService.getAttackDesc(attacker.getName(), npc.getName(), weaponType);
            String damageDesc = messageService.getDamageDesc(damageType, damage);
            String resultDesc = messageService.getDamageResultDesc(damage);

            result.setAttackerMessage(attackDesc + "，" + damageDesc + " " + resultDesc + "伤害。");
            result.setObserverMessage(attackDesc + "，" + damageDesc);

            engine.getMessageService().sendToPlayer(attacker.getId(),
                    GameMessage.combat(result.getAttackerMessage()));
            engine.getMessageService().sendToRoom(attacker.getRoomId(),
                    GameMessage.combat(result.getObserverMessage()));

            // NPC反击
            long npcDamage = Math.max(1, npcAttack - calcDefensePower(attacker) / 2 + random.nextInt(10) - 5);
            npcDamage = (long)(npcDamage * (0.8 + random.nextDouble() * 0.4));
            attacker.setBody(attacker.getBody() - npcDamage);
            engine.getPlayerManager().updateOnlinePlayer(attacker);

            String npcAttackDesc = messageService.getAttackDesc(npc.getName(), attacker.getName(), npc.getWeaponType());
            String npcDamageDesc = messageService.getDamageDesc(messageService.getDamageType(npc.getWeaponType()), npcDamage);

            engine.getMessageService().sendToPlayer(attacker.getId(),
                    GameMessage.combat(npcAttackDesc + "，" + npcDamageDesc + " 你受到" + npcDamage + "点伤害！"));
            engine.getMessageService().sendToRoom(attacker.getRoomId(),
                    GameMessage.combat(npcAttackDesc + "，" + npcDamageDesc));

            // 推送HP更新
            engine.getMessageService().sendHpUpdate(
                    attacker.getId(),
                    attacker.getBody(), attacker.getMaxBody(),
                    attacker.getEnergy(), attacker.getMaxEnergy(),
                    attacker.getInternalForce(), attacker.getMaxInternalForce(),
                    attacker.getFood(), attacker.getMaxFood(),
                    attacker.getDrink(), attacker.getMaxDrink()
            );

            // NPC死亡
            if (result.isDefenderDead()) {
                handleNpcDeath(engine, attacker, npc, info);
                endCombat(attacker.getId());
            }

            // 玩家死亡
            if (attacker.getBody() <= 0) {
                handlePlayerDeath(engine, attacker, npc);
                endCombat(attacker.getId());
            }

        } else {
            // 玩家vs玩家
            Player defender = engine.getPlayerManager().getOnlinePlayer(info.getDefenderId());
            if (defender == null) {
                engine.getMessageService().sendToPlayer(attacker.getId(),
                        GameMessage.combat(info.getDefenderName() + " 已经不在了。"));
                endCombat(info.getAttackerId());
                return CombatResult.miss();
            }

            defensePower = calcDefensePower(defender);
            long damage = Math.max(1, attackPower - defensePower / 2 + random.nextInt(20) - 10);
            damage = (long)(damage * (0.8 + random.nextDouble() * 0.4));

            defender.setBody(defender.getBody() - damage);
            engine.getPlayerManager().updateOnlinePlayer(defender);

            result.setDamage(damage);
            result.setDefenderBody(defender.getBody());
            result.setDefenderDead(defender.getBody() <= 0);

            String weaponType = attacker.getWeaponType() != null ? attacker.getWeaponType() : "";
            String damageType = messageService.getDamageType(weaponType);
            String attackDesc = messageService.getAttackDesc(attacker.getName(), defender.getName(), weaponType);
            String damageDesc = messageService.getDamageDesc(damageType, damage);

            result.setAttackerMessage(attackDesc + "，" + damageDesc);
            engine.getMessageService().sendToPlayer(attacker.getId(),
                    GameMessage.combat(result.getAttackerMessage()));
            engine.getMessageService().sendToPlayer(defender.getId(),
                    GameMessage.combat(attackDesc + "，" + damageDesc + " 你受到" + damage + "点伤害！"));
            engine.getMessageService().sendToRoom(attacker.getRoomId(),
                    GameMessage.combat(attackDesc + "，" + damageDesc));

            // 推送HP更新给防御者
            engine.getMessageService().sendHpUpdate(
                    defender.getId(),
                    defender.getBody(), defender.getMaxBody(),
                    defender.getEnergy(), defender.getMaxEnergy(),
                    defender.getInternalForce(), defender.getMaxInternalForce(),
                    defender.getFood(), defender.getMaxFood(),
                    defender.getDrink(), defender.getMaxDrink()
            );

            if (result.isDefenderDead()) {
                handlePlayerKillPlayer(engine, attacker, defender);
                endCombat(attacker.getId());
            }
        }

        info.setRoundCount(info.getRoundCount() + 1);
        info.setLastRoundTime(System.currentTimeMillis());

        return result;
    }

    /**
     * 停止战斗
     */
    public void halt(GameEngine engine, Long playerId) {
        CombatInfo info = activeCombats.remove(playerId);
        if (info != null) {
            String haltDesc = messageService.getHaltDesc();
            engine.getMessageService().sendToPlayer(playerId, GameMessage.combat(haltDesc));
            engine.getMessageService().sendToRoom(
                    info.getAttackerId() != null ? getPlayerRoomId(engine, playerId) : null,
                    GameMessage.combat(info.getAttackerName() + haltDesc));
        } else {
            engine.getMessageService().sendToPlayer(playerId, "你没有在战斗中。");
        }
    }

    /**
     * 检查是否在战斗中
     */
    public boolean isInCombat(Long playerId) {
        return activeCombats.containsKey(playerId);
    }

    /**
     * 获取战斗信息
     */
    public CombatInfo getCombatInfo(Long playerId) {
        return activeCombats.get(playerId);
    }

    /**
     * 结束战斗
     */
    public void endCombat(Long playerId) {
        activeCombats.remove(playerId);
    }

    /**
     * 获取所有活跃战斗
     */
    public Map<Long, CombatInfo> getActiveCombats() {
        return activeCombats;
    }

    private Long getPlayerRoomId(GameEngine engine, Long playerId) {
        Player p = engine.getPlayerManager().getOnlinePlayer(playerId);
        return p != null ? p.getRoomId() : null;
    }

    /**
     * 处理NPC死亡
     */
    private void handleNpcDeath(GameEngine engine, Player attacker, Npc npc, CombatInfo info) {
        String deathMsg = npc.getName() + "倒下了！";
        engine.getMessageService().sendToPlayer(attacker.getId(),
                GameMessage.combat("你击败了" + npc.getName() + "！"));
        engine.getMessageService().sendToRoom(attacker.getRoomId(),
                GameMessage.combat(attacker.getName() + "击败了" + npc.getName() + "！"));

        // 经验奖励
        long expReward = Math.max(10, npc.getLevel() != null ? npc.getLevel() * 10 : 100);
        long potentialReward = Math.max(1, expReward / 10);

        // 对杀才有经验
        if (info.getType() == CombatInfo.CombatType.KILL) {
            attacker.setExperience(attacker.getExperience() + expReward);
            attacker.setPotential(attacker.getPotential() + potentialReward);
            attacker.setKillTimes(attacker.getKillTimes() + 1);
            engine.getPlayerManager().updateOnlinePlayer(attacker);

            engine.getMessageService().sendToPlayer(attacker.getId(),
                    GameMessage.info("你获得了" + expReward + "点经验，" + potentialReward + "点潜能。"));
        }

        // NPC复活(重置气血)
        npc.setBody(npc.getMaxBody());
    }

    /**
     * 处理玩家被NPC杀死
     */
    private void handlePlayerDeath(GameEngine engine, Player player, Npc npc) {
        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.combat("你被" + npc.getName() + "击败了！"));
        engine.getMessageService().sendToRoom(player.getRoomId(),
                GameMessage.combat(player.getName() + "被" + npc.getName() + "击败了！"));

        // 玩家死亡处理
        player.setBody(player.getMaxBody() / 2);
        player.setEnergy(player.getMaxEnergy() / 2);
        player.setBeKillTimes(player.getBeKillTimes() + 1);
        player.setRoomId(13L); // 鬼门关
        engine.getPlayerManager().updateOnlinePlayer(player);
        engine.getPlayerManager().movePlayerToRoom(player.getId(), 13L);

        engine.getMessageService().sendToPlayer(player.getId(),
                GameMessage.system("你被传送到了鬼门关。"));
    }

    /**
     * 处理玩家杀死玩家
     */
    private void handlePlayerKillPlayer(GameEngine engine, Player killer, Player victim) {
        engine.getMessageService().sendToPlayer(killer.getId(),
                GameMessage.combat("你击败了" + victim.getName() + "！"));
        engine.getMessageService().sendToPlayer(victim.getId(),
                GameMessage.combat("你被" + killer.getName() + "击败了！"));
        engine.getMessageService().sendToRoom(killer.getRoomId(),
                GameMessage.combat(killer.getName() + "击败了" + victim.getName() + "！"));

        // PK统计
        killer.setPkTimes(killer.getPkTimes() + 1);
        killer.setExperience(killer.getExperience() + 50);
        engine.getPlayerManager().updateOnlinePlayer(killer);

        // 受害者处理
        victim.setBody(victim.getMaxBody() / 2);
        victim.setEnergy(victim.getMaxEnergy() / 2);
        victim.setBePkTimes(victim.getBePkTimes() + 1);
        victim.setRoomId(13L); // 鬼门关
        engine.getPlayerManager().updateOnlinePlayer(victim);
        engine.getPlayerManager().movePlayerToRoom(victim.getId(), 13L);

        engine.getMessageService().sendToPlayer(killer.getId(),
                GameMessage.info("你PK获胜，获得50点经验。"));
        engine.getMessageService().sendToPlayer(victim.getId(),
                GameMessage.system("你被传送到了鬼门关。"));
    }
}
