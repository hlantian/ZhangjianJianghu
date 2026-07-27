package com.zjjh.mud.game.timer;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.engine.GameEngine;
import com.zjjh.mud.game.engine.PlayerManager;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.util.Collection;

@Slf4j
@Component
@RequiredArgsConstructor
public class GameTimerTasks {

    private final GameEngine gameEngine;

    @Value("${game.body-recovery:30000}")
    private long bodyRecoveryInterval;

    /**
     * 玩家气血/精力/内力恢复 - 每30秒
     */
    @Scheduled(fixedDelay = 30000)
    public void playerRecovery() {
        if (!gameEngine.isRunning()) return;

        PlayerManager pm = gameEngine.getPlayerManager();
        for (Player player : pm.getAllOnlinePlayers()) {
            boolean changed = false;

            // 气血恢复(需有食物和饮水)
            if (player.getBody() < player.getMaxBody() && player.getFood() > 0 && player.getDrink() > 0) {
                long recover = Math.max(1, player.getMaxBody() / 50);
                player.setBody(Math.min(player.getMaxBody(), player.getBody() + recover));
                changed = true;
            }

            // 精力恢复
            if (player.getEnergy() < player.getMaxEnergy()) {
                long recover = Math.max(1, player.getMaxEnergy() / 30);
                player.setEnergy(Math.min(player.getMaxEnergy(), player.getEnergy() + recover));
                changed = true;
            }

            // 内力恢复
            if (player.getInternalForce() < player.getMaxInternalForce()) {
                long recover = Math.max(1, player.getMaxInternalForce() / 40);
                player.setInternalForce(Math.min(player.getMaxInternalForce(), player.getInternalForce() + recover));
                changed = true;
            }

            if (changed) {
                pm.updateOnlinePlayer(player);
                // 推送HP更新
                gameEngine.getMessageService().sendHpUpdate(
                        player.getId(),
                        player.getBody(), player.getMaxBody(),
                        player.getEnergy(), player.getMaxEnergy(),
                        player.getInternalForce(), player.getMaxInternalForce(),
                        player.getFood(), player.getMaxFood(),
                        player.getDrink(), player.getMaxDrink()
                );
            }
        }
    }

    /**
     * 食物饮水消耗 - 每60秒
     */
    @Scheduled(fixedDelay = 60000)
    public void foodConsume() {
        if (!gameEngine.isRunning()) return;

        PlayerManager pm = gameEngine.getPlayerManager();
        for (Player player : pm.getAllOnlinePlayers()) {
            boolean changed = false;

            // 食物消耗
            if (player.getFood() > 0) {
                player.setFood(Math.max(0, player.getFood() - 2));
                changed = true;
            }
            // 饮水消耗
            if (player.getDrink() > 0) {
                player.setDrink(Math.max(0, player.getDrink() - 2));
                changed = true;
            }

            if (changed) {
                pm.updateOnlinePlayer(player);
                // 食物/饮水为0时提示
                if (player.getFood() == 0) {
                    gameEngine.getMessageService().sendToPlayer(player.getId(),
                            "你饿得头晕眼花，快找点东西吃吧！");
                }
                if (player.getDrink() == 0) {
                    gameEngine.getMessageService().sendToPlayer(player.getId(),
                            "你渴得口干舌燥，快找点水喝吧！");
                }
            }
        }
    }

    /**
     * 空闲检测 - 每5分钟
     */
    @Scheduled(fixedDelay = 300000)
    public void idleCheck() {
        if (!gameEngine.isRunning()) return;

        PlayerManager pm = gameEngine.getPlayerManager();
        long now = System.currentTimeMillis();
        Collection<Player> all = pm.getAllOnlinePlayers();

        for (Player player : all) {
            // 增加在线时间
            player.setOnlineTime((player.getOnlineTime() != null ? player.getOnlineTime() : 0) + 300000);

            // 检查空闲时间
            if (player.getFreeTime() != null && player.getFreeTime() > 900000) { // 15分钟
                log.info("玩家空闲超时离线: {}", player.getName());
                pm.playerOffline(player.getId());
                gameEngine.getMessageService().sendToPlayer(player.getId(),
                        "你因长时间空闲而被系统请下线了。");
            }
        }
    }

    /**
     * 年龄增长 - 每24小时
     */
    @Scheduled(fixedDelay = 86400000)
    public void ageGrowth() {
        if (!gameEngine.isRunning()) return;

        PlayerManager pm = gameEngine.getPlayerManager();
        for (Player player : pm.getAllOnlinePlayers()) {
            if (player.getAge() != null) {
                player.setAge(player.getAge() + 1);
                pm.updateOnlinePlayer(player);
                gameEngine.getMessageService().sendToPlayer(player.getId(),
                        "你又长大了一岁，现在 " + player.getAge() + " 岁了。");
            }
        }
    }

    /**
     * 房间刷新 - 每15分钟
     */
    @Scheduled(fixedDelay = 900000)
    public void roomRefresh() {
        if (!gameEngine.isRunning()) return;

        // 收集所有活跃房间
        java.util.Set<Long> activeRooms = new java.util.HashSet<>();
        for (Player player : gameEngine.getPlayerManager().getAllOnlinePlayers()) {
            if (player.getRoomId() != null) {
                activeRooms.add(player.getRoomId());
            }
        }

        // 释放不活跃的房间
        gameEngine.getRoomManager().releaseInactiveRooms(activeRooms);
        log.debug("房间刷新完成，活跃房间数: {}", activeRooms.size());
    }
}
