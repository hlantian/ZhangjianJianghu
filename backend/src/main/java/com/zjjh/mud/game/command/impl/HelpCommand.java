package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

import java.util.Map;

@Component
public class HelpCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "help";
    }

    @Override
    public String getDescription() {
        return "查看可用命令列表";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        StringBuilder sb = new StringBuilder();
        sb.append("===== 仗剑江湖命令列表 =====\n\n");

        sb.append("【移动】\n");
        sb.append("  go <方向>    - 前往指定方向(东/南/西/北/上/下)\n");
        sb.append("  move <x> <y> - 在房间内移动\n");
        sb.append("  look [目标]  - 查看环境或目标\n");
        sb.append("\n");

        sb.append("【聊天】\n");
        sb.append("  say <消息>   - 房间内说话\n");
        sb.append("  chat <消息>  - 公共频道\n");
        sb.append("  rumor <消息> - 谣言频道\n");
        sb.append("  newbie <消息>- 新手频道\n");
        sb.append("  party <消息> - 门派频道\n");
        sb.append("  tell <名字> <消息> - 密谈\n");
        sb.append("\n");

        sb.append("【状态】\n");
        sb.append("  hp           - 查看气血状态\n");
        sb.append("  score        - 查看人物状态\n");
        sb.append("  skills       - 查看武功\n");
        sb.append("  inventory    - 查看物品\n");
        sb.append("  who          - 查看在线玩家\n");
        sb.append("\n");

        sb.append("【物品】\n");
        sb.append("  get <物品>   - 拾取物品\n");
        sb.append("  drop <物品>  - 丢弃物品\n");
        sb.append("  give <名字> <物品> - 给予物品\n");
        sb.append("  wield <武器> - 装备武器\n");
        sb.append("  unwield      - 卸下武器\n");
        sb.append("  wear <防具>  - 穿上防具\n");
        sb.append("  unwear       - 脱下防具\n");
        sb.append("\n");

        sb.append("【武功】\n");
        sb.append("  bai <师父>   - 拜师\n");
        sb.append("  xue <武功>   - 学武功\n");
        sb.append("  lian <武功>  - 练习武功\n");
        sb.append("  enable <武功>- 启用武功\n");
        sb.append("  fangqi <武功>- 放弃武功\n");
        sb.append("\n");

        sb.append("【战斗】\n");
        sb.append("  fight <名字> - 较量武功\n");
        sb.append("  kill <名字>  - 对杀\n");
        sb.append("  hit <名字>   - 强行攻击\n");
        sb.append("  touxi <名字> - 偷袭\n");
        sb.append("  halt         - 停止战斗\n");
        sb.append("\n");

        sb.append("【生活】\n");
        sb.append("  sleep        - 睡觉\n");
        sb.append("  sit          - 坐下\n");
        sb.append("  eat <食物>   - 吃东西\n");
        sb.append("  drink        - 喝水\n");
        sb.append("  quit         - 退出游戏\n");
        sb.append("  wimpy <系数> - 设置逃跑系数\n");
        sb.append("  nick <绰号>  - 设置绰号\n");
        sb.append("\n");

        sb.append("【快捷】\n");
        sb.append("  n/s/e/w/u/d  - 方向快捷\n");
        sb.append("  l            - 等同 look\n");
        sb.append("  i            - 等同 inventory\n");
        sb.append("  '消息        - 等同 say\n");

        engine.getMessageService().sendToPlayer(player.getId(), GameMessage.info(sb.toString()));
    }
}
