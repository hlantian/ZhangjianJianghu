package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("things")
public class Thing {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String name;
    private String fontName;
    private Long weight;
    private Long price;
    private String describe;
    private String quantifier;
    private Integer thingType;
    private String varientName;
    private String category;
    private String subType;
    private Long attack;
    private Long defense;
}
