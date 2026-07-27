package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("factions")
public class Faction {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String name;
    private String banner;
    private Long ownerId;
    private String color;
    private Long power;
    private Long playerAmount;
    private Long close;
    private Integer isSchool;
    private java.time.LocalDateTime createTime;
}
