package com.zjjh.mud.game.engine;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.entity.*;
import com.zjjh.mud.mapper.*;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Component;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;

@Slf4j
@Component
@RequiredArgsConstructor
public class RoomManager {

    private final RoomMapper roomMapper;
    private final RoomExitMapper roomExitMapper;
    private final NpcMapper npcMapper;
    private final ThingMapper thingMapper;

    private final RedisTemplate<String, Object> redisTemplate;

    private static final String ROOM_CACHE_KEY = "room:cache:";
    private static final String ROOM_EXIT_CACHE_KEY = "room:exit:";
    private static final long ROOM_CACHE_TTL = 30; // minutes

    // 活跃房间缓存: roomId -> Room
    private final Map<Long, Room> activeRooms = new ConcurrentHashMap<>();

    // 房间出口缓存: roomId -> List<RoomExit>
    private final Map<Long, List<RoomExit>> roomExits = new ConcurrentHashMap<>();

    // 房间内NPC: roomId -> List<Npc>
    private final Map<Long, List<Npc>> roomNpcs = new ConcurrentHashMap<>();

    // 房间内物品: roomId -> List<Thing>
    private final Map<Long, List<Thing>> roomThings = new ConcurrentHashMap<>();

    /**
     * 加载房间
     */
    public Room getRoom(Long roomId) {
        if (roomId == null) {
            return null;
        }
        // 先从内存缓存获取
        Room room = activeRooms.get(roomId);
        if (room != null) {
            return room;
        }
        // 从数据库加载
        room = roomMapper.selectById(roomId);
        if (room != null) {
            activeRooms.put(roomId, room);
            redisTemplate.opsForValue().set(ROOM_CACHE_KEY + roomId, room, ROOM_CACHE_TTL, TimeUnit.MINUTES);
        }
        return room;
    }

    /**
     * 通过路径加载房间
     */
    public Room getRoomByPath(String roomPath) {
        LambdaQueryWrapper<Room> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Room::getRoomPath, roomPath);
        Room room = roomMapper.selectOne(wrapper);
        if (room != null) {
            activeRooms.put(room.getId(), room);
        }
        return room;
    }

    /**
     * 获取房间出口
     */
    public List<RoomExit> getRoomExits(Long roomId) {
        List<RoomExit> exits = roomExits.get(roomId);
        if (exits != null) {
            return exits;
        }
        LambdaQueryWrapper<RoomExit> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(RoomExit::getRoomId, roomId);
        exits = roomExitMapper.selectList(wrapper);
        roomExits.put(roomId, exits);
        return exits;
    }

    /**
     * 获取房间出口方向
     */
    public RoomExit getRoomExit(Long roomId, String direction) {
        List<RoomExit> exits = getRoomExits(roomId);
        for (RoomExit exit : exits) {
            if (exit.getDirection().equals(direction)) {
                return exit;
            }
        }
        return null;
    }

    /**
     * 获取房间内NPC
     */
    public List<Npc> getRoomNpcs(Long roomId) {
        List<Npc> npcs = roomNpcs.get(roomId);
        if (npcs != null) {
            return npcs;
        }
        LambdaQueryWrapper<Npc> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Npc::getRoomId, roomId);
        npcs = npcMapper.selectList(wrapper);
        roomNpcs.put(roomId, npcs);
        return npcs;
    }

    /**
     * 获取房间内NPC(按名称)
     */
    public Npc getNpcByName(Long roomId, String name) {
        List<Npc> npcs = getRoomNpcs(roomId);
        for (Npc npc : npcs) {
            if (npc.getName().equals(name) || npc.getName().contains(name)) {
                return npc;
            }
        }
        return null;
    }

    /**
     * 获取房间内物品
     */
    public List<Thing> getRoomThings(Long roomId) {
        return roomThings.getOrDefault(roomId, Collections.emptyList());
    }

    /**
     * 获取房间描述信息
     */
    public String getRoomDescription(Long roomId) {
        Room room = getRoom(roomId);
        if (room == null) {
            return "未知的地方";
        }
        StringBuilder sb = new StringBuilder();
        sb.append(room.getName()).append("\n");
        if (room.getDescription() != null) {
            sb.append(room.getDescription());
        }

        // 显示出口
        List<RoomExit> exits = getRoomExits(roomId);
        if (!exits.isEmpty()) {
            sb.append("\n");
            List<String> visibleExits = new ArrayList<>();
            for (RoomExit exit : exits) {
                if (exit.getIsHidden() == null || exit.getIsHidden() == 0) {
                    visibleExits.add(exit.getDirection());
                }
            }
            if (!visibleExits.isEmpty()) {
                sb.append("    这里的出口有: ").append(String.join("、", visibleExits)).append("。");
            }
        }

        return sb.toString();
    }

    /**
     * 玩家移动到指定方向
     * @return 目标房间ID, null表示无法移动
     */
    public Long moveActorToDirection(Long roomId, String direction) {
        RoomExit exit = getRoomExit(roomId, direction);
        if (exit == null) {
            return null;
        }
        return exit.getTargetRoomId();
    }

    /**
     * 释放不活跃的房间
     */
    public void releaseInactiveRooms(Set<Long> activeRoomIds) {
        Iterator<Map.Entry<Long, Room>> it = activeRooms.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Long, Room> entry = it.next();
            if (!activeRoomIds.contains(entry.getKey())) {
                it.remove();
                roomExits.remove(entry.getKey());
                roomNpcs.remove(entry.getKey());
                roomThings.remove(entry.getKey());
                redisTemplate.delete(ROOM_CACHE_KEY + entry.getKey());
                log.debug("释放不活跃房间: {}", entry.getKey());
            }
        }
    }

    /**
     * 刷新房间NPC
     */
    public void refreshRoomNpcs(Long roomId) {
        roomNpcs.remove(roomId);
        LambdaQueryWrapper<Npc> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Npc::getRoomId, roomId);
        roomNpcs.put(roomId, npcMapper.selectList(wrapper));
    }
}
