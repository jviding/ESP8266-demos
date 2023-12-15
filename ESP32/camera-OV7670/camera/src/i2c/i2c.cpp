#include "i2c.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/i2c.h"

const i2c_config_t I2C::conf = {
  .mode =           I2C_MODE_MASTER,
  .sda_io_num =     PIN_SDA,
  .scl_io_num =     PIN_SCL,
  .sda_pullup_en =  GPIO_PULLUP_ENABLE,
  .scl_pullup_en =  GPIO_PULLUP_ENABLE,
  .master = { 
    .clk_speed =    SCCB_FREQ 
  },
  .clk_flags =      0,  // TODO: Poista?
};

i2c_cmd_handle_t I2C::cmd = NULL;


void I2C::init() {
  i2c_param_config(PORT, &conf);
  
  // Clock periods
  /*uint32_t clk_high_period = 600; // Min. 600 ns
  uint32_t clk_low_period = 1300;   // Min. 1.3 us
  i2c_set_period(PORT_NUM, clk_high_period, clk_low_period);
  
  // Sample times
  uint32_t sda_sample_time = 100; // Min. 100 ns
  uint32_t sda_hold_time = 100;   // Min. 0
  i2c_set_data_timing(PORT_NUM, sda_sample_time, sda_hold_time);

  // Hold times
  uint32_t start_setup_time = 600;  // Min. 600 ns
  uint32_t start_hold_time = 600;   // Min. 600 ns
  i2c_set_start_timing(PORT_NUM, start_setup_time, start_hold_time);*/

  i2c_driver_install(PORT, I2C_MODE_MASTER, 0, 0, 0);
};

void I2C::start() {
  cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
};

void I2C::stop() {
  i2c_master_stop(cmd);
  i2c_master_cmd_begin(PORT, cmd, TIMEOUT);
  i2c_cmd_link_delete(cmd);
  cmd = NULL;
};

void I2C::writeByte(uint8_t data) { 
  i2c_master_write_byte(cmd, data, false);
  // esp_err_t er =
  // if (er != ESP_OK) {}
};

uint8_t I2C::readByte() {
  uint8_t data;
  i2c_master_read_byte(cmd, &data, I2C_MASTER_NACK);
  return data;
};

void I2C::writeRegister(uint8_t reg, uint8_t val) {
  start();
  writeByte(DEVICE_ADDR_WRITE);
  writeByte(reg);
  writeByte(val);
  stop();
};

uint8_t I2C::readRegister(uint8_t reg) {
  start();
  writeByte(DEVICE_ADDR_WRITE);
  writeByte(reg);
  stop();
  start();
  writeByte(DEVICE_ADDR_READ);
  uint8_t val = readByte();
  stop();
  return val;
};
