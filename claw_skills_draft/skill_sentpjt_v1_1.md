---
name: baselu-api
description: Use this draft skill when generating a cooling-system JSON from local examples, then calling the BaseLU project-creation or evaporating-temperature APIs and turning the base64 image response into a PNG report.
version: 1.1.1
---

# BaseLU API Draft

## Read These Local References First

- `device_params/BaseModuleID.txt`
- `json_to_png/*.json`
- `claw_skills_draft/prompt_designer.md`
- `claw_skills_draft/prompt_devops.md`

Ignore `NetAccess/` unless you are debugging your friend's internal renderer.

## Design Workflow

1. Determine the required system topology from the user's brief.
2. Select device types and `BaseModuleID` values from `device_params/BaseModuleID.txt`.
3. Build a UTF-8 JSON file that matches the structure used in `json_to_png/*.json`.
4. Save the JSON file locally first.
5. Call `POST /clawpjt` with an outer JSON body whose `data` field is a JSON string, not a nested JSON object.
6. If the API returns `image`, decode the base64 content into a PNG and save it locally.
7. Output a short report describing the design, the JSON path, the PNG path, and any API failures.

## JSON Rules

Top-level fields:

- `DeviceNb`: integer, must equal the total length of `DeviceInfo`
- `DeviceInfo`: array of devices, nodes, and page jumps

Each normal device entry follows this shape:

```json
{
  "设备": 0,
  "InstanceID": 0,
  "设备类型": "压缩机",
  "BaseModuelID": 24032321240003492,
  "FluidType": 0,
  "PositionX": 80,
  "PositionZ": 760,
  "RoomID": 0,
  "ModelID": ""
}
```

Important notes:

- Keep the API field spelling exactly as shown: `BaseModuelID` is intentionally misspelled in the existing data format.
- Use `设备` for normal devices, `节点` for nodes such as `FLUID`, and `跳转` for page connectors such as `PAGEIN` and `PAGEOUT`.
- The global numbering field (`设备`, `节点`, or `跳转`) should stay unique across the full array.
- `InstanceID` is usually sequential within each category.
- `PositionX` and `PositionZ` are canvas coordinates copied from the sample style; they are not physical dimensions.
- `RoomID` is `0` in the existing examples.
- `ModelID` can stay as `""` unless you have a confirmed model string.

## Practical Design Heuristic For A 2,000 m² Cold Store

Unless the user gives a stricter process requirement, a reasonable draft is:

- four cold rooms of roughly 500 m² each
- four compressors
- two evaporative condensers
- one intermediate cooler
- one liquid source vessel and one horizontal receiver
- two circulation pumps
- one branch per room with a throttling valve
- two air coolers per room

This is only a layout heuristic. The renderer appears to care mainly about valid device names, `BaseModuleID` values, and coordinates.

## Project Creation API

Endpoint:

```text
POST http://nas2.createing.cn:33360/clawpjt
```

Request body:

| Field | Type | Required | Notes |
|---|---|---|---|
| `name` | string | yes | Project name. Use 2-32 uppercase letters or digits. Existing examples such as `NH3CO2ZL` show digits are accepted. |
| `data` | string | yes | The full inner system JSON as a string. Do not send it as a nested JSON object unless you have verified the server accepts that form. |

Portable request pattern:

```bash
jq -Rs --arg name COLDHUB '{name:$name,data:.}' json_to_png/coldhub.json \
| curl -sS -X POST 'http://nas2.createing.cn:33360/clawpjt' \
    -H 'Content-Type: application/json; charset=utf-8' \
    --data-binary @-
```

Success response:

```json
{
  "image": "Base64image",
  "data": "已成功执行指令"
}
```

PNG decode examples:

Linux:

```bash
jq -r '.image' response.json | base64 --decode > json_to_png/coldhub.png
```

macOS:

```bash
jq -r '.image' response.json | base64 -D > json_to_png/coldhub.png
```

## Evaporating Temperature API

Endpoint:

```text
POST http://nas2.createing.cn:33360/clawtemp
```

Request body:

| Field | Type | Required | Notes |
|---|---|---|---|
| `name` | string | yes | Existing project name |
| `data` | number | yes | Target evaporating temperature in Celsius |

Example:

```bash
curl -sS -X POST 'http://nas2.createing.cn:33360/clawtemp' \
  -H 'Content-Type: application/json; charset=utf-8' \
  -d '{"name":"NH3CO2ZL","data":-23.2}'
```

## Beijing Outdoor Temperature Mapping

For the devops flow, use a linear mapping from outdoor temperature to evaporating temperature:

- outdoor range: `-15` to `40` Celsius
- evaporating range: `-22` to `-28` Celsius
- hotter outdoor temperature means lower evaporating temperature
- if outdoor temperature is outside the stated range, use `-23`

One direct formula is:

```text
evap = -22 - (outdoor - (-15)) * 6 / 55
```

Then clamp to `[-28, -22]`.

## Failure Handling

If the API is unreachable, times out, or returns malformed JSON:

1. keep the generated design JSON file
2. report the exact network or parsing error
3. do not fabricate a PNG
4. state that the blockage is external-service availability, not completed rendering

## What Was Fixed In This Draft

- Removed the hard-coded Windows path usage from the workflow.
- Replaced malformed `curl.exe` examples with shell-safe `curl` commands.
- Clarified that `data` for `/clawpjt` should be sent as a JSON string.
- Aligned the project-name note with the observed `NH3CO2ZL` example.
- Moved the device ID source of truth to `device_params/BaseModuleID.txt` instead of duplicating a fragile list here.
- Updated the documented API host to `nas2.createing.cn`.
