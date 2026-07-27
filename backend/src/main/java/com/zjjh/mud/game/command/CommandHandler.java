package com.zjjh.mud.game.command;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.engine.GameEngine;

import java.util.List;

/**
 * 命令处理器接口
 */
public interface CommandHandler {
    /**
     * 处理命令
     * @param engine 游戏引擎
     * @param player 玩家
     * @param args 命令参数
     */
    void handle(GameEngine engine, Player player, String args);

    /**
     * 获取命令名称
     */
    String getCommandName();

    /**
     * 获取命令描述
     */
    default String getDescription() {
        return "";
    }
}
