现在帮忙设计一套氨制冷系统。

先阅读 `claw_skills_draft/skill_sentpjt_v1_1.md`、`device_params/BaseModuleID.txt` 和 `json_to_png/*.json`，忽略 `NetAccess/`。

然后为一个 2000 平方米冷库设计一套氨制冷系统，并按以下顺序执行：

1. 先生成一个新的系统 JSON 文件，并保存到 `json_to_png/`。
2. 再调用 `http://nas2.createing.cn:33360/clawpjt`。
3. 请求体中的 `data` 必须是完整系统 JSON 的字符串，而不是嵌套对象。
4. 如果接口返回 `image`，将 base64 解码为 PNG，并保存到 `json_to_png/`。
5. 输出简短报告，至少包含设备方案、JSON 路径、PNG 路径。
6. 如果接口超时、不可达或返回异常，明确报告失败原因，不要伪造图片。
