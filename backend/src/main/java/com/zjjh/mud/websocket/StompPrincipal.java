package com.zjjh.mud.websocket;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.security.Principal;

@Data
@AllArgsConstructor
public class StompPrincipal implements Principal {
    private final Long userId;
    private final String username;

    @Override
    public String getName() {
        return String.valueOf(userId);
    }
}
