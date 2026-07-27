package com.zjjh.mud.controller;

import com.zjjh.mud.common.Result;
import com.zjjh.mud.datamigration.DataMigrationService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

@RestController
@RequestMapping("/api/admin")
@RequiredArgsConstructor
public class MigrationController {

    private final DataMigrationService migrationService;

    @PostMapping("/migrate")
    public Result<String> migrate() {
        migrationService.migrateAll();
        return Result.success("数据迁移完成");
    }

    @PostMapping("/migrate/rooms")
    public Result<Integer> migrateRooms() {
        return Result.success(migrationService.migrateRooms());
    }

    @PostMapping("/migrate/things")
    public Result<Integer> migrateThings() {
        return Result.success(migrationService.migrateThings());
    }

    @PostMapping("/migrate/npcs")
    public Result<Integer> migrateNpcs() {
        return Result.success(migrationService.migrateNpcs());
    }

    @PostMapping("/migrate/exits")
    public Result<Integer> migrateExits() {
        return Result.success(migrationService.migrateRoomExits());
    }
}
