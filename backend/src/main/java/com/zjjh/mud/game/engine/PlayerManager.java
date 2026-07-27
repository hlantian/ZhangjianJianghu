package com.zjjh.mud.game.engine;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessageService;
import com.zjjh.mud.service.AuthService;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Component;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

@Slf4j
@Component
@RequiredArgsConstructor
public class PlayerManager {

    private final AuthService authService;
    private final RedisTemplate<String, Object> redisTemplate;
    private final GameMessageService messageService;

    private static final String ONLINE_KEY = "player:online:";

    // 在线玩家: playerId -> Player
    private final Map<Long, Player> onlinePlayers = new ConcurrentHashMap<>();

    // 玩家所在房间: playerId -> roomId
    private final Map<Long, Long> playerRooms = new ConcurrentHashMap<>();

    // 房间内玩家: roomId -> Set<playerId>
    private final Map<Long, Set<Long>> roomPlayers = new ConcurrentHashMap<>();

    /**
     * 玩家上线
     */
    public void playerOnline(Long playerId) {
        Player player = authService.getPlayerById(playerId);
        if (player == null) {
            log.warn("玩家上线失败: 未找到玩家 playerId={}", playerId);
            return;
        }

        onlinePlayers.put(playerId, player);
        redisTemplate.opsForValue().set(ONLINE_KEY + playerId, player.getId());

        // 如果没有房间，分配初始房间
        if (player.getRoomId() == null) {
            player.setRoomId(1L); // 默认初始房间
            authService.updatePlayer(player);
        }

        Long roomId = player.getRoomId();
        playerRooms.put(playerId, roomId);
        roomPlayers.computeIfAbsent(roomId, k -> ConcurrentHashMap.newKeySet()).add(playerId);

        log.info("玩家上线: {} (id={}, room={})", player.getName(), playerId, roomId);
    }

    /**
     * 玩家离线
     */
    public void playerOffline(Long playerId) {
        Player player = onlinePlayers.remove(playerId);
        if (player == null) {
            return;
        }

        Long roomId = playerRooms.remove(playerId);
        if (roomId != null) {
            Set<Long> players = roomPlayers.get(roomId);
            if (players != null) {
                players.remove(playerId);
                if (players.isEmpty()) {
                    roomPlayers.remove(roomId);
                }
            }
        }

        redisTemplate.delete(ONLINE_KEY + playerId);

        // 保存玩家数据
        authService.updatePlayer(player);

        log.info("玩家离线: {} (id={})", player.getName(), playerId);
    }

    /**
     * 获取在线玩家
     */
    public Player getOnlinePlayer(Long playerId) {
        return onlinePlayers.get(playerId);
    }

    /**
     * 更新在线玩家数据
     */
    public void updateOnlinePlayer(Player player) {
        onlinePlayers.put(player.getId(), player);
    }

    /**
     * 获取房间内所有玩家ID
     */
    public Set<Long> getPlayersInRoom(Long roomId) {
        return roomPlayers.getOrDefault(roomId, Collections.emptySet());
    }

    /**
     * 获取房间内所有在线玩家
     */
    public List<Player> getOnlinePlayersInRoom(Long roomId) {
        Set<Long> playerIds = getPlayersInRoom(roomId);
        List<Player> players = new ArrayList<>();
        for (Long pid : playerIds) {
            Player p = onlinePlayers.get(pid);
            if (p != null) {
                players.add(p);
            }
        }
        return players;
    }

    /**
     * 玩家移动到新房间
     */
    public void movePlayerToRoom(Long playerId, Long newRoomId) {
        Player player = onlinePlayers.get(playerId);
        if (player == null) {
            return;
        }

        Long oldRoomId = playerRooms.get(playerId);
        if (oldRoomId != null) {
            Set<Long> players = roomPlayers.get(oldRoomId);
            if (players != null) {
                players.remove(playerId);
                // 通知旧房间玩家离开
                messageService.sendActorLeave(oldRoomId, player.getName());
            }
        }

        player.setRoomId(newRoomId);
        playerRooms.put(playerId, newRoomId);
        roomPlayers.computeIfAbsent(newRoomId, k -> ConcurrentHashMap.newKeySet()).add(playerId);

        // 通知新房间玩家进入
        String displayName = player.getName();
        messageService.sendActorEnter(newRoomId, player.getName(), displayName,
                player.getPlayerX(), player.getPlayerY());

        authService.updatePlayer(player);
    }

    /**
     * 获取在线玩家数量
     */
    public int getOnlineCount() {
        return onlinePlayers.size();
    }

    /**
     * 检查玩家是否在线
     */
    public boolean isOnline(Long playerId) {
        return onlinePlayers.containsKey(playerId);
    }

    /**
     * 获取所有在线玩家
     */
    public Collection<Player> getAllOnlinePlayers() {
        return onlinePlayers.values();
    }
}
