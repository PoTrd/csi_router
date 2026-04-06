# Partition Table Documentation

This project uses a custom ESP-IDF partition table defined in [partitions.csv](/Users/paultaurand/Projects/csi_router/partitions.csv).

## Current Layout

```csv
# Name,      Type, SubType, Offset,   Size,    Flags
nvs,         data, nvs,     0x9000,   24K,
phy_init,    data, phy,     0xf000,   4K,
factory,     app,  factory, 0x10000,  1500K,
```

## Partition Description

### `nvs`

- Type: `data`
- SubType: `nvs`
- Offset: `0x9000`
- Size: `24K`

This partition stores persistent key-value data.
It is commonly used for:

- application settings
- saved configuration
- Wi-Fi credentials
- calibration or small runtime data

## `phy_init`

- Type: `data`
- SubType: `phy`
- Offset: `0xf000`
- Size: `4K`

This partition stores PHY initialization data used by the ESP32 radio subsystem.
It is a standard partition in many ESP-IDF layouts.

## `factory`

- Type: `app`
- SubType: `factory`
- Offset: `0x10000`
- Size: `1500K`

This is the main application partition.
The board boots the firmware from this partition.

For the current project, this size is enough for the application binary while keeping free space for future growth.

## Why This Layout

This layout was chosen because it is the simplest working custom partition table for the project:

- it includes the required persistent storage partition
- it includes the standard PHY data partition
- it provides one large application partition for the firmware

It does not include OTA partitions or a filesystem partition because they are not required for the current goal of getting the project to build and run with a test UI.

## Notes

- If OTA updates are needed later, this table should be changed to include `ota_0`, `ota_1`, and `otadata`.
- If the project needs local file storage, a `spiffs` or `fatfs` partition can be added.
- If the application binary grows too much, the `factory` partition size can be increased.
