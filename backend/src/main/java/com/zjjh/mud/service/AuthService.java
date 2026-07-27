package com.zjjh.mud.service;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.common.BusinessException;
import com.zjjh.mud.config.JwtUtil;
import com.zjjh.mud.dto.*;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.entity.User;
import com.zjjh.mud.mapper.PlayerMapper;
import com.zjjh.mud.mapper.UserMapper;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.concurrent.TimeUnit;

@Slf4j
@Service
@RequiredArgsConstructor
public class AuthService {

    private final UserMapper userMapper;
    private final PlayerMapper playerMapper;
    private final JwtUtil jwtUtil;
    private final RedisTemplate<String, Object> redisTemplate;

    private static final BCryptPasswordEncoder passwordEncoder = new BCryptPasswordEncoder();
    private static final String PLAYER_REDIS_KEY = "player:online:";

    @Transactional
    public LoginResponse register(RegisterRequest request) {
        // 检查用户名是否已存在
        LambdaQueryWrapper<User> userWrapper = new LambdaQueryWrapper<>();
        userWrapper.eq(User::getUsername, request.getUsername());
        if (userMapper.selectCount(userWrapper) > 0) {
            throw BusinessException.of(400, "用户名已存在");
        }

        // 检查角色名是否已存在
        LambdaQueryWrapper<Player> playerWrapper = new LambdaQueryWrapper<>();
        playerWrapper.eq(Player::getName, request.getPlayerName());
        if (playerMapper.selectCount(playerWrapper) > 0) {
            throw BusinessException.of(400, "角色名已存在");
        }

        // 创建用户
        User user = new User();
        user.setUsername(request.getUsername());
        user.setPassword(passwordEncoder.encode(request.getPassword()));
        user.setSex(request.getSex());
        user.setStatus(1);
        user.setLastLoginTime(LocalDateTime.now());
        userMapper.insert(user);

        // 创建玩家角色
        Player player = createNewPlayer(user.getId(), request.getPlayerName(), request.getSex());
        playerMapper.insert(player);

        // 生成token
        String token = jwtUtil.generateToken(user.getId(), user.getUsername());

        LoginResponse response = new LoginResponse();
        response.setToken(token);
        response.setUserId(user.getId());
        response.setUsername(user.getUsername());
        response.setPlayerId(player.getId());
        response.setPlayerName(player.getName());
        response.setSex(player.getSex());
        response.setIsNewPlayer(true);

        return response;
    }

    public LoginResponse login(LoginRequest request) {
        // 查找用户
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(User::getUsername, request.getUsername());
        User user = userMapper.selectOne(wrapper);

        if (user == null) {
            throw BusinessException.of(400, "用户名或密码不正确");
        }

        if (!passwordEncoder.matches(request.getPassword(), user.getPassword())) {
            throw BusinessException.of(400, "用户名或密码不正确");
        }

        if (user.getStatus() != 1) {
            throw BusinessException.of(403, "账号已被禁用");
        }

        // 更新最后登录时间
        user.setLastLoginTime(LocalDateTime.now());
        userMapper.updateById(user);

        // 查找玩家角色
        LambdaQueryWrapper<Player> playerWrapper = new LambdaQueryWrapper<>();
        playerWrapper.eq(Player::getUserId, user.getId());
        Player player = playerMapper.selectOne(playerWrapper);

        // 生成token
        String token = jwtUtil.generateToken(user.getId(), user.getUsername());

        LoginResponse response = new LoginResponse();
        response.setToken(token);
        response.setUserId(user.getId());
        response.setUsername(user.getUsername());
        response.setIsNewPlayer(false);

        if (player != null) {
            response.setPlayerId(player.getId());
            response.setPlayerName(player.getName());
            response.setSex(player.getSex());

            // 将玩家数据缓存到Redis
            redisTemplate.opsForValue().set(
                    PLAYER_REDIS_KEY + player.getId(),
                    player,
                    jwtUtil.getExpiration(),
                    TimeUnit.MILLISECONDS
            );
        }

        return response;
    }

    @Transactional
    public void changePassword(ChangePasswordRequest request) {
        LambdaQueryWrapper<User> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(User::getUsername, request.getUsername());
        User user = userMapper.selectOne(wrapper);

        if (user == null) {
            throw BusinessException.of(400, "用户不存在");
        }

        if (!passwordEncoder.matches(request.getOldPassword(), user.getPassword())) {
            throw BusinessException.of(400, "旧密码不正确");
        }

        user.setPassword(passwordEncoder.encode(request.getNewPassword()));
        userMapper.updateById(user);
    }

    public Player getPlayerByUserId(Long userId) {
        LambdaQueryWrapper<Player> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(Player::getUserId, userId);
        return playerMapper.selectOne(wrapper);
    }

