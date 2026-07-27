package com.zjjh.mud.websocket;

import com.zjjh.mud.config.JwtUtil;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.simp.stomp.StompCommand;
import org.springframework.messaging.simp.stomp.StompHeaderAccessor;
import org.springframework.messaging.support.ChannelInterceptor;
import org.springframework.messaging.support.MessageBuilder;
import org.springframework.stereotype.Component;

import java.util.List;

@Slf4j
@Component
@RequiredArgsConstructor
public class GameWebSocketAuthInterceptor implements ChannelInterceptor {

    private final JwtUtil jwtUtil;

    @Override
    public Message<?> preSend(Message<?> message, MessageChannel channel) {
        StompHeaderAccessor accessor = StompHeaderAccessor.wrap(message);

        if (StompCommand.CONNECT.equals(accessor.getCommand())) {
            // 尝试从STOMP头获取Authorization
            List<String> authHeaders = accessor.getNativeHeader("Authorization");
            String token = null;

            if (authHeaders != null && !authHeaders.isEmpty()) {
                String authHeader = authHeaders.get(0);
                if (authHeader.startsWith("Bearer ")) {
                    token = authHeader.substring(7);
                }
            }

            // 如果STOMP头没有，从会话属性获取(HandshakeInterceptor设置的)
            if (token == null) {
                @SuppressWarnings("unchecked")
                java.util.Map<String, Object> sessionAttrs = 
                    (java.util.Map<String, Object>) accessor.getHeader(
                        org.springframework.messaging.support.NativeMessageHeaderAccessor.NATIVE_HEADERS);
                
                // 从session attributes获取
                Object principalObj = accessor.getSessionAttributes() != null ? 
                    accessor.getSessionAttributes().get("principal") : null;
                if (principalObj instanceof StompPrincipal stompPrincipal) {
                    accessor.setUser(stompPrincipal);
                    log.info("WebSocket用户连接(来自握手): userId={}, username={}", 
                        stompPrincipal.getUserId(), stompPrincipal.getUsername());
                    return MessageBuilder.createMessage(
                        message.getPayload(), accessor.getMessageHeaders());
                }
            }

            if (token != null && jwtUtil.validateToken(token)) {
                Long userId = jwtUtil.getUserIdFromToken(token);
                String username = jwtUtil.getUsernameFromToken(token);
                StompPrincipal principal = new StompPrincipal(userId, username);
                accessor.setUser(principal);
                log.info("WebSocket用户连接(来自STOMP头): userId={}, username={}", userId, username);
                return MessageBuilder.createMessage(
                    message.getPayload(), accessor.getMessageHeaders());
            }

            log.warn("WebSocket连接认证失败");
            return null;
        }

        // 非CONNECT消息，原样返回(保留session级别的user principal)
        return message;
    }
}
