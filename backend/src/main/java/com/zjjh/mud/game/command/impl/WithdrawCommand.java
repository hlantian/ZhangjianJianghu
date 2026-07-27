package com.zjjh.mud.game.command.impl;

import com.zjjh.mud.entity.Player;
import com.zjjh.mud.game.GameMessage;
import com.zjjh.mud.game.command.CommandHandler;
import com.zjjh.mud.game.engine.GameEngine;
import org.springframework.stereotype.Component;

@Component
public class WithdrawCommand implements CommandHandler {

    @Override
    public String getCommandName() {
        return "withdraw";
    }

    @Override
    public String getDescription() {
        return "从银行取款 (withdraw <金额>)";
    }

    @Override
    public void handle(GameEngine engine, Player player, String args) {
        if (args == null || args.isEmpty()) {
            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你目前的存款为" + (player.getDeposit() != null ? player.getDeposit() : 0) + "两白银。"));
            return;
        }

        try {
            long amount = Long.parseLong(args.trim());
            long deposit = player.getDeposit() != null ? player.getDeposit() : 0;

            if (amount <= 0) {
                engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("取款金额必须大于0。"));
                return;
            }

            if (amount > deposit) {
                engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("你的存款不够。"));
                return;
            }

            player.setDeposit(deposit - amount);
            engine.getPlayerManager().updateOnlinePlayer(player);

            engine.getMessageService().sendToPlayer(player.getId(),
                    GameMessage.info("你取出了" + amount + "两白银，剩余存款" + player.getDeposit() + "两。"));
        } catch (NumberFormatException e) {
            engine.getMessageService().sendToPlayer(player.getId(), GameMessage.error("请输入正确的金额。"));
        }
    }
}
