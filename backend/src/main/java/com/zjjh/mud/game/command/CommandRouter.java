package com.zjjh.mud.game.command;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.engine.GameEngine;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Component;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Slf4j
@Component
@RequiredArgsConstructor
public class CommandRouter {

    private final List<CommandHandler> handlers;
    private final Map<String, CommandHandler> commandMap = new HashMap<>();
    private final Map<String, String> aliasMap = new HashMap<>();

    // 命令别名
    {
        aliasMap.put("l", "look");
        aliasMap.put("n", "go");
        aliasMap.put("s", "go");
        aliasMap.put("e", "go");
        aliasMap.put("w", "go");
        aliasMap.put("u", "go");
        aliasMap.put("d", "go");
        aliasMap.put("i", "inventory");
        aliasMap.put("hp", "hp");
        aliasMap.put("sc", "score");
        aliasMap.put("sk", "skills");
        aliasMap.put("q", "quest");
        aliasMap.put("gq", "giveup");
        aliasMap.put("'", "say");
    }

    public void init() {
        for (CommandHandler handler : handlers) {
            commandMap.put(handler.getCommandName(), handler);
            log.debug("注册命令: {}", handler.getCommandName());
        }
        log.info("命令系统初始化完成，已注册 {} 个命令", commandMap.size());
    }

    /**
     * 处理玩家命令
     */
    public void processCommand(GameEngine engine, Player player, String rawCommand) {
        if (rawCommand == null || rawCommand.trim().isEmpty()) {
            return;
        }

        rawCommand = rawCommand.trim();

        // 处理别名
        String commandName;
        String args;

        // 检查是否是说话快捷方式
        if (rawCommand.startsWith("'")) {
            commandName = "say";
            args = rawCommand.substring(1).trim();
        } else if (rawCommand.startsWith("/")) {
            commandName = rawCommand.substring(1).trim();
            int spaceIdx = commandName.indexOf(' ');
            if (spaceIdx > 0) {
                args = commandName.substring(spaceIdx + 1).trim();
                commandName = commandName.substring(0, spaceIdx);
            } else {
                args = "";
            }
        } else {
            int spaceIdx = rawCommand.indexOf(' ');
            if (spaceIdx > 0) {
                commandName = rawCommand.substring(0, spaceIdx).toLowerCase();
                args = rawCommand.substring(spaceIdx + 1).trim();
            } else {
                commandName = rawCommand.toLowerCase();
                args = "";
            }
        }

        // 应用别名
        if (aliasMap.containsKey(commandName)) {
            String aliasTarget = aliasMap.get(commandName);
            if (aliasTarget.equals("go")) {
                // 方向快捷: n/s/e/w/u/d
                args = commandName;
                commandName = "go";
            } else {
                commandName = aliasTarget;
            }
        }

        // 查找并执行命令
        CommandHandler handler = commandMap.get(commandName);
        if (handler == null) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    "未知命令: " + commandName + "。输入 help 查看可用命令。");
            return;
        }

        try {
            handler.handle(engine, player, args);
        } catch (Exception e) {
            log.error("命令执行异常: cmd={}, player={}", commandName, player.getName(), e);
            engine.getMessageService().sendToPlayer(player.getId(),
                    "命令执行出错: " + e.getMessage());
        }
    }

    public Map<String, CommandHandler> getCommandMap() {
        return commandMap;
    }
}
