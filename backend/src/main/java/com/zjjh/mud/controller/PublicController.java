package com.zjjh.mud.controller;

import com.zjjh.mud.common.Result;
import com.zjjh.mud.service.PublicService;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/api/public")
@RequiredArgsConstructor
public class PublicController {

    private final PublicService publicService;

    @GetMapping("/online-count")
    public Result<Integer> getOnlineCount() {
        return Result.success(publicService.getOnlineCount());
    }

    @GetMapping("/rankings/exp")
    public Result<List<Map<String, Object>>> getExpRankings() {
        return Result.success(publicService.getExpRankings());
    }

    @GetMapping("/rankings/money")
    public Result<List<Map<String, Object>>> getMoneyRankings() {
        return Result.success(publicService.getMoneyRankings());
    }
}
