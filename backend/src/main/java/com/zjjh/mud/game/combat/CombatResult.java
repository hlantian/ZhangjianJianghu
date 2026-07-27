package com.zjjh.mud.game.combat;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class CombatResult {
    /** 攻击者造成的伤害 */
    private long damage;
    /** 伤害类型: stab(刺伤)/slash(砍伤)/blunt(空手伤)/bite(咬伤)/poison(毒伤) */
    private String damageType;
    /** 战斗描述文本 */
    private String attackerMessage;  // 攻击者看到的
    private String defenderMessage;  // 防御者看到的
    private String observerMessage;  // 旁观者看到的
    /** 攻击者是否命中 */
    private boolean hit;
    /** 防御者是否闪避 */
    private boolean dodged;
    /** 防御者是否招架 */
    private boolean parried;
    /** 防御者剩余气血 */
    private long defenderBody;
    /** 防御者是否死亡 */
    private boolean defenderDead;
    /** 攻击者获得的经验 */
    private long expGained;
    /** 攻击者获得的潜能 */
    private long potentialGained;

    public CombatResult(long damage, String damageType) {
        this.damage = damage;
        this.damageType = damageType;
        this.hit = true;
    }

    public static CombatResult miss() {
        CombatResult result = new CombatResult();
        result.setHit(false);
        return result;
    }

    public static CombatResult dodged() {
        CombatResult result = new CombatResult();
        result.setHit(false);
        result.setDodged(true);
        return result;
    }

    public static CombatResult parried() {
        CombatResult result = new CombatResult();
        result.setHit(false);
        result.setParried(true);
        return result;
    }
}
