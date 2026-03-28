---
name: BaseLU API
version: 1.1.0
description: BaseLU API，能够新建冷库节能项目、设计一套氨制冷系统，可在与AI交互中通过调用下面所述API完成

# 基础知识
为了能顺利地完成氨制冷系统自动化设计、选型、组态，需要下面的对应关系：

设备库名称、BaseModuleID：
设备"MOS管"的BaseModuleID是"25030109460484710
设备"二极管"的BaseModuleID是"25022822195203300
设备"二极管反"的BaseModuleID是"2503011707491137
设备"关断器"的BaseModuleID是"24071322341181210
设备"导线"的BaseModuleID是"25032321491014823
设备"比较器"的BaseModuleID是"25030110122037710
设备"滤波波源"的BaseModuleID是"25110813505234380
设备"电位器"的BaseModuleID是"25030114053853177
设备"电容"的BaseModuleID是"24071320514960160
设备"电感"的BaseModuleID是"24070417122868918
设备"电池"的BaseModuleID是"24070219361900876
设备"电阻"的BaseModuleID是"24070219262122176
设备"直流电机"的BaseModuleID是"25022614563908107
设备"三相电源"的BaseModuleID是"25042710241042517
设备"接地"的BaseModuleID是"25050518550170396
设备"直流电源"的BaseModuleID是"25071322442767581
设备"MOS信号截断"的BaseModuleID是"25071421110748540
设备"脱扣器故障"的BaseModuleID是"25081812134202109
设备"断路故障"的BaseModuleID是"25081812202080309
设备"辅助电源板"的BaseModuleID是"25081811553232809
设备"霍尔电流"的BaseModuleID是"25030109385005110
设备"三级换热器二"的BaseModuleID是"26011210333490162
设备"储热罐定压"的BaseModuleID是"26010914123611094
设备"压气机"的BaseModuleID是"26010916045307494
设备"储冷罐定压"的BaseModuleID是"26011119283015866
设备"压缩一级换热器"的BaseModuleID是"26011121304191229
设备"压缩二级换热器"的BaseModuleID是"26011208583707559
设备"三级换热器一"的BaseModuleID是"26011209141011859
设备"中间冷却器"的BaseModuleID是"25030715413286490
设备"容积型源头"的BaseModuleID是"24032321240014592
设备"温度"的BaseModuleID是"25091713543619370
设备"罐体卧式"的BaseModuleID是"24032321240000892
设备"罐体立式"的BaseModuleID是"25030412494383087
设备"蓄水池不限高"的BaseModuleID是"25052114525635477
设备"精馏塔"的BaseModuleID是"25101910335071906
设备"冷却塔"的BaseModuleID是"24032321240002892
设备"管壳式换热器"的BaseModuleID是"24032321240015392
设备"冷风机"的BaseModuleID是"24032321240004592
设备"蒸发器"的BaseModuleID是"24032321240019292
设备"管壳式换热器定压"的BaseModuleID是"25063008510799313
设备"蒸发式冷凝器"的BaseModuleID是"24032321240020192
设备"板式换热器"的BaseModuleID是"25092115491945659
设备"太阳能集热器"的BaseModuleID是"25092117163842532
设备"过饱和蒸发器"的BaseModuleID是"25091113330390398
设备"风机盘管"的BaseModuleID是"25092117291321127
设备"冷库库房"的BaseModuleID是"24032321240008292
设备"压缩机"的BaseModuleID是"24032321240003492
设备"泵曲线法"的BaseModuleID是"24032321240011392
设备"泵迭代法"的BaseModuleID是"24032321240010892
设备"风机"的BaseModuleID是"24032321240003992
设备"风机曲线法"的BaseModuleID是"25092123400444808
设备"定位管"的BaseModuleID是"25092122461652050
设备"异径管"的BaseModuleID是"24032321240010392
设备"弯管"的BaseModuleID是"24032321240009792
设备"管道通用"的BaseModuleID是"24032022192805856
设备"毛细管道"的BaseModuleID是"25082921131886033
设备"方形风管"的BaseModuleID是"25082921244318233
设备"方形弯管"的BaseModuleID是"25082922074538433
设备"异径风管"的BaseModuleID是"25082923170872582
设备"铜弯管"的BaseModuleID是"25083018214709961
设备"铜异径管"的BaseModuleID是"25083018524631661
设备"铜直管"的BaseModuleID是"25083017561574261
设备"截止阀"的BaseModuleID是"24030917322826102
设备"止回阀"的BaseModuleID是"24032321240016792
设备"毛细节流阀"的BaseModuleID是"24032321240018492
设备"热力膨胀阀"的BaseModuleID是"24032321240016192
设备"止回阀逆向"的BaseModuleID是"25031017235859673
设备"蝶阀"的BaseModuleID是"25090821231444374
设备"球阀"的BaseModuleID是"25090822002576974
设备"闸阀"的BaseModuleID是"25090821481320374
设备"防火阀"的BaseModuleID是"25090822412897574
设备"风阀"的BaseModuleID是"25090822221234474
设备"电解制氢"的BaseModuleID是"25111612101817943
设备"汽轮机_TEST"的BaseModuleID是"25090111113467595
设备"冷凝器"的BaseModuleID是"25091615244343361
设备"给水泵"的BaseModuleID是"25091814230189937
设备"汽轮机2"的BaseModuleID是"25091815003418537
设备"节能控制"的BaseModuleID是"25062414021543233
设备"采暖负反馈器"的BaseModuleID是"25062820515823485
设备"风机盘管控制"的BaseModuleID是"24032321240005692
设备"现场v举报v规划"的BaseModuleID是"26031823105782676
设备"FOLDEDPLATEFLOCCULATION"的BaseModuleID是"25041019275798128
设备"ADVECTIVESEDIMENTATION"的BaseModuleID是"25041019275795428
设备"VFILTER"的BaseModuleID是"25041019275802728
设备"INCLINED"的BaseModuleID是"25041019275800928
设备"振动传感器WIT"的BaseModuleID是"26030110512383413
设备"可搭建房间"的BaseModuleID是"25092208120526336
设备"室外机"的BaseModuleID是"25092120305257651
设备"散热器"的BaseModuleID是"25092119192771617
设备"室内机"的BaseModuleID是"25092119192766817
设备"冷水机组"的BaseModuleID是"25092119192763617
设备"新风机组"的BaseModuleID是"25092119192773017
设备"锅炉"的BaseModuleID是"25092119192794717
设备"组合式空调机组"的BaseModuleID是"25092119192786017
设备"溴化锂机组"的BaseModuleID是"25092119192780117
设备"风冷机组"的BaseModuleID是"25092119192797217
设备"AAO"的BaseModuleID是"25041019275793928
设备"FLSECC"的BaseModuleID是"25041019275796828
设备"ZWXXDC"的BaseModuleID是"25041019275803328
设备"GMC"的BaseModuleID是"25041019275799228

