package com.zjjh.mud.websocket;

import lombok.extern.slf4j.Slf4j;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.server.support.DefaultHandshakeHandler;

import java.security.Principal;
import java.util.Map;

@Slf4j
@Component
public class CustomHandshakeHandler extends DefaultHandshakeHandler {

    @Override
    protected Principal determineUser(ServerHttpRequest request,
                                       WebSocketHandler wsHandler,
                                       Map<String, Object> attributes) {
        // 从握手属性中获取 HandshakeInterceptor 设置的 principal
        Object principal = attributes.get("principal");
        if (principal instanceof Principal p) {
            log.info("HandshakeHandler确定用户: {}", ((StompPrincipal) p).getUsername());
            return p;
        }
        log.warn("HandshakeHandler未找到用户principal, 使用默认");
        return super.determineUser(request, wsHandler, attributes);
    }
}
