package com.zjjh.mud.websocket;

import com.zjjh.mud.config.JwtUtil;
import io.jsonwebtoken.Claims;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServerHttpResponse;
import org.springframework.http.server.ServletServerHttpRequest;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.server.HandshakeInterceptor;
import org.springframework.stereotype.Component;

import jakarta.servlet.http.HttpServletRequest;
import java.security.Principal;
import java.util.Map;

@Slf4j
@Component
@RequiredArgsConstructor
public class WebSocketHandshakeInterceptor implements HandshakeInterceptor {

    private final JwtUtil jwtUtil;

    @Override
    public boolean beforeHandshake(ServerHttpRequest request, ServerHttpResponse response,
                                   WebSocketHandler wsHandler, Map<String, Object> attributes) {
        if (request instanceof ServletServerHttpRequest servletRequest) {
            HttpServletRequest httpRequest = servletRequest.getServletRequest();
            
            // 从查询参数获取token
            String token = httpRequest.getParameter("token");
            if (token == null || token.isEmpty()) {
                // 也尝试从Header获取
                token = httpRequest.getHeader("Authorization");
                if (token != null && token.startsWith("Bearer ")) {
                    token = token.substring(7);
                }
            }

            if (token == null || token.isEmpty()) {
                log.warn("WebSocket握手缺少token");
                return false;
            }

            if (!jwtUtil.validateToken(token)) {
                log.warn("WebSocket握手token无效");
                return false;
            }

            try {
                Claims claims = jwtUtil.parseToken(token);
                Long userId = claims.get("userId", Long.class);
                if (userId == null) {
                    Object idObj = claims.get("userId");
                    if (idObj instanceof Integer) {
                        userId = ((Integer) idObj).longValue();
                    }
                }
                String username = claims.getSubject();

                // 设置用户Principal到WebSocket会话属性
                StompPrincipal principal = new StompPrincipal(userId, username);
                attributes.put("principal", principal);
                
                log.info("WebSocket握手成功: userId={}, username={}", userId, username);
                return true;
            } catch (Exception e) {
                log.error("WebSocket握手解析token失败", e);
                return false;
            }
        }
        return false;
    }

    @Override
    public void afterHandshake(ServerHttpRequest request, ServerHttpResponse response,
                               WebSocketHandler wsHandler, Exception exception) {
    }
}
