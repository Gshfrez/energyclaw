---
name: BaseCER API
version: 1.1.0
description: BaseCER API，可以获取冷库项目的运行概况、效能数据。

## 运维调节步骤

自动获取北京市的实时气温，将实时气温映射为一个蒸发温度，并通过下文"蒸发温度设定"中的API进行调用。

实时气温与蒸发温度范围及相互映射的规则如下：
实时气温的范围：从-15摄氏度到40摄氏度
蒸发温度的范围：从-22摄氏度到-28摄氏度
映射关系为：实时气温越高，蒸发温度越低，当超出映射范围时，蒸发温度默认为-23摄氏度


## 效能获取步骤

使用下文中的“获取效能请求”API，获取返回值中的图片（image）、描述（data）生成一份图文并茂的报告。其中，返回值中图片展示的是曲线图变化，返回值中的描述（data）内容包含效率值、能耗值、库温值、冷凝温度值

## BaseCER API
⚠️ **注意：**
- 所有 HTTP 请求与响应均使用 **UTF-8 编码**；发送 JSON 时推荐设置：`Content-Type: application/json; charset=utf-8`。

---

### 1.  蒸发温度设定
```bash 
curl.exe -X POST http://nas2.createing.cn:33360/clawtemp -H "Content-Type: application/json; charset=utf-8" \ -d '{\"name\":\"FLAWET\",\"data\":-23.22}'
```

**请求体 (AgentRegisterIn):**
| 字段 | 类型 | 必填 | 说明 |
|------|------|------|------|
| name | string | 是 | ProjectName 名称，2–32 字符，仅字母数字，不能有下划线 |
| data | double | 是 | 要设置的温度 |


**成功响应 (200):**
```json
{
  "data": "已成功将温度转化、设置到位 或您的温度设置超出正常范围，为安全着想，一忽略此次设置"
}
```
**响应体:**
| 字段 | 类型 | 必填 | 说明 |
|------|------|------|------|
| data | string | 是 | 返回的执行结果，包含成功与否、问题反馈 |


### 2.  获取效能请求
```bash 
curl.exe -X POST http://nas2.createing.cn:33360/clawcer -H "Content-Type: application/json; charset=utf-8" \ -d '{\"name\":\"FLAWET\"}'
```

**请求体 (AgentRegisterIn):**
| 字段 | 类型 | 必填 | 说明 |
|------|------|------|------|
| name | string | 是 | ProjectName 名称，2–32 字符，仅字母数字，不能有下划线 |


**成功响应 (200):**
```json
{
  "image": "Base64image",
  "data": "当前效率值是：4.2；平均能耗是300KW；库温-17.5摄氏度；冷凝温度为28.5摄氏度"
}
```
**响应体:**
| 字段 | 类型 | 必填 | 说明 |
|------|------|------|------|
| image | Base64 | 是 | 返回的图片，用于展示给用户看 |
| data | string | 是 | 返回的执行描述与问题，配合图片展示给用户看 |
