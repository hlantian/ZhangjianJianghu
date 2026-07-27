package com.zjjh.mud.game.combat;

import org.springframework.stereotype.Service;

import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

/**
 * 战斗描述生成服务 - 对应原项目 fightmiaoshu.cpp
 */
@Service
public class CombatMessageService {

    private static final Random random = ThreadLocalRandom.current();

    /**
     * 武功级别描述 (36级)
     */
    private static final String[] WUGONG_LEVEL_DESC = {
        "*不堪一击*", "*毫不足虑*", "*不足挂齿*", "*初学乍练*", "*初窥门径*", "*略知一二*",
        "*普普通通*", "*平平淡淡*", "*平淡无奇*", "*粗通皮毛*", "*马马虎虎*", "*略有小成*",
        "*驾轻就熟*", "*心领神会*", "*了然於胸*", "*略有大成*", "*已有大成*", "*豁然贯通*",
        "*出类拔萃*", "*无可匹敌*", "*技冠群雄*", "*神乎其技*", "*出神入化*", "*傲视群雄*",
        "*登峰造极*", "*所向披靡*", "*一代宗师*", "*神功盖世*", "*举世无双*", "*惊世骇俗*",
        "*震古铄今*", "*深藏不露*", "*深不可测*", "*返朴归真*", "*物我两忘*", "*至尊无敌*"
    };

    /**
     * 气血形容 (6级)
     */
    private static final String[] BODY_DESC = {
        "看上去气血充盈，没有受一点伤。",
        "看上去气血充盈，受了一点小伤。",
        "受了一点轻伤，没有什么关系。",
        "的伤势有些严重了，要好好休息了。",
        "的伤势很严重了，再不休息会死的啊。",
        "有如风中之烛，随时都有可能倒下。"
    };

    /**
     * 生成武功级别描述
     */
    public String getWugongLevelDesc(int level) {
        if (level < 0) level = 0;
        if (level >= WUGONG_LEVEL_DESC.length) level = WUGONG_LEVEL_DESC.length - 1;
        return WUGONG_LEVEL_DESC[level];
    }

    /**
     * 根据气血百分比获取气血形容
     */
    public String getBodyDesc(long body, long maxBody) {
        if (maxBody <= 0) return BODY_DESC[0];
        int percent = (int)(body * 100 / maxBody);
        if (percent >= 90) return BODY_DESC[0];
        if (percent >= 70) return BODY_DESC[1];
        if (percent >= 50) return BODY_DESC[2];
        if (percent >= 30) return BODY_DESC[3];
        if (percent >= 10) return BODY_DESC[4];
        return BODY_DESC[5];
    }

    /**
     * 生成刺伤描述
     */
    public String getStabDesc(long damage) {
        if (damage < 10) return "觉得只是轻轻地被刺破皮肉。";
        if (damage < 20) return "被刺出一个创口。";
        if (damage < 40) return "「噗」地一声刺入了寸许。";
        if (damage < 80) return "「噗」地一声刺进去！";
        if (damage < 120) return "「噗嗤」地一声刺出一个血肉模糊的血窟窿！";
        return "一声惨嚎，已对穿而出，鲜血溅得满地！！";
    }

    /**
     * 生成砍伤描述
     */
    public String getSlashDesc(long damage) {
        if (damage < 10) return "觉得只是轻轻地划破了皮肉。";
        if (damage < 20) return "感到划出一道细长的血痕。";
        if (damage < 40) return "「嗤」地一声划出一道伤口！";
        if (damage < 80) return "「嗤」地一声划出一道血淋淋的伤口！";
        if (damage < 120) return "划出一道又长又深的伤口，鲜血四溅。";
        return "划出一道深及见骨的可怕伤口！！";
    }

    /**
     * 生成空手伤描述
     */
    public String getBluntDesc(long damage) {
        if (damage < 10) return "觉得只是轻轻地碰到，比拍苍蝇稍微重了点。";
        if (damage < 20) return "没有躲开，造成一处瘀青。";
        if (damage < 40) return "身上登时肿了一块老高！";
        if (damage < 80) return "闷哼了一声显然吃了不小的亏！";
        if (damage < 120) return "只听见「砰」地一声，退了两步！";
        if (damage < 160) return "这一下「砰」地一声,连退了好几步，差一点摔倒！";
        return "被重重地击中，「哇」地一声吐出一口鲜血。";
    }

    /**
     * 生成咬伤描述
     */
    public String getBiteDesc(long damage) {
        if (damage < 10) return "只是轻轻的留下了咬痕。";
        if (damage < 20) return "到被咬了一口，留下了一道血印。";
        if (damage < 40) return "被重重的咬住，出现了几个小洞。";
        if (damage < 80) return "只听「嗤」地一声,一块肉已经被咬了下来。";
        return "一声惨嚎，被咬中的地方开始「泊泊」的流起了鲜血。";
    }

