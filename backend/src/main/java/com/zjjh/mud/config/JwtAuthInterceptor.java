package com.zjjh.mud.config;

import com.zjjh.mud.common.BusinessException;
import io.jsonwebtoken.Claims;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;

@Slf4j
@Component
@RequiredArgsConstructor
public class JwtAuthInterceptor implements HandlerInterceptor {

    private final JwtUtil jwtUtil;

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) {
        // OPTIONS预检请求放行
        if ("OPTIONS".equalsIgnoreCase(request.getMethod())) {
            return true;
        }

        String authHeader = request.getHeader("Authorization");
        if (authHeader == null || !authHeader.startsWith("Bearer ")) {
            throw BusinessException.of(401, "未登录或登录已过期，请重新登录");
        }

        String token = authHeader.substring(7);
        if (!jwtUtil.validateToken(token)) {
            throw BusinessException.of(401, "登录已过期，请重新登录");
        }

        try {
            Claims claims = jwtUtil.parseToken(token);
            request.setAttribute("userId", claims.get("userId"));
            request.setAttribute("username", claims.getSubject());
        } catch (Exception e) {
            throw BusinessException.of(401, "无效的登录凭证");
        }

        return true;
    }
}
