package com.zjjh.mud.datamigration;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zjjh.mud.entity.*;
import com.zjjh.mud.mapper.*;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.nio.file.*;
import java.util.*;
import java.util.stream.Stream;

/**
 * 数据迁移服务 - 从原C++项目.profile文件导入数据到MySQL
 */
@Slf4j
@Service
@RequiredArgsConstructor
public class DataMigrationService {

    private final RoomMapper roomMapper;
    private final RoomExitMapper roomExitMapper;
    private final NpcMapper npcMapper;
    private final ThingMapper thingMapper;

    @Value("${game.data-path:e:/ZhangjianJianghu/home/mud/data}")
    private String dataPath;

    private final ProfileParser parser = new ProfileParser();

    // 房间路径 -> 房间ID 映射
    private final Map<String, Long> roomPathMap = new HashMap<>();

    // 物品名 -> 物品ID 映射
    private final Map<String, Long> thingNameMap = new HashMap<>();

    /**
     * 迁移所有数据
     */
    public void migrateAll() {
        log.info("========== 开始数据迁移 ==========");
        long start = System.currentTimeMillis();

        int roomsCount = migrateRooms();
        int thingsCount = migrateThings();
        int npcsCount = migrateNpcs();
        int exitsCount = migrateRoomExits();

        log.info("========== 数据迁移完成: 房间={}, 物品={}, NPC={}, 出口={}, 耗时={}ms ==========",
                roomsCount, thingsCount, npcsCount, exitsCount, System.currentTimeMillis() - start);
    }

    /**
     * 迁移房间数据
     */
    public int migrateRooms() {
        Path roomDir = Paths.get(dataPath, "room");
        if (!Files.exists(roomDir)) {
            log.warn("房间数据目录不存在: {}", roomDir);
            return 0;
        }

        int count = 0;
        try (Stream<Path> paths = Files.walk(roomDir)) {
            var profileFiles = paths
                    .filter(p -> p.toString().endsWith(".profile"))
                    .filter(p -> !p.getFileName().toString().equals("a.profile"))
                    .filter(p -> !p.getFileName().toString().equals("defaultroom.profile"))
                    .filter(p -> !p.getFileName().toString().equals("loadroom.profile"))
                    .toList();

            log.info("发现 {} 个房间文件", profileFiles.size());

            for (Path file : profileFiles) {
                try {
                    ProfileParser.ParsedProfile profile = parser.parse(file);
                    if (profile == null) continue;

                    // 构建房间路径
                    String relativePath = roomDir.relativize(file).toString()
                            .replace("\\", "/")
                            .replace(".profile", "");
                    String roomPath = "/room/" + relativePath;

                    // 检查是否已存在
                    LambdaQueryWrapper<Room> wrapper = new LambdaQueryWrapper<>();
                    wrapper.eq(Room::getRoomPath, roomPath);
                    Room existing = roomMapper.selectOne(wrapper);
                    if (existing != null) {
                        roomPathMap.put(roomPath, existing.getId());
                        continue;
                    }

                    // 创建房间
                    Room room = new Room();
                    room.setRoomPath(roomPath);
                    room.setName(profile.getString("名字") != null ? profile.getString("名字") : file.getFileName().toString().replace(".profile", ""));
                    room.setDescription(profile.getString("描述"));
                    room.setRoomType(mapRoomType(profile.getClassName()));
                    room.setForbidFight(profile.getLong("禁止战斗") != null ? 1 : 0);

                    // 解析出口(在YPropertyGroup中的非标准属性)
                    room.setMinX(10);
                    room.setMaxX(365);
                    room.setMinY(90);
                    room.setMaxY(320);

                    roomMapper.insert(room);
                    roomPathMap.put(roomPath, room.getId());
                    count++;

                    // 存储出口信息供后续迁移使用
                    storeExits(profile, room);

                } catch (Exception e) {
                    log.error("迁移房间失败: {}", file, e);
                }
            }
        } catch (IOException e) {
            log.error("遍历房间目录失败", e);
        }

        log.info("成功迁移 {} 个房间", count);
        return count;
    }

