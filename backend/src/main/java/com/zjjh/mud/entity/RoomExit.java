package com.zjjh.mud.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName("room_exits")
public class RoomExit {
    @TableId(type = IdType.AUTO)
    private Long id;
    private Long roomId;
    private String direction;
    private Long targetRoomId;
    private Integer isHidden;
}