    public Player getPlayerById(Long playerId) {
        // 先从Redis缓存获取
        Object cached = redisTemplate.opsForValue().get(PLAYER_REDIS_KEY + playerId);
        if (cached instanceof Player) {
            return (Player) cached;
        }
        // 从数据库获取
        Player player = playerMapper.selectById(playerId);
        if (player != null) {
            redisTemplate.opsForValue().set(
                    PLAYER_REDIS_KEY + playerId,
                    player,
                    jwtUtil.getExpiration(),
                    TimeUnit.MILLISECONDS
            );
        }
        return player;
    }

    public void updatePlayer(Player player) {
        playerMapper.updateById(player);
        redisTemplate.opsForValue().set(
                PLAYER_REDIS_KEY + player.getId(),
                player,
                jwtUtil.getExpiration(),
                TimeUnit.MILLISECONDS
        );
    }

    private Player createNewPlayer(Long userId, String playerName, String sex) {
        Player player = new Player();
        player.setUserId(userId);
        player.setName(playerName);
        player.setSex(sex);
        player.setAge(14);

        // 气血
        player.setBody(100L);
        player.setMaxBody(100L);
        player.setEnergy(100L);
        player.setMaxEnergy(100L);
        player.setAddMaxEnergy(0L);

        // 内力
        player.setInternalForce(0L);
        player.setMaxInternalForce(0L);
        player.setAddMaxInternalForce(0L);

        // 经验
        player.setExperience(0L);
        player.setPotential(0L);
        player.setGoodnessCount(0L);

        // 食物饮水
        player.setFood(150L);
        player.setMaxFood(200L);
        player.setDrink(150L);
        player.setMaxDrink(200L);

        // 先天属性(总100点, 各15初始)
        player.setBeginArm(15L);
        player.setBeginLearn(15L);
        player.setBeginForce(15L);
        player.setBeginDodge(15L);

        // 后天属性
        player.setLastArm(15L);
        player.setLastLearn(15L);
        player.setLastForce(15L);
        player.setLastDodge(15L);

        // 攻击防御
        player.setInhereAttack(player.getBeginArm());
        player.setInhereDefense(0L);
        player.setPowerupAttack(0L);
        player.setAppendAttack(0L);
        player.setForceAttack(0L);
        player.setWeaponAttack(0L);
        player.setPowerupDefense(0L);
        player.setAppendDefense(0L);

        // 负重(臂力的15倍)
        player.setMaxWeight(player.getBeginArm() * 15);
        player.setWeight(0L);
        player.setDeposit(0L);

        // 容貌福缘
        player.setFeature(50L);
        player.setAddFeature(0L);
        player.setLuck(50L);
        player.setAddLuck(0L);

        // 战斗状态
        player.setWimpy(0L);
        player.setFreeTime(0L);
        player.setBusy(0L);
        player.setFaintTime(0L);
        player.setSleepTime(0L);

        // 击杀统计
        player.setKillTimes(0L);
        player.setBeKillTimes(0L);
        player.setPkTimes(0L);
        player.setBePkTimes(0L);
        player.setCityKill(0L);
        player.setGiveThing(0L);

        // 在线统计
        player.setOnlineTime(0L);
        player.setLastOnlineTime(0L);
        player.setPlayerLevel(0L);
        player.setPlayerSleepSkip(0L);
        player.setPlayerRenew(0L);
        player.setNowWork(0L);

        // 频道开关
        player.setCloseChat(0);
        player.setCloseRumor(0);
        player.setCloseNewbie(0);
        player.setCloseParty(0);
        player.setCloseFactionParty(0);

        // 其他
        player.setSchool("");
        player.setTeacherName("");
        player.setSchoolPlace(0L);
        player.setAllSkillsList("");
        player.setWorkSkills("");
        player.setAllEnemyList("");
        player.setQuestList("");
        player.setAllCkList("");
        player.setCkLevel(0L);
        player.setNotDead(0);
        player.setComeIn(0L);
        player.setNoaccept(0);
        player.setWizCloseChat(0);
        player.setPlayCloseChat(0);
        player.setPlaySaySpeed(0L);
        player.setPlayerX(50);
        player.setPlayerY(50);
        player.setIconNo(sex.equals("m") ? "man1" : "weman1");
        player.setNick("");
        player.setTitle("");
        player.setDescribe("");
        player.setStatus("");
        player.setAdversary("");
        player.setFollowYou("");
        player.setYouFollow("");
        player.setWeaponName("");
        player.setWeaponType("");
        player.setClothName("");
        player.setArmor("");
        player.setHat("");
        player.setShoe("");
        player.setFlower("");
        player.setRing("");
        player.setNecklace("");
        player.setBangle("");
        player.setFactionId(null);
        player.setFactionTitle("");
        player.setIsFactionOwner(0);
        player.setPartyValue(0L);
        player.setCourtValue(0L);
        player.setSocietyValue(0L);
        player.setDeathMode("");
        player.setRoomId(null); // 首次登录时分配初始房间

        return player;
    }
}