    /**
     * 迁移物品数据
     */
    public int migrateThings() {
        Path thingDir = Paths.get(dataPath, "thing");
        if (!Files.exists(thingDir)) {
            log.warn("物品数据目录不存在: {}", thingDir);
            return 0;
        }

        int count = 0;
        try (Stream<Path> paths = Files.walk(thingDir)) {
            var profileFiles = paths
                    .filter(p -> p.toString().endsWith(".profile"))
                    .toList();

            log.info("发现 {} 个物品文件", profileFiles.size());

            for (Path file : profileFiles) {
                try {
                    ProfileParser.ParsedProfile profile = parser.parse(file);
                    if (profile == null) continue;

                    String name = profile.getString("名字");
                    if (name == null || name.isEmpty()) continue;

                    // 检查是否已存在
                    LambdaQueryWrapper<Thing> wrapper = new LambdaQueryWrapper<>();
                    wrapper.eq(Thing::getName, name).last("LIMIT 1");
                    Thing existing = thingMapper.selectOne(wrapper);
                    if (existing != null) {
                        thingNameMap.put(name, existing.getId());
                        continue;
                    }

                    Thing thing = new Thing();
                    thing.setName(name);
                    thing.setFontName(profile.getString("显示名字") != null ? profile.getString("显示名字") : name);
                    thing.setWeight(profile.getLong("重量") != null ? profile.getLong("重量") : 1L);
                    thing.setPrice(profile.getLong("价钱") != null ? profile.getLong("价钱") : 0L);
                    thing.setDescribe(profile.getString("描述"));
                    thing.setQuantifier(profile.getString("量词") != null ? profile.getString("量词") : "个");
                    thing.setThingType(0);
                    thing.setCategory(mapThingCategory(profile));
                    thing.setSubType(mapThingSubType(profile));
                    thing.setAttack(profile.getLong("攻击力") != null ? profile.getLong("攻击力") : 0L);
                    thing.setDefense(profile.getLong("防御力") != null ? profile.getLong("防御力") : 0L);

                    thingMapper.insert(thing);
                    thingNameMap.put(name, thing.getId());
                    count++;

                } catch (Exception e) {
                    log.error("迁移物品失败: {}", file, e);
                }
            }
        } catch (IOException e) {
            log.error("遍历物品目录失败", e);
        }

        log.info("成功迁移 {} 个物品", count);
        return count;
    }

