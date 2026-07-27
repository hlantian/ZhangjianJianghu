package com.zjjh.mud.datamigration;

import lombok.extern.slf4j.Slf4j;

import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.*;
import java.util.*;

/**
 * .profile 文件解析器
 * 解析原C++项目的属性文件格式
 *
 * 格式示例:
 * #class=YRoom
 * begin of YPropertyGroup
 * string values:
 * 名字=房间名
 * 描述=@LONG
 *     多行描述...
 * LONG
 * 出口名=/room/路径
 * long values:
 * 数值属性=100
 * float values:
 * end of YPropertyGroup
 * begin of YObjectGroup
 * object=thing/物品名
 * object=npc/NPC名
 * end of YObjectGroup
 */
@Slf4j
public class ProfileParser {

    private final Charset charset;

    public ProfileParser() {
        // 原文件使用 GBK/GB2312 编码
        this.charset = Charset.forName("GBK");
    }

    public ParsedProfile parse(Path filePath) {
        try {
            List<String> lines = Files.readAllLines(filePath, charset);
            return parseLines(lines);
        } catch (IOException e) {
            log.error("解析文件失败: {}", filePath, e);
            return null;
        }
    }

    public ParsedProfile parseLines(List<String> lines) {
        ParsedProfile profile = new ParsedProfile();
        String currentSection = null;
        String currentValueType = null; // string/long/float
        boolean inLongText = false;
        StringBuilder longText = new StringBuilder();
        String longTextKey = null;

        for (String line : lines) {
            // 处理多行文本块
            if (inLongText) {
                if (line.trim().equals("LONG") || line.trim().equals("@LONG")) {
                    // 结束多行文本
                    if (longTextKey != null && currentSection != null) {
                        profile.setValue(currentSection, longTextKey, longText.toString().trim());
                    }
                    inLongText = false;
                    longText = new StringBuilder();
                    longTextKey = null;
                } else {
                    longText.append(line).append("\n");
                }
                continue;
            }

            String trimmed = line.trim();

            // class声明
            if (trimmed.startsWith("#class=")) {
                profile.setClassName(trimmed.substring(7).trim());
                continue;
            }

            // 开始属性组
            if (trimmed.startsWith("begin of ")) {
                String sectionName = trimmed.substring(9).trim();
                currentSection = sectionName;
                continue;
            }

            // 结束属性组
            if (trimmed.startsWith("end of ")) {
                currentSection = null;
                currentValueType = null;
                continue;
            }

            // 值类型标记
            if (trimmed.equals("string values:")) {
                currentValueType = "string";
                continue;
            }
            if (trimmed.equals("long values:")) {
                currentValueType = "long";
                continue;
            }
            if (trimmed.equals("float values:")) {
                currentValueType = "float";
                continue;
            }

            // 空行跳过
            if (trimmed.isEmpty()) continue;

            // key=value 对
            int eqIdx = trimmed.indexOf('=');
            if (eqIdx > 0 && currentSection != null) {
                String key = trimmed.substring(0, eqIdx).trim();
                String value = trimmed.substring(eqIdx + 1).trim();

                // 检查是否是@LONG多行文本
                if (value.equals("@LONG")) {
                    inLongText = true;
                    longTextKey = key;
                    longText = new StringBuilder();
                    continue;
                }

                // object=xxx 格式
                if (key.equals("object") && currentSection.equals("YObjectGroup")) {
                    profile.addObject(value);
                    continue;
                }

                profile.setValue(currentSection, key, value);
                continue;
            }
        }

        return profile;
    }

    /**
     * 解析结果
     */
    public static class ParsedProfile {
        private String className;
        private final Map<String, Map<String, String>> sections = new LinkedHashMap<>();
        private final List<String> objects = new ArrayList<>();

        public ParsedProfile() {}

        public String getClassName() { return className; }
        public void setClassName(String className) { this.className = className; }

        public void setValue(String section, String key, String value) {
            sections.computeIfAbsent(section, k -> new LinkedHashMap<>()).put(key, value);
        }

        public String getValue(String section, String key) {
            Map<String, String> s = sections.get(section);
            return s != null ? s.get(key) : null;
        }

        public String getString(String key) {
            return getValue("YPropertyGroup", key);
        }

        public Long getLong(String key) {
            String v = getValue("YPropertyGroup", key);
            if (v == null || v.isEmpty()) return null;
            try { return Long.parseLong(v.trim()); } catch (NumberFormatException e) { return null; }
        }

        public void addObject(String obj) { objects.add(obj); }
        public List<String> getObjects() { return objects; }

        public Map<String, Map<String, String>> getSections() { return sections; }

        @Override
        public String toString() {
            return "ParsedProfile{class=" + className + ", sections=" + sections.size() + ", objects=" + objects.size() + "}";
        }
    }
}
