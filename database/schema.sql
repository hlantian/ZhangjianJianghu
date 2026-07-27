-- ============================================
-- 仗剑江湖 数据库建表脚本
-- ============================================

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- 1. 用户账户表
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id`              BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `username`        VARCHAR(50)  NOT NULL COMMENT '用户名',
  `password`        VARCHAR(100) NOT NULL COMMENT '密码(BCrypt加密)',
  `sex`             CHAR(1)      DEFAULT 'm' COMMENT '性别: m-男, f-女',
  `status`          TINYINT      DEFAULT 1 COMMENT '状态: 0-禁用, 1-正常',
  `create_time`     DATETIME     DEFAULT CURRENT_TIMESTAMP COMMENT '注册时间',
  `last_login_time` DATETIME     DEFAULT NULL COMMENT '最后登录时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户账户表';

-- ----------------------------
-- 2. 玩家角色表
-- ----------------------------
DROP TABLE IF EXISTS `players`;
CREATE TABLE `players` (
  `id`                    BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `user_id`               BIGINT       NOT NULL COMMENT '用户ID',
  `name`                  VARCHAR(50)  NOT NULL COMMENT '角色名',
  `nick`                  VARCHAR(100) DEFAULT '' COMMENT '绰号',
  `title`                 VARCHAR(100) DEFAULT '' COMMENT '头衔',
  `describe`              TEXT         COMMENT '个人描述',
  `sex`                   CHAR(1)      DEFAULT 'm' COMMENT '性别',
  `age`                   INT          DEFAULT 14 COMMENT '年龄',
  `icon_no`               VARCHAR(20)  DEFAULT '' COMMENT '头像编号',
  `room_id`               BIGINT       DEFAULT NULL COMMENT '当前房间ID',
  `player_x`              INT          DEFAULT 50 COMMENT '房内X坐标',
  `player_y`              INT          DEFAULT 50 COMMENT '房内Y坐标',
  -- 气血相关
  `body`                  BIGINT       DEFAULT 100 COMMENT '气血',
  `max_body`              BIGINT       DEFAULT 100 COMMENT '最大气血',
  `energy`                BIGINT       DEFAULT 100 COMMENT '精力',
  `max_energy`            BIGINT       DEFAULT 100 COMMENT '最大精力',
  `add_max_energy`        BIGINT       DEFAULT 0 COMMENT '附加最大精力',
  -- 内力相关
  `internal_force`        BIGINT       DEFAULT 0 COMMENT '内力',
  `max_internal_force`    BIGINT       DEFAULT 0 COMMENT '最大内力',
  `add_max_internal_force` BIGINT      DEFAULT 0 COMMENT '附加最大内力',
  -- 经验与潜能
  `experience`            BIGINT       DEFAULT 0 COMMENT '经验',
  `potential`             BIGINT       DEFAULT 0 COMMENT '潜能',
  `goodness_count`        BIGINT       DEFAULT 0 COMMENT '正气值',
  -- 食物饮水
  `food`                  BIGINT       DEFAULT 150 COMMENT '食物',
  `max_food`              BIGINT       DEFAULT 200 COMMENT '最大食物',
  `drink`                 BIGINT       DEFAULT 150 COMMENT '饮水',
  `max_drink`             BIGINT       DEFAULT 200 COMMENT '最大饮水',
  -- 负重与金钱
  `weight`                BIGINT       DEFAULT 0 COMMENT '当前负重',
  `max_weight`            BIGINT       DEFAULT 0 COMMENT '最大负重',
  `deposit`               BIGINT       DEFAULT 0 COMMENT '银行存款',
  -- 先天属性
  `begin_arm`             BIGINT       DEFAULT 15 COMMENT '先天臂力',
  `begin_learn`          BIGINT       DEFAULT 15 COMMENT '先天悟性',
  `begin_force`          BIGINT       DEFAULT 15 COMMENT '先天根骨',
  `begin_dodge`          BIGINT       DEFAULT 15 COMMENT '先天身法',
  -- 后天属性
  `last_arm`              BIGINT       DEFAULT 15 COMMENT '后天臂力',
  `last_learn`           BIGINT       DEFAULT 15 COMMENT '后天悟性',
  `last_force`            BIGINT       DEFAULT 15 COMMENT '后天根骨',
  `last_dodge`            BIGINT       DEFAULT 15 COMMENT '后天身法',
  -- 攻击力
  `inhere_attack`         BIGINT       DEFAULT 0 COMMENT '固定攻击力',
  `powerup_attack`        BIGINT       DEFAULT 0 COMMENT 'powerup攻击力',
  `append_attack`         BIGINT       DEFAULT 0 COMMENT '附加攻击力',
  `force_attack`          BIGINT       DEFAULT 0 COMMENT '加力攻击力',
  `weapon_attack`         BIGINT       DEFAULT 0 COMMENT '武器攻击力',
  -- 防御力
  `inhere_defense`        BIGINT       DEFAULT 0 COMMENT '固定防御力',
  `powerup_defense`       BIGINT       DEFAULT 0 COMMENT 'powerup防御力',
  `append_defense`        BIGINT       DEFAULT 0 COMMENT '附加防御力',
  -- 容貌福缘
  `feature`               BIGINT       DEFAULT 50 COMMENT '容貌',
  `add_feature`           BIGINT       DEFAULT 0 COMMENT '附加容貌值',
  `luck`                  BIGINT       DEFAULT 50 COMMENT '福缘',
  `add_luck`              BIGINT       DEFAULT 0 COMMENT '附加福缘',
  -- 战斗状态
  `wimpy`                 BIGINT       DEFAULT 0 COMMENT '逃跑系数',
  `free_time`             BIGINT       DEFAULT 0 COMMENT '空闲时间',
  `busy`                  BIGINT       DEFAULT 0 COMMENT '繁忙状态',
  `faint_time`            BIGINT       DEFAULT 0 COMMENT '晕倒时间',
  `sleep_time`            BIGINT       DEFAULT 0 COMMENT '睡眠时间',
  -- 击杀统计
  `kill_times`            BIGINT       DEFAULT 0 COMMENT '杀人次数',
  `be_kill_times`         BIGINT       DEFAULT 0 COMMENT '被杀次数',
  `pk_times`              BIGINT       DEFAULT 0 COMMENT 'PK杀玩家次数',
  `be_pk_times`           BIGINT       DEFAULT 0 COMMENT '被PK杀死次数',
  `city_kill`             BIGINT       DEFAULT 0 COMMENT '屠城数',
  `give_thing`            BIGINT       DEFAULT 0 COMMENT '送东西数',
  -- 门派/帮派
  `faction_id`            BIGINT       DEFAULT NULL COMMENT '帮派ID',
  `faction_title`         VARCHAR(100) DEFAULT '' COMMENT '帮派头衔',
  `is_faction_owner`      TINYINT      DEFAULT 0 COMMENT '是否帮主: 0-否, 1-是',
  `party_value`           BIGINT       DEFAULT 0 COMMENT '门派评价',
  `court_value`           BIGINT       DEFAULT 0 COMMENT '朝廷声望',
  `society_value`         BIGINT       DEFAULT 0 COMMENT '江湖声望',
  -- 在线统计
  `online_time`           BIGINT       DEFAULT 0 COMMENT '在线时间(毫秒)',
  `last_online_time`      BIGINT       DEFAULT 0 COMMENT '上次在线时间',
  `player_level`          BIGINT       DEFAULT 0 COMMENT '玩家级别',
  `player_sleep_skip`     BIGINT       DEFAULT 0 COMMENT '睡眠间隔',
  `player_renew`          BIGINT       DEFAULT 0 COMMENT '体力恢复',
  `now_work`              BIGINT       DEFAULT 0 COMMENT '正在劳动',
  -- 频道开关
  `close_chat`            TINYINT      DEFAULT 0 COMMENT '关闭公共频道',
  `close_rumor`           TINYINT      DEFAULT 0 COMMENT '关闭谣言频道',
  `close_newbie`          TINYINT      DEFAULT 0 COMMENT '关闭新手频道',
  `close_party`           TINYINT      DEFAULT 0 COMMENT '关闭门派频道',
  `close_faction_party`   TINYINT      DEFAULT 0 COMMENT '关闭帮派频道',
  -- 位置与状态
  `status`                VARCHAR(100) DEFAULT '' COMMENT '状态描述',
  `adversary`             VARCHAR(100) DEFAULT '' COMMENT '对手名字',
  `follow_you`            VARCHAR(500) DEFAULT '' COMMENT '跟随自己的人',
  `you_follow`            VARCHAR(100) DEFAULT '' COMMENT '自己跟随的人',
  -- 师承
  `teacher_name`          VARCHAR(50)  DEFAULT '' COMMENT '师父名字',
  `school`                VARCHAR(50)  DEFAULT '' COMMENT '门派',
  `school_place`          BIGINT       DEFAULT 0 COMMENT '辈分',
  `all_enemy_list`        TEXT         COMMENT '所有敌人列表',
  `all_skills_list`       TEXT         COMMENT '所会技能列表',
  `work_skills`           TEXT         COMMENT '劳动技能',
  -- 装备
  `weapon_name`            VARCHAR(50)  DEFAULT '' COMMENT '武器名称',
  `weapon_type`            VARCHAR(20)  DEFAULT '' COMMENT '武器类型',
  `cloth_name`             VARCHAR(50)  DEFAULT '' COMMENT '衣服名称',
  `armor`                  VARCHAR(50)  DEFAULT '' COMMENT '盔甲',
  `hat`                    VARCHAR(50)  DEFAULT '' COMMENT '帽子',
  `shoe`                   VARCHAR(50)  DEFAULT '' COMMENT '鞋子',
  `flower`                 VARCHAR(50)  DEFAULT '' COMMENT '花',
  `ring`                   VARCHAR(50)  DEFAULT '' COMMENT '戒指',
  `necklace`               VARCHAR(50)  DEFAULT '' COMMENT '项链',
  `bangle`                 VARCHAR(50)  DEFAULT '' COMMENT '手镯',
  -- 仓库与任务
  `ck_level`              BIGINT       DEFAULT 0 COMMENT '仓库等级',
  `all_ck_list`           TEXT         COMMENT '仓库物品列表',
  `quest_list`            TEXT         COMMENT '任务列表',
  -- 其他
  `death_mode`            VARCHAR(20)  DEFAULT '' COMMENT '死亡方式',
  `not_dead`              TINYINT      DEFAULT 0 COMMENT '不死标记',
  `come_in`               BIGINT       DEFAULT 0 COMMENT '新人登录步骤',
  `noaccept`              TINYINT      DEFAULT 0 COMMENT '是否接受物品',
  `wiz_close_chat`        TINYINT      DEFAULT 0 COMMENT '巫师关闭频道',
  `play_close_chat`       TINYINT      DEFAULT 0 COMMENT '玩家关闭频道',
  `play_say_speed`        BIGINT       DEFAULT 0 COMMENT '说话频率',
  `create_time`           DATETIME     DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `update_time`           DATETIME     DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_user_id` (`user_id`),
  UNIQUE KEY `uk_name` (`name`),
  KEY `idx_faction` (`faction_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='玩家角色表';

-- ----------------------------
-- 3. 房间表
-- ----------------------------
DROP TABLE IF EXISTS `rooms`;
CREATE TABLE `rooms` (
  `id`                    BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `room_path`             VARCHAR(200) NOT NULL COMMENT '房间路径(如/room/华山/华山脚下)',
  `name`                  VARCHAR(100) NOT NULL COMMENT '房间名称',
  `description`           TEXT         COMMENT '房间描述',
  `room_type`             VARCHAR(30)  DEFAULT 'normal' COMMENT '房间类型: normal/bank/pawn/cook/retiring/work/yelian/liandan/newplayer/collect/jollity/lingwu/jail/marry/door/hiddendoor/load/cangku',
  `forbid_fight`          TINYINT     DEFAULT 0 COMMENT '禁止战斗: 0-否, 1-是',
  `boss_name`             VARCHAR(50) DEFAULT '' COMMENT '老板名字',
  `food_consume`          BIGINT      DEFAULT 2 COMMENT '饮食消耗',
  `update_time_interval`  BIGINT      DEFAULT 900000 COMMENT '刷新时间间隔(毫秒)',
  `destroy_list`          TEXT        COMMENT '销毁列表',
  `play_list_quit`        TEXT        COMMENT '人物退出列表',
  `min_x`                 INT         DEFAULT 10 COMMENT '最小X坐标',
  `max_x`                 INT         DEFAULT 365 COMMENT '最大X坐标',
  `min_y`                 INT         DEFAULT 90 COMMENT '最小Y坐标',
  `max_y`                 INT         DEFAULT 320 COMMENT '最大Y坐标',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_room_path` (`room_path`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='房间表';

-- ----------------------------
-- 4. 房间出口表
-- ----------------------------
DROP TABLE IF EXISTS `room_exits`;
CREATE TABLE `room_exits` (
  `id`              BIGINT      NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `room_id`         BIGINT      NOT NULL COMMENT '房间ID',
  `direction`       VARCHAR(20) NOT NULL COMMENT '方向(东/南/西/北/上/下/出口名)',
  `target_room_id`  BIGINT      NOT NULL COMMENT '目标房间ID',
  `is_hidden`       TINYINT     DEFAULT 0 COMMENT '是否暗门: 0-否, 1-是',
  PRIMARY KEY (`id`),
  KEY `idx_room_id` (`room_id`),
  KEY `idx_target` (`target_room_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='房间出口表';

-- ----------------------------
-- 5. NPC表
-- ----------------------------
DROP TABLE IF EXISTS `npcs`;
CREATE TABLE `npcs` (
  `id`                            BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `name`                          VARCHAR(50)  NOT NULL COMMENT 'NPC名称',
  `room_id`                       BIGINT       DEFAULT NULL COMMENT '所在房间ID',
  `place`                         VARCHAR(50)  DEFAULT '' COMMENT '所在位置(如:华山派)',
  `school`                        VARCHAR(50)  DEFAULT '' COMMENT '门派',
  `allow_prentice`                TINYINT      DEFAULT 0 COMMENT '是否收徒',
  `answer_for_agree_prentice`     VARCHAR(200) DEFAULT '' COMMENT '同意拜师的回答',
  `provide_quest`                 TINYINT      DEFAULT 0 COMMENT '是否发放任务',
  `need_pate`                     TINYINT      DEFAULT 0 COMMENT '需要首级',
  `need_kill_by_self`             TINYINT      DEFAULT 0 COMMENT '需亲自杀',
  `need_ge_by_self`               TINYINT      DEFAULT 0 COMMENT '需亲自割',
  `unite_kill`                    TINYINT      DEFAULT 0 COMMENT '联合协防',
  `player_say_when_giveup`        VARCHAR(200) DEFAULT '' COMMENT '玩家放弃时说话',
  `npc_say_when_no_quest`         VARCHAR(200) DEFAULT '' COMMENT '无任务说话',
  `npc_say_when_giveup`           VARCHAR(200) DEFAULT '' COMMENT '被放弃任务说话',
  `npc_say_when_be_give`          VARCHAR(200) DEFAULT '' COMMENT '被给东西时说话',
  `npc_say_when_end_quest`        VARCHAR(200) DEFAULT '' COMMENT '被完成任务说话',
  `appraise_name`                 VARCHAR(50)  DEFAULT '' COMMENT '评价名',
  `npc_show`                       TEXT         COMMENT 'NPC描述',
  `body`                          BIGINT       DEFAULT 100 COMMENT '气血',
  `max_body`                      BIGINT       DEFAULT 100 COMMENT '最大气血',
  `energy`                        BIGINT       DEFAULT 100 COMMENT '精力',
  `max_energy`                    BIGINT       DEFAULT 100 COMMENT '最大精力',
  `internal_force`                BIGINT       DEFAULT 0 COMMENT '内力',
  `max_internal_force`            BIGINT       DEFAULT 0 COMMENT '最大内力',
  `inhere_attack`                 BIGINT       DEFAULT 150 COMMENT '固定攻击力',
  `inhere_defense`                BIGINT       DEFAULT 150 COMMENT '固定防御力',
  `experience`                    BIGINT       DEFAULT 0 COMMENT '经验',
  `level`                         BIGINT       DEFAULT 20 COMMENT '等级',
  `icon_no`                       VARCHAR(20)  DEFAULT '' COMMENT '头像',
  `sex`                           CHAR(1)      DEFAULT 'm' COMMENT '性别',
  `age`                           INT          DEFAULT 30 COMMENT '年龄',
  `all_skills_list`               TEXT         COMMENT '所会技能',
  `killer_name`                   VARCHAR(50)  DEFAULT '' COMMENT '杀死自己的凶手',
  `be_kill_times`                 BIGINT       DEFAULT 0 COMMENT '被杀次数',
  `all_enemy_list`                TEXT         COMMENT '所有敌人列表',
  `death_mode`                    VARCHAR(20)  DEFAULT '' COMMENT '死亡方式',
  `not_dead`                      TINYINT      DEFAULT 0 COMMENT '不死',
  `npc_type`                      VARCHAR(30)  DEFAULT 'normal' COMMENT 'NPC类型: normal/teacher/marry/money/betray/offerreward/special',
  `title`                         VARCHAR(100) DEFAULT '' COMMENT '头衔',
  `nick`                          VARCHAR(100) DEFAULT '' COMMENT '绰号',
  `weapon_name`                   VARCHAR(50)  DEFAULT '' COMMENT '武器名称',
  `weapon_type`                   VARCHAR(20)  DEFAULT '' COMMENT '武器类型',
  `cloth_name`                    VARCHAR(50)  DEFAULT '' COMMENT '衣服名称',
  PRIMARY KEY (`id`),
  KEY `idx_room_id` (`room_id`),
  KEY `idx_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='NPC表';

-- ----------------------------
-- 6. 物品定义表
-- ----------------------------
DROP TABLE IF EXISTS `things`;
CREATE TABLE `things` (
  `id`            BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `name`          VARCHAR(50)  NOT NULL COMMENT '物品名称',
  `font_name`     VARCHAR(50)  DEFAULT '' COMMENT '显示名称',
  `weight`       BIGINT       DEFAULT 1 COMMENT '重量',
  `price`        BIGINT       DEFAULT 0 COMMENT '价格',
  `describe`      TEXT         COMMENT '描述',
  `quantifier`    VARCHAR(10)  DEFAULT '个' COMMENT '量词',
  `thing_type`    INT          DEFAULT 0 COMMENT '物体类型: 0-same 1-sameButOne 2-different',
  `varient_name`  VARCHAR(50)  DEFAULT '' COMMENT '变化量名',
  `category`      VARCHAR(20)  DEFAULT 'other' COMMENT '分类: weapon/armor/food/medicine/book/material/other',
  `sub_type`      VARCHAR(20)  DEFAULT '' COMMENT '子类型: sword/saber/fist/armor/hat/shoe/ring/necklace/bangle/flower',
  `attack`        BIGINT       DEFAULT 0 COMMENT '攻击力',
  `defense`       BIGINT       DEFAULT 0 COMMENT '防御力',
  PRIMARY KEY (`id`),
  KEY `idx_name` (`name`),
  KEY `idx_category` (`category`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='物品定义表';

-- ----------------------------
-- 7. 玩家物品表
-- ----------------------------
DROP TABLE IF EXISTS `player_things`;
CREATE TABLE `player_things` (
  `id`          BIGINT  NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `player_id`   BIGINT  NOT NULL COMMENT '玩家ID',
  `thing_id`    BIGINT  NOT NULL COMMENT '物品ID',
  `count`       INT     DEFAULT 1 COMMENT '数量',
  `equipped`    TINYINT DEFAULT 0 COMMENT '是否装备: 0-否, 1-是',
  `slot`        VARCHAR(20) DEFAULT '' COMMENT '装备位置: weapon/armor/hat/shoe/ring/necklace/bangle/flower',
  PRIMARY KEY (`id`),
  KEY `idx_player_id` (`player_id`),
  KEY `idx_thing_id` (`thing_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='玩家物品表';

-- ----------------------------
-- 8. 房间物品表
-- ----------------------------
DROP TABLE IF EXISTS `room_things`;
CREATE TABLE `room_things` (
  `id`          BIGINT NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `room_id`     BIGINT NOT NULL COMMENT '房间ID',
  `thing_id`    BIGINT NOT NULL COMMENT '物品ID',
  `count`       INT    DEFAULT 1 COMMENT '数量',
  PRIMARY KEY (`id`),
  KEY `idx_room_id` (`room_id`),
  KEY `idx_thing_id` (`thing_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='房间物品表';

-- ----------------------------
-- 9. 武功表
-- ----------------------------
DROP TABLE IF EXISTS `wugong`;
CREATE TABLE `wugong` (
  `id`                     BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `name`                   VARCHAR(50)  NOT NULL COMMENT '武功名称',
  `description`            TEXT         COMMENT '武功描述',
  `menpai`                 VARCHAR(50) DEFAULT '' COMMENT '门派',
  `leixing`                VARCHAR(20) DEFAULT '' COMMENT '类型: 拳法/掌法/剑法/刀法/暗器/内功/轻功/招架',
  `zhaoshu`                TEXT         COMMENT '招数列表(空格分隔)',
  `fangshouli`             BIGINT      DEFAULT 0 COMMENT '防守力',
  `neigong_needed`        BIGINT      DEFAULT 0 COMMENT '所需内功',
  `jiben_needed`           BIGINT      DEFAULT 0 COMMENT '所需基本武功',
  `jingyan_needed`         BIGINT      DEFAULT 0 COMMENT '所需经验',
  `jingli_used`            BIGINT      DEFAULT 3 COMMENT '消耗精力',
  `qianneng_used`          BIGINT      DEFAULT 1 COMMENT '消耗潜能',
  `is_special`             TINYINT     DEFAULT 0 COMMENT '是否特殊武功',
  `corresponding_basic`    VARCHAR(50) DEFAULT '' COMMENT '对应基本武功',
  `all_unique_skill`       TEXT         COMMENT '所有绝招(空格分隔)',
  PRIMARY KEY (`id`),
  KEY `idx_name` (`name`),
  KEY `idx_menpai` (`menpai`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='武功表';

-- ----------------------------
-- 10. 武功招数表
-- ----------------------------
DROP TABLE IF EXISTS `wugong_moves`;
CREATE TABLE `wugong_moves` (
  `id`            BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `wugong_id`     BIGINT       NOT NULL COMMENT '武功ID',
  `move_name`     VARCHAR(50)  NOT NULL COMMENT '招数名称',
  `gongjili`      BIGINT       DEFAULT 0 COMMENT '攻击力',
  `miaoshu`       TEXT         COMMENT '描述模板',
  `usable_level`  BIGINT       DEFAULT 0 COMMENT '可使用等级',
  PRIMARY KEY (`id`),
  KEY `idx_wugong_id` (`wugong_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='武功招数表';

-- ----------------------------
-- 11. 玩家技能表
-- ----------------------------
DROP TABLE IF EXISTS `player_skills`;
CREATE TABLE `player_skills` (
  `id`          BIGINT  NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `player_id`   BIGINT  NOT NULL COMMENT '玩家ID',
  `wugong_id`   BIGINT  NOT NULL COMMENT '武功ID',
  `level`       BIGINT  DEFAULT 0 COMMENT '武功等级',
  `is_enabled`  TINYINT DEFAULT 0 COMMENT '是否启用',
  `is_basic`    TINYINT DEFAULT 0 COMMENT '是否基本武功',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_player_wugong` (`player_id`, `wugong_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='玩家技能表';

-- ----------------------------
-- 12. 基本武功等级表
-- ----------------------------
DROP TABLE IF EXISTS `base_skills`;
CREATE TABLE `base_skills` (
  `id`          BIGINT      NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `player_id`   BIGINT      NOT NULL COMMENT '玩家ID',
  `skill_type`  VARCHAR(20) NOT NULL COMMENT '技能类型: hand/finger/sole/leg/pub/clow/dodge/force/parry/learn',
  `level`       BIGINT      DEFAULT 0 COMMENT '等级',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_player_type` (`player_id`, `skill_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='基本武功等级表';

-- ----------------------------
-- 13. 门派/帮派表
-- ----------------------------
DROP TABLE IF EXISTS `factions`;
CREATE TABLE `factions` (
  `id`            BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `name`          VARCHAR(50)  NOT NULL COMMENT '名称',
  `banner`        VARCHAR(200) DEFAULT '' COMMENT '口号',
  `owner_id`      BIGINT       DEFAULT NULL COMMENT '帮主玩家ID',
  `color`         VARCHAR(20)  DEFAULT 'green' COMMENT '颜色',
  `power`         BIGINT       DEFAULT 0 COMMENT '势力值',
  `player_amount` BIGINT       DEFAULT 0 COMMENT '玩家数量',
  `close`         BIGINT       DEFAULT 0 COMMENT '团结度',
  `is_school`     TINYINT      DEFAULT 0 COMMENT '是否门派: 0-帮派, 1-门派',
  `create_time`   DATETIME     DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='门派/帮派表';

-- ----------------------------
-- 14. 任务表
-- ----------------------------
DROP TABLE IF EXISTS `quests`;
CREATE TABLE `quests` (
  `id`                BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `quest_type`        VARCHAR(20)  NOT NULL COMMENT '任务类型: kill/send/city_kill',
  `target`            VARCHAR(100) DEFAULT '' COMMENT '任务目标(NPC名/地点)',
  `target_type`       VARCHAR(50)  DEFAULT '' COMMENT '目标类型(屠城专用)',
  `thing`             VARCHAR(50)  DEFAULT '' COMMENT '任务物品(送专用)',
  `time_limit`        BIGINT       DEFAULT 0 COMMENT '时间限制(毫秒)',
  `reward_exp`        BIGINT       DEFAULT 0 COMMENT '奖励经验',
  `reward_potential`  BIGINT       DEFAULT 0 COMMENT '奖励潜能',
  `reward_appraise`   BIGINT       DEFAULT 0 COMMENT '奖励评价',
  `reward_money`      BIGINT       DEFAULT 0 COMMENT '奖励银子',
  `npc_id`            BIGINT       DEFAULT NULL COMMENT '发放NPC的ID',
  PRIMARY KEY (`id`),
  KEY `idx_npc_id` (`npc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='任务表';

-- ----------------------------
-- 15. 玩家任务表
-- ----------------------------
DROP TABLE IF EXISTS `player_quests`;
CREATE TABLE `player_quests` (
  `id`          BIGINT  NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `player_id`   BIGINT  NOT NULL COMMENT '玩家ID',
  `quest_id`   BIGINT  NOT NULL COMMENT '任务ID',
  `times`       BIGINT  DEFAULT 1 COMMENT '连续次数',
  `status`      TINYINT DEFAULT 0 COMMENT '状态: 0-进行中 1-已完成 2-已放弃',
  `start_time`  DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT '开始时间',
  PRIMARY KEY (`id`),
  KEY `idx_player_id` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='玩家任务表';

-- ----------------------------
-- 16. 聊天记录表
-- ----------------------------
DROP TABLE IF EXISTS `chat_messages`;
CREATE TABLE `chat_messages` (
  `id`          BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `channel`     VARCHAR(20)  NOT NULL COMMENT '频道: say/chat/rumor/newbie/party/faction/wiz/system',
  `player_id`   BIGINT       DEFAULT NULL COMMENT '发送者ID',
  `player_name` VARCHAR(50)  DEFAULT '' COMMENT '发送者名称',
  `message`     TEXT         NOT NULL COMMENT '消息内容',
  `create_time` DATETIME     DEFAULT CURRENT_TIMESTAMP COMMENT '发送时间',
  PRIMARY KEY (`id`),
  KEY `idx_channel` (`channel`),
  KEY `idx_create_time` (`create_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='聊天记录表';

-- ----------------------------
-- 17. 系统设置表
-- ----------------------------
DROP TABLE IF EXISTS `system_settings`;
CREATE TABLE `system_settings` (
  `id`          BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `key`         VARCHAR(100) NOT NULL COMMENT '设置键',
  `value`       TEXT         COMMENT '设置值',
  `type`        VARCHAR(10)  DEFAULT 'string' COMMENT '值类型: string/long/float',
  `description` VARCHAR(200) DEFAULT '' COMMENT '描述',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_key` (`key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='系统设置表';

-- ----------------------------
-- 18. 仓库表
-- ----------------------------
DROP TABLE IF EXISTS `warehouse`;
CREATE TABLE `warehouse` (
  `id`          BIGINT NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `player_id`   BIGINT NOT NULL COMMENT '玩家ID',
  `thing_id`    BIGINT NOT NULL COMMENT '物品ID',
  `count`       INT    DEFAULT 1 COMMENT '数量',
  PRIMARY KEY (`id`),
  KEY `idx_player_id` (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='仓库表';

-- ----------------------------
-- 19. 表情动作表 (emote)
-- ----------------------------
DROP TABLE IF EXISTS `emotes`;
CREATE TABLE `emotes` (
  `id`            BIGINT       NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `name`          VARCHAR(30)  NOT NULL COMMENT '表情名',
  `self_msg`      VARCHAR(200) DEFAULT '' COMMENT '自己看到的消息',
  `target_msg`   VARCHAR(200) DEFAULT '' COMMENT '目标看到的消息',
  `others_msg`    VARCHAR(200) DEFAULT '' COMMENT '旁人看到的消息',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='表情动作表';

SET FOREIGN_KEY_CHECKS = 1;