    /**
     * 迁移NPC数据
     */
    public int migrateNpcs() {
        Path npcDir = Paths.get(dataPath, "npc");
        if (!Files.exists(npcDir)) {
            log.warn("NPC数据目录不存在: {}", npcDir);
            return 0;
        }

        int count = 0;
        try (Stream<Path> paths = Files.walk(npcDir)) {
            var profileFiles = paths
                    .filter(p -> p.toString().endsWith(".profile"))
                    .toList();

            log.info("发现 {} 个NPC文件", profileFiles.size());

            for (Path file : profileFiles) {
                try {
                    ProfileParser.ParsedProfile profile = parser.parse(file);
                    if (profile == null) continue;

                    String name = profile.getString("名字");
                    if (name == null || name.isEmpty()) continue;

                    // 检查是否已存在
                    LambdaQueryWrapper<Npc> wrapper = new LambdaQueryWrapper<>();
                    wrapper.eq(Npc::getName, name).last("LIMIT 1");
                    if (npcMapper.selectCount(wrapper) > 0) continue;

                    Npc npc = new Npc();
                    npc.setName(name);
                    npc.setNpcShow(profile.getString("描述"));
                    npc.setPlace(profile.getString("所在位置"));
                    npc.setSchool(profile.getString("门派"));
                    npc.setAllowPrentice(profile.getLong("收徒") != null ? 1 : 0);
                    npc.setAnswerForAgreePrentice(profile.getString("同意拜师的回答"));
                    npc.setProvideQuest(profile.getLong("发任务") != null ? 1 : 0);
                    npc.setNeedPate(profile.getLong("需要首级") != null ? 1 : 0);
                    npc.setNeedKillBySelf(profile.getLong("需亲自杀") != null ? 1 : 0);
                    npc.setNeedGeBySelf(profile.getLong("需亲自割") != null ? 1 : 0);
                    npc.setUniteKill(profile.getLong("联合协防") != null ? 1 : 0);
                    npc.setPlayerSayWhenGiveup(profile.getString("玩家放弃时说话"));
                    npc.setNpcSayWhenNoQuest(profile.getString("无任务说话"));
                    npc.setNpcSayWhenGiveup(profile.getString("被放弃任务说话"));
                    npc.setNpcSayWhenBeGive(profile.getString("被给时说话"));
                    npc.setNpcSayWhenEndQuest(profile.getString("被完成任务说话"));
                    npc.setAppraiseName(profile.getString("评价名"));
                    npc.setTitle(profile.getString("头衔"));
                    npc.setNick(profile.getString("绰号"));

                    // 战斗属性
                    npc.setBody(profile.getLong("气血") != null ? profile.getLong("气血") : 100L);
                    npc.setMaxBody(profile.getLong("最大气血") != null ? profile.getLong("最大气血") : 100L);
                    npc.setEnergy(profile.getLong("精力") != null ? profile.getLong("精力") : 100L);
                    npc.setMaxEnergy(profile.getLong("最大精力") != null ? profile.getLong("最大精力") : 100L);
                    npc.setInternalForce(profile.getLong("内力") != null ? profile.getLong("内力") : 0L);
                    npc.setMaxInternalForce(profile.getLong("最大内力") != null ? profile.getLong("最大内力") : 0L);
                    npc.setInhereAttack(profile.getLong("固定攻击力") != null ? profile.getLong("固定攻击力") : 150L);
                    npc.setInhereDefense(profile.getLong("固定防御力") != null ? profile.getLong("固定防御力") : 150L);
                    npc.setExperience(profile.getLong("经验") != null ? profile.getLong("经验") : 0L);
                    npc.setLevel(profile.getLong("等级") != null ? profile.getLong("等级") : 20L);
                    npc.setIconNo(profile.getString("头像"));
                    npc.setSex(profile.getString("性别") != null ? profile.getString("性别") : "m");
                    npc.setAge(profile.getLong("年龄") != null ? profile.getLong("年龄").intValue() : 30);
                    npc.setAllSkillsList(profile.getString("所会技能"));
                    npc.setNpcType(mapNpcType(profile.getClassName()));
                    npc.setWeaponName(profile.getString("武器名称") != null ? profile.getString("武器名称") : "");
                    npc.setWeaponType(profile.getString("武器类型") != null ? profile.getString("武器类型") : "");
                    npc.setClothName(profile.getString("衣服名称") != null ? profile.getString("衣服名称") : "");
                    npc.setNotDead(0);
                    npc.setBeKillTimes(0L);

                    npcMapper.insert(npc);
                    count++;

                } catch (Exception e) {
                    log.error("迁移NPC失败: {}", file, e);
                }
            }
        } catch (IOException e) {
            log.error("遍历NPC目录失败", e);
        }

        log.info("成功迁移 {} 个NPC", count);
        return count;
    }

    /**
     * 迁移房间出口
     */
    public int migrateRoomExits() {
        // 这里需要之前存储的出口信息
        // 简化: 在migrateRooms中已存储, 现在解析路径
        int count = 0;
        for (Map.Entry<String, List<String[]>> entry : pendingExits.entrySet()) {
            Long roomId = roomPathMap.get(entry.getKey());
            if (roomId == null) continue;

            for (String[] exit : entry.getValue()) {
                String direction = exit[0];
                String targetPath = exit[1];
                Long targetId = roomPathMap.get(targetPath);
                if (targetId == null) continue;

                // 检查是否已存在
                LambdaQueryWrapper<RoomExit> wrapper = new LambdaQueryWrapper<>();
                wrapper.eq(RoomExit::getRoomId, roomId)
                       .eq(RoomExit::getDirection, direction);
                if (roomExitMapper.selectCount(wrapper) > 0) continue;

                RoomExit roomExit = new RoomExit();
                roomExit.setRoomId(roomId);
                roomExit.setDirection(direction);
                roomExit.setTargetRoomId(targetId);
                roomExit.setIsHidden(0);
                roomExitMapper.insert(roomExit);
                count++;
            }
        }
        pendingExits.clear();
        log.info("成功迁移 {} 个房间出口", count);
        return count;
    }

    // 待处理的出口: roomPath -> List<[direction, targetPath]>
    private final Map<String, List<String[]>> pendingExits = new HashMap<>();

