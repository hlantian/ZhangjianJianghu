package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.FieldFill;
import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.time.LocalDateTime;

@Data
@TableName("players")
public class Player {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long userId;
    private String name;
    private String nick;
    private String title;
    private String describe;
    private String sex;
    private Integer age;
    private String iconNo;
    private Long roomId;
    private Integer playerX;
    private Integer playerY;

    // 气血相关
    private Long body;
    private Long maxBody;
    private Long energy;
    private Long maxEnergy;
    private Long addMaxEnergy;

    // 内力相关
    private Long internalForce;
    private Long maxInternalForce;
    private Long addMaxInternalForce;

    // 经验与潜能
    private Long experience;
    private Long potential;
    private Long goodnessCount;

    // 食物饮水
    private Long food;
    private Long maxFood;
    private Long drink;
    private Long maxDrink;

    // 负重与金钱
    private Long weight;
    private Long maxWeight;
    private Long deposit;

    // 先天属性
    private Long beginArm;
    private Long beginLearn;
    private Long beginForce;
    private Long beginDodge;

    // 后天属性
    private Long lastArm;
    private Long lastLearn;
    private Long lastForce;
    private Long lastDodge;

    // 攻击力
    private Long inhereAttack;
    private Long powerupAttack;
    private Long appendAttack;
    private Long forceAttack;
    private Long weaponAttack;

    // 防御力
    private Long inhereDefense;
    private Long powerupDefense;
    private Long appendDefense;

    // 容貌福缘
    private Long feature;
    private Long addFeature;
    private Long luck;
    private Long addLuck;

    // 战斗状态
    private Long wimpy;
    private Long freeTime;
    private Long busy;
    private Long faintTime;
    private Long sleepTime;

    // 击杀统计
    private Long killTimes;
    private Long beKillTimes;
    private Long pkTimes;
    private Long bePkTimes;
    private Long cityKill;
    private Long giveThing;

    // 门派/帮派
    private Long factionId;
    private String factionTitle;
    private Integer isFactionOwner;
    private Long partyValue;
    private Long courtValue;
    private Long societyValue;

    // 在线统计
    private Long onlineTime;
    private Long lastOnlineTime;
    private Long playerLevel;
    private Long playerSleepSkip;
    private Long playerRenew;
    private Long nowWork;

    // 频道开关
    private Integer closeChat;
    private Integer closeRumor;
    private Integer closeNewbie;
    private Integer closeParty;
    private Integer closeFactionParty;

    // 位置与状态
    private String status;
    private String adversary;
    private String followYou;
    private String youFollow;

    // 师承
    private String teacherName;
    private String school;
    private Long schoolPlace;
    private String allEnemyList;
    private String allSkillsList;
    private String workSkills;

    // 装备
    private String weaponName;
    private String weaponType;
    private String clothName;
    private String armor;
    private String hat;
    private String shoe;
    private String flower;
    private String ring;
    private String necklace;
    private String bangle;

    // 仓库与任务
    private Long ckLevel;
    private String allCkList;
    private String questList;

    // 其他
    private String deathMode;
    private Integer notDead;
    private Long comeIn;
    private Integer noaccept;
    private Integer wizCloseChat;
    private Integer playCloseChat;
    private Long playSaySpeed;

    @TableField(fill = FieldFill.INSERT)
    private LocalDateTime createTime;

    @TableField(fill = FieldFill.INSERT_UPDATE)
    private LocalDateTime updateTime;
}
