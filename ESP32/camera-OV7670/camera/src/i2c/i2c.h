#pragma once

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"

#define DEVICE_ADDR       0x21                        // OV7670 camera I2C address
#define DEVICE_ADDR_WRITE ((DEVICE_ADDR << 1) | 0x00) // 0x42
#define DEVICE_ADDR_READ  ((DEVICE_ADDR << 1) | 0x01) // 0x43

#define PIN_SDA       GPIO_NUM_26 //GPIO_NUM_21
#define PIN_SCL       GPIO_NUM_27 //GPIO_NUM_22

#define PORT          I2C_NUM_0   
#define TIMEOUT       (1000 / portTICK_PERIOD_MS) // Approx. 1000ms
#define SCCB_FREQ     (200 * 1000)                // 200kHz

class I2C {
public:
  // Functions
  static void init();
  static void writeRegister(uint8_t reg, uint8_t val);
  static uint8_t readRegister(uint8_t reg);

private:
  // Variables
  static const i2c_config_t conf;
  static i2c_cmd_handle_t cmd;

  // Functions
  static void start();
  static void stop();
  static void writeByte(uint8_t data);
  static uint8_t readByte();
};