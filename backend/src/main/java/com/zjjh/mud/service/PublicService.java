package com.zjjh.mud.service;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.mapper.PlayerMapper;
import lombok.RequiredArgsConstructor;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
@RequiredArgsConstructor
public class PublicService {

    private final PlayerMapper playerMapper;
    private final RedisTemplate<String, Object> redisTemplate;

    private static final String ONLINE_KEY = "player:online";

    public int getOnlineCount() {
        Set<String> keys = redisTemplate.keys(ONLINE_KEY + ":*");
        return keys != null ? keys.size() : 0;
    }

    public List<Map<String, Object>> getExpRankings() {
        LambdaQueryWrapper<Player> wrapper = new LambdaQueryWrapper<>();
        wrapper.orderByDesc(Player::getExperience).last("LIMIT 100");
        List<Player> players = playerMapper.selectList(wrapper);

        List<Map<String, Object>> result = new ArrayList<>();
        for (int i = 0; i < players.size(); i++) {
            Player p = players.get(i);
            Map<String, Object> item = new HashMap<>();
            item.put("rank", i + 1);
            item.put("name", p.getName());
            item.put("experience", p.getExperience());
            item.put("level", p.getPlayerLevel());
            result.add(item);
        }
        return result;
    }

    public List<Map<String, Object>> getMoneyRankings() {
        LambdaQueryWrapper<Player> wrapper = new LambdaQueryWrapper<>();
        wrapper.orderByDesc(Player::getDeposit).last("LIMIT 100");
        List<Player> players = playerMapper.selectList(wrapper);

        List<Map<String, Object>> result = new ArrayList<>();
        for (int i = 0; i < players.size(); i++) {
            Player p = players.get(i);
            Map<String, Object> item = new HashMap<>();
            item.put("rank", i + 1);
            item.put("name", p.getName());
            item.put("deposit", p.getDeposit());
            result.add(item);
        }
        return result;
    }
}
