package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("player_things")
public class PlayerThing {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long playerId;
    private Long thingId;
    private Integer count;
    private Integer equipped;
    private String slot;
}