### 设计步骤

依照设计要求，对设备进行选型，参照上文的BaseModuID，将设备选型信息与BaseModuleID相关联，列出设备列表，并将设备列表发送给下文“创建项目”中的API
，获取返回值之后，依照返回值中的图片（image）、描述（data），自主生成图文报告。

### BaseLU API
⚠️ **注意：**
- 所有 HTTP 请求与响应均使用 **UTF-8 编码**；发送 JSON 时推荐设置：`Content-Type: application/json; charset=utf-8`。

---

#### 1. 创建项目

```bash 
curl.exe -X POST http://nas2.createing.cn:33360/clawpjt -H "Content-Type: application/json; charset=utf-8" \ -d '{\"name\":\"FLAWET\",\"data\":\"{\\\"DeviceNb\\\":24,\\\"DeviceInfo\\\":[{\\\"设备\\\":0,\\\"InstanceID\\\":0,\\\"设备类型\\\":\\\"管壳式换热器\\\",\\\"BaseModuelID\\\":24032321240015392,\\\"FluidType\\\":0,\\\"PositionX\\\":10.2,\\\"PositionZ\\\":9.8,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":1,\\\"InstanceID\\\":1,\\\"设备类型\\\":\\\"管壳式换热器\\\",\\\"BaseModuelID\\\":24032321240015392,\\\"FluidType\\\":0,\\\"PositionX\\\":13.0,\\\"PositionZ\\\":3.0,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":2,\\\"InstanceID\\\":2,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":7.6,\\\"PositionZ\\\":2.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":3,\\\"InstanceID\\\":3,\\\"设备类型\\\":\\\"压缩机\\\",\\\"BaseModuelID\\\":24032321240003492,\\\"FluidType\\\":0,\\\"PositionX\\\":1.4,\\\"PositionZ\\\":2.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":4,\\\"InstanceID\\\":4,\\\"设备类型\\\":\\\"毛细节流阀\\\",\\\"BaseModuelID\\\":24032321240018492,\\\"FluidType\\\":0,\\\"PositionX\\\":21.6,\\\"PositionZ\\\":6.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":5,\\\"InstanceID\\\":5,\\\"设备类型\\\":\\\"截止阀\\\",\\\"BaseModuelID\\\":24030917322826102,\\\"FluidType\\\":0,\\\"PositionX\\\":21.6,\\\"PositionZ\\\":3.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":6,\\\"InstanceID\\\":6,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":13.4,\\\"PositionZ\\\":6.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":7,\\\"InstanceID\\\":7,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":21.6,\\\"PositionZ\\\":5.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":8,\\\"InstanceID\\\":8,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":16.4,\\\"PositionZ\\\":8.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":9,\\\"InstanceID\\\":9,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":12.8,\\\"PositionZ\\\":12.2,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":10,\\\"InstanceID\\\":10,\\\"设备类型\\\":\\\"容积型源头\\\",\\\"BaseModuelID\\\":24032321240014592,\\\"FluidType\\\":0,\\\"PositionX\\\":5.4,\\\"PositionZ\\\":3.8,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":11,\\\"InstanceID\\\":11,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":8.2,\\\"PositionZ\\\":3.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":12,\\\"InstanceID\\\":12,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":6.6,\\\"PositionZ\\\":8.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":13,\\\"InstanceID\\\":13,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":10.0,\\\"PositionZ\\\":5.2,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":14,\\\"InstanceID\\\":14,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":6.8,\\\"PositionZ\\\":10.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":15,\\\"InstanceID\\\":15,\\\"设备类型\\\":\\\"容积型源头\\\",\\\"BaseModuelID\\\":24032321240014592,\\\"FluidType\\\":0,\\\"PositionX\\\":2.4,\\\"PositionZ\\\":8.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":16,\\\"InstanceID\\\":16,\\\"设备类型\\\":\\\"泵曲线法\\\",\\\"BaseModuelID\\\":24032321240011392,\\\"FluidType\\\":0,\\\"PositionX\\\":4.6,\\\"PositionZ\\\":8.2,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":17,\\\"InstanceID\\\":17,\\\"设备类型\\\":\\\"泵曲线法\\\",\\\"BaseModuelID\\\":24032321240011392,\\\"FluidType\\\":0,\\\"PositionX\\\":6.8,\\\"PositionZ\\\":3.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":18,\\\"InstanceID\\\":18,\\\"设备类型\\\":\\\"截止阀\\\",\\\"BaseModuelID\\\":24030917322826102,\\\"FluidType\\\":0,\\\"PositionX\\\":9.6,\\\"PositionZ\\\":3.2,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":19,\\\"InstanceID\\\":19,\\\"设备类型\\\":\\\"截止阀\\\",\\\"BaseModuelID\\\":24030917322826102,\\\"FluidType\\\":0,\\\"PositionX\\\":9.0,\\\"PositionZ\\\":8.0,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":20,\\\"InstanceID\\\":20,\\\"设备类型\\\":\\\"管道通用\\\",\\\"BaseModuelID\\\":24032022192805856,\\\"FluidType\\\":0,\\\"PositionX\\\":21.6,\\\"PositionZ\\\":2.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"设备\\\":21,\\\"InstanceID\\\":21,\\\"设备类型\\\":\\\"截止阀\\\",\\\"BaseModuelID\\\":24030917322826102,\\\"FluidType\\\":0,\\\"PositionX\\\":23.0,\\\"PositionZ\\\":9.2,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"节点\\\":22,\\\"InstanceID\\\":0,\\\"设备类型\\\":\\\"FLUID\\\",\\\"BaseModuelID\\\":3000,\\\"FluidType\\\":0,\\\"PositionX\\\":19.2,\\\"PositionZ\\\":3.4,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"},{\\\"节点\\\":23,\\\"InstanceID\\\":1,\\\"设备类型\\\":\\\"FLUID\\\",\\\"BaseModuelID\\\":3000,\\\"FluidType\\\":0,\\\"PositionX\\\":20.4,\\\"PositionZ\\\":8.6,\\\"RoomID\\\":0,\\\"ModelID\\\":\\\"\\\"}]}\"}'
```

