# Demos with hardware setups

Microcontrollers, sensors, components, etc.

## Note: NMAP
To find the device from your local network:
\$ sudo nmap --open -sS -p <SSH-port> <NetworkIPs>

## 1 - Raspberry Pi (RPi)

- 3-Axis Acceleration Gyroscope (GY-521 MPU6050)

## 2 - ESP32

- Camera module (OV7670)

## 3 - ESP8266


## Set up ESP dev environment on RPi

See: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/

To easily set up the esp-idf environment in any terminal session.
1. Create an alias for executing export.sh:
\$ alias get_idf='. $HOME/esp/esp-idf/export.sh'
2. Refresh the terminal session, or:
\$ source ~/.bashrc
3. Launch the environment:
\$ get_idf

4. Remember to set the target chip (i.e., esp32):
\$ idf.py set-target <target>
