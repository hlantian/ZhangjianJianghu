package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("rooms")
public class Room {
    @TableId(type = IdType.AUTO)
    private Long id;
    private String roomPath;
    private String name;
    private String description;
    private String roomType;
    private Integer forbidFight;
    private String bossName;
    private Long foodConsume;
    private Long updateTimeInterval;
    private String destroyList;
    private String playListQuit;
    private Integer minX;
    private Integer maxX;
    private Integer minY;
    private Integer maxY;
}
