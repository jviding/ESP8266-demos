# Build

VS Code > Platformio > Build
  or
\$ pio run
  or
\$ g++ -o main main.cpp lib.h lib.cpp ...


Build includes:
1. bootloader.bin
2. partitions.bin
3. firmware.bin


# Flash

1. Identify the serial port
\$ ls /dev/ttyUSB*

2. First, erase flash (optional but recommended)
\$ esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash

3. Flash
\$ esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x1000 0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 firmware.bin

4. Optional: Read serial output from ESP32
\$ minicom -D /dev/ttyUSB0 -b 115200

With CTRL down A then Q to exit minicom