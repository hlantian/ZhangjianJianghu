package com.zjjh.mud.dto;

import lombok.Data;

@Data
public class LoginResponse {
    private String token;
    private Long userId;
    private String username;
    private Long playerId;
    private String playerName;
    private String sex;
    private Boolean isNewPlayer;
}
