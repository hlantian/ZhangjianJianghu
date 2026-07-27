package com.zjjh.mud.dto;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;
import lombok.Data;

@Data
public class RegisterRequest {
    @NotBlank(message = "用户名不能为空")
    @Size(min = 2, max = 20, message = "用户名长度2-20个字符")
    private String username;

    @NotBlank(message = "密码不能为空")
    @Size(min = 6, max = 30, message = "密码长度6-30个字符")
    private String password;

    @NotBlank(message = "性别不能为空")
    @Pattern(regexp = "^[mf]$", message = "性别只能为m或f")
    private String sex;

    @NotBlank(message = "角色名不能为空")
    @Size(min = 2, max = 10, message = "角色名长度2-10个字符")
    private String playerName;
}