    /**
     * 生成毒伤描述
     */
    public String getPoisonDesc(long damage) {
        if (damage < 10) return "只是轻轻的搽过，皮肤上微微有点青黑色。";
        if (damage < 20) return "皮肤上出现明显青黑色。";
        if (damage < 40) return "皮肤上出现青黑色，手脚也有些不听使唤。";
        if (damage < 80) return "青黑色一直朝面部蔓延而去，望着十分恐怖。";
        return "一声惨嚎，吐出一口黑血，面色整个变成青黑色。";
    }

    /**
     * 生成伤害结果描述
     */
    public String getDamageResultDesc(long damage) {
        if (damage < 5) return "结果只是勉强造成一处轻微";
        if (damage < 10) return "结果造成轻微的";
        if (damage < 20) return "结果造成一处";
        if (damage < 30) return "结果造成一处严重";
        if (damage < 50) return "结果造成颇为严重的";
        if (damage < 80) return "结果造成相当严重的";
        if (damage < 100) return "结果造成十分严重的";
        if (damage < 160) return "结果造成极其严重的";
        return "结果造成非常可怕的严重";
    }

    /**
     * 生成停手描述
     */
    public String getHaltDesc() {
        String[] descs = {
            "哈哈大笑，说道：承让了！",
            "双手一拱，笑著说道：承让！",
            "胜了这招，向后跃开三尺，笑道：承让！",
            "双手一拱，笑著说道：知道我的利害了吧！",
            "向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！",
            "向后一纵，恨恨地说道：君子报仇，十年不晚！",
            "脸色一寒，说道：算了算了，就当是我让你吧！",
            "纵声而笑，叫道：你运气好！你运气好！一面身子向后跳开。",
            "脸色微变，说道：佩服，佩服！",
            "向后退了几步，说道：这场比试算我输了，佩服，佩服！",
            "向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！"
        };
        return descs[random.nextInt(descs.length)];
    }

    /**
     * 生成攻击描述
     */
    public String getAttackDesc(String attackerName, String defenderName, String weaponType) {
        if (weaponType == null || weaponType.isEmpty()) {
            // 空手
            String[] actions = {
                attackerName + "一拳打向" + defenderName,
                attackerName + "一掌劈向" + defenderName,
                attackerName + "飞起一脚踢向" + defenderName,
                attackerName + "向" + defenderName + "挥出一记重拳"
            };
            return actions[random.nextInt(actions.length)];
        } else {
            // 使用武器
            String[] actions = {
                attackerName + "挥动" + weaponType + "刺向" + defenderName,
                attackerName + "举" + weaponType + "向" + defenderName + "砍去",
                attackerName + "用" + weaponType + "向" + defenderName + "发起攻击",
                attackerName + "持" + weaponType + "直取" + defenderName
            };
            return actions[random.nextInt(actions.length)];
        }
    }

    /**
     * 根据武器类型获取伤害类型
     */
    public String getDamageType(String weaponType) {
        if (weaponType == null || weaponType.isEmpty()) return "blunt";
        switch (weaponType) {
            case "sword": return "stab";   // 剑-刺伤
            case "saber": return "slash";  // 刀-砍伤
            case "fist":  return "blunt";  // 拳-空手伤
            case "spear": return "stab";   // 枪-刺伤
            case "whip":  return "slash";  // 鞭-砍伤
            default: return "blunt";
        }
    }

    /**
     * 获取伤害描述
     */
    public String getDamageDesc(String damageType, long damage) {
        switch (damageType) {
            case "stab": return getStabDesc(damage);
            case "slash": return getSlashDesc(damage);
            case "blunt": return getBluntDesc(damage);
            case "bite": return getBiteDesc(damage);
            case "poison": return getPoisonDesc(damage);
            default: return getBluntDesc(damage);
        }
    }

    /**
     * 获取容貌描述
     */
    public String getFeatureDesc(long feature, boolean isMale) {
        if (isMale) {
            if (feature > 80) return "长得宛如玉树临风，风流倜傥，顾盼之间，神采飞扬。真正是人中龙凤！";
            if (feature > 70) return "长得英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。";
            if (feature > 60) return "长得相貌英俊，仪表堂堂。骨格清奇，丰姿非俗。";
            if (feature > 50) return "长得五官端正。";
            if (feature > 40) return "长得相貌平平。没什么好看的。";
            return "长的...有点对不住别人。";
        } else {
            if (feature > 80) return "有倾国倾城之貌，容色丽都，娇艳绝伦，堪称人间仙子！";
            if (feature > 70) return "长得清丽绝俗，风姿动人。有沉鱼落雁之容，避月羞花之貌！";
            if (feature > 60) return "长得肤如凝脂，眉目如画，风情万种，楚楚动人。";
            if (feature > 55) return "长得容色秀丽，面带晕红，眼含秋波。";
            if (feature > 50) return "长得气质高雅，面目姣好。";
            if (feature > 45) return "长得相貌平平，还看得过去。";
            if (feature > 40) return "她长得的相貌嘛...马马虎虎吧。";
            return "长得和无盐有点相似耶。";
        }
    }
}
