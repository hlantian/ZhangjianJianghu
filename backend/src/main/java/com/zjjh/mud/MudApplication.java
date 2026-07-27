package com.zjjh.mud;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@MapperScan("com.zjjh.mud.mapper")
@EnableScheduling
public class MudApplication {
    public static void main(String[] args) {
        SpringApplication.run(MudApplication.class, args);
    }
}
