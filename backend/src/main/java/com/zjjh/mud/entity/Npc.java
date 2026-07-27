package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("npcs")
public class Npc {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String name;
    private Long roomId;
    private String place;
    private String school;
    private Integer allowPrentice;
    private String answerForAgreePrentice;
    private Integer provideQuest;
    private Integer needPate;
    private Integer needKillBySelf;
    private Integer needGeBySelf;
    private Integer uniteKill;
    private String playerSayWhenGiveup;
    private String npcSayWhenNoQuest;
    private String npcSayWhenGiveup;
    private String npcSayWhenBeGive;
    private String npcSayWhenEndQuest;
    private String appraiseName;
    private String npcShow;
    private Long body;
    private Long maxBody;
    private Long energy;
    private Long maxEnergy;
    private Long internalForce;
    private Long maxInternalForce;
    private Long inhereAttack;
    private Long inhereDefense;
    private Long experience;
    private Long level;
    private String iconNo;
    private String sex;
    private Integer age;
    private String allSkillsList;
    private String killerName;
    private Long beKillTimes;
    private String allEnemyList;
    private String deathMode;
    private Integer notDead;
    private String npcType;
    private String title;
    private String nick;
    private String weaponName;
    private String weaponType;
    private String clothName;
}
