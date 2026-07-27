package com.zjjh.mud.controller;

import com.zjjh.mud.common.Result;
import com.zjjh.mud.dto.*;
import com.zjjh.mud.entity.Player;
import com.zjjh.mud.service.AuthService;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/auth")
@RequiredArgsConstructor
public class AuthController {

    private final AuthService authService;

    @PostMapping("/register")
    public Result<LoginResponse> register(@Valid @RequestBody RegisterRequest request) {
        return Result.success("注册成功", authService.register(request));
    }

    @PostMapping("/login")
    public Result<LoginResponse> login(@Valid @RequestBody LoginRequest request) {
        return Result.success("登录成功", authService.login(request));
    }

    @PostMapping("/password")
    public Result<Void> changePassword(@Valid @RequestBody ChangePasswordRequest request) {
        authService.changePassword(request);
        return Result.success("密码修改成功", null);
    }

    @GetMapping("/player")
    public Result<Player> getPlayerInfo(HttpServletRequest request) {
        Long userId = (Long) request.getAttribute("userId");
        Player player = authService.getPlayerByUserId(userId);
        if (player == null) {
            return Result.error("未找到角色信息");
        }
        return Result.success(player);
    }
}
