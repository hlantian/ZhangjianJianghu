package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("wugong")
public class Wugong {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String name;
    private String description;
    private String menpai;
    private String leixing;
    private String zhaoshu;
    private Long fangshouli;
    private Long neigongNeeded;
    private Long jibenNeeded;
    private Long jingyanNeeded;
    private Long jingliUsed;
    private Long qiannengUsed;
    private Integer isSpecial;
    private String correspondingBasic;
    private String allUniqueSkill;
}