    private void storeExits(ProfileParser.ParsedProfile profile, Room room) {
        Map<String, Map<String, String>> sections = profile.getSections();
        Map<String, String> props = sections.get("YPropertyGroup");
        if (props == null) return;

        List<String[]> exits = new ArrayList<>();
        // 出口的key就是方向名, value是目标房间路径
        // 已知的属性key: 名字, 描述, 禁止战斗, etc.
        Set<String> knownKeys = Set.of("名字", "描述", "禁止战斗", "老板名字", "饮食消耗",
                "刷新时间间隔", "销毁列表", "人物退出列表", "收徒", "发任务",
                "同意拜师的回答", "需要首级", "需亲自杀", "需亲自割", "联合协防",
                "玩家放弃时说话", "无任务说话", "被放弃任务说话", "被给时说话",
                "被完成任务说话", "评价名", "头衔", "绰号", "气血", "最大气血",
                "精力", "最大精力", "内力", "最大内力", "固定攻击力", "固定防御力",
                "经验", "等级", "头像", "性别", "年龄", "所会技能", "武器名称",
                "武器类型", "衣服名称", "死亡方式", "不死", "状态", "战斗间隔",
                "晕倒时间", "对手", "杀死自己", "被杀次数", "所有敌人列表",
                "师父的名字", "辈分", "跟随的人", "前进方向", "跟随", "重量",
                "显示名字", "价钱", "量词", "攻击力", "防御力", "附加攻击力",
                "附加防御力", "容貌", "福缘");

        for (Map.Entry<String, String> entry : props.entrySet()) {
            String key = entry.getKey();
            String value = entry.getValue();
            if (!knownKeys.contains(key) && value != null && value.startsWith("/room/")) {
                // 这是一个出口
                exits.add(new String[]{key, value});
            }
        }

        if (!exits.isEmpty()) {
            pendingExits.put(room.getRoomPath(), exits);
        }
    }

    private String mapRoomType(String className) {
        if (className == null) return "normal";
        return switch (className) {
            case "YBankRoom" -> "bank";
            case "YPawnRoom" -> "pawn";
            case "YCookRoom" -> "cook";
            case "YRetiringRoom" -> "retiring";
            case "YWorkRoom" -> "work";
            case "YYelianRoom" -> "yelian";
            case "YLiandanRoom" -> "liandan";
            case "YNewPlayerRoom" -> "newplayer";
            case "YCollectRoom" -> "collect";
            case "YJollityRoom" -> "jollity";
            case "YLingwuRoom" -> "lingwu";
            case "YJailRoom" -> "jail";
            case "YMarryRoom" -> "marry";
            case "YDoorRoom" -> "door";
            case "YHideDoorRoom" -> "hiddendoor";
            case "YLoadRoom" -> "load";
            case "YCangkuRoom" -> "cangku";
            default -> "normal";
        };
    }

    private String mapNpcType(String className) {
        if (className == null) return "normal";
        return switch (className) {
            case "YTeacherNPC" -> "teacher";
            case "YMarryNPC" -> "marry";
            case "YMoneyNPC" -> "money";
            case "YBetrayNPC" -> "betray";
            case "YOfferRewardNPC" -> "offerreward";
            case "YSpecialNPC" -> "special";
            default -> "normal";
        };
    }

    private String mapThingCategory(ProfileParser.ParsedProfile profile) {
        String name = profile.getString("名字");
        if (name == null) return "other";
        if (name.contains("剑") || name.contains("刀") || name.contains("棍") ||
            name.contains("鞭") || name.contains("枪") || name.contains("杖") ||
            name.contains("匕首")) return "weapon";
        if (name.contains("衣") || name.contains("袍") || name.contains("甲") ||
            name.contains("帽") || name.contains("靴") || name.contains("鞋") ||
            name.contains("戒指") || name.contains("项链") || name.contains("手镯")) return "armor";
        if (name.contains("丹") || name.contains("药") || name.contains("丸")) return "medicine";
        if (name.contains("谱") || name.contains("书") || name.contains("经")) return "book";
        if (name.contains("矿") || name.contains("石") || name.contains("铁") ||
            name.contains("金") || name.contains("木")) return "material";
        return "other";
    }

    private String mapThingSubType(ProfileParser.ParsedProfile profile) {
        String name = profile.getString("名字");
        if (name == null) return "";
        if (name.contains("剑")) return "sword";
        if (name.contains("刀")) return "saber";
        if (name.contains("拳") || name.contains("掌")) return "fist";
        if (name.contains("帽")) return "hat";
        if (name.contains("靴") || name.contains("鞋")) return "shoe";
        if (name.contains("戒指")) return "ring";
        if (name.contains("项链")) return "necklace";
        if (name.contains("手镯")) return "bangle";
        if (name.contains("甲") || name.contains("衣") || name.contains("袍")) return "armor";
        return "";
    }
}