**请求体 (AgentRegisterIn):**
| 字段 | 类型 | 必填 | 说明 |
|------|------|------|------|
| name | string | 是 | ProjectName 名称，2–32 字符，仅大写字母 |
| data | string | 是 | 指令文本、json |

data的格式如下：
```json
{"DeviceNb":24,
"DeviceInfo":[
  {"设备":0,"InstanceID":0,"设备类型":"管壳式换热器","BaseModuelID":24032321240015392,"FluidType":0,"PositionX":10.2,"PositionZ":9.8,"RoomID":0,"ModelID":""},
  {"设备":1,"InstanceID":1,"设备类型":"管壳式换热器","BaseModuelID":24032321240015392,"FluidType":0,"PositionX":13.0,"PositionZ":3.0,"RoomID":0,"ModelID":""},
  {"设备":2,"InstanceID":2,"设备类型":"管道通用","BaseModuelID":24032022192805856,"FluidType":0,"PositionX":7.6,"PositionZ":2.6,"RoomID":0,"ModelID":""},
  {"设备":3,"InstanceID":3,"设备类型":"压缩机","BaseModuelID":24032321240003492,"FluidType":0,"PositionX":1.4,"PositionZ":2.4,"RoomID":0,"ModelID":""},
  {"设备":4,"InstanceID":4,"设备类型":"毛细节流阀","BaseModuelID":24032321240018492,"FluidType":0,"PositionX":21.6,"PositionZ":6.6,"RoomID":0,"ModelID":""},
  {"设备":5,"InstanceID":5,"设备类型":"截止阀","BaseModuelID":24030917322826102,"FluidType":0,"PositionX":21.6,"PositionZ":3.6,"RoomID":0,"ModelID":""},
  {"设备":6,"InstanceID":6,"设备类型":"管道通用","BaseModuelID":24032022192805856,"FluidType":0,"PositionX":13.4,"PositionZ":6.4,"RoomID":0,"ModelID":""}]
}
```

**成功响应 (200):**
```json
{
  "image": "Base64image",
  "data": "已成功执行指令"
}
```

**响应体:**
| 字段 | 类型 | 必填 | 说明 |
|------|------|------|------|
| image | Base64 | 是 | 返回的图片，用于展示给用户看 |
| data | string | 是 | 返回的执行结果，配合图片给用户看 |

**报告生成:**
根据上述请求响应中的图片（image ）、描述（data ），自动生成一个报告，给用户展示。

