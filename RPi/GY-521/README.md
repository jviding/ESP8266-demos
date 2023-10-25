# Prerequisites

Enable I2C on RPi:
1. \$ sudo raspi-config
2. Choose: Interface Options
3. Choose: I2C
4. Choose: Yes (to enable)

Verify:
5. \$ ls /dev/\*i2c\*

Should show a user-mode I2C port:
> /dev/i2c-1

# Then

\$ python main.py
