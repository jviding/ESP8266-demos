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
    .clk_speed =    SCCB_FREQ,
  },
  .clk_flags =      0,
};

i2c_cmd_handle_t I2C::cmd = NULL;
uint8_t I2C::i2c_data_in = 0x00;


void I2C::init() {
  i2c_param_config(PORT, &conf);

  /*// Clock periods
  //uint32_t clk_high_period; // min. 600 ns
  //uint32_t clk_low_period;  // min. 1.3 us
  //i2c_set_period(PORT, clk_high_period, clk_low_period);
  
  // Clock START
  uint32_t start_setup_time;  // min. 600 ns
  uint32_t start_hold_time;   // min. 600 ns
  i2c_set_start_timing(PORT, start_setup_time, start_hold_time);
  
  // Clock STOP
  uint32_t stop_setup_time;   // min. 600 ns 
  uint32_t stop_hold_time;    // min. n/a    
  i2c_set_stop_timing(PORT, stop_setup_time, stop_hold_time);
  
  // Data periods
  uint32_t sda_sample_time;   // min. 100 ns
  uint32_t sda_hold_time;     // min. 0
  i2c_set_data_timing(PORT, sda_sample_time, sda_hold_time);*/

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

void I2C::write_byte(uint8_t data) { 
  i2c_master_write_byte(cmd, data, false);
};

void I2C::read_byte() {
  i2c_data_in = 0x00;
  i2c_master_read_byte(cmd, &i2c_data_in, I2C_MASTER_NACK);
};

void I2C::write_register(uint8_t reg, uint8_t val) {
  start();
  write_byte(DEVICE_ADDR_WRITE);
  write_byte(reg);
  write_byte(val);
  stop();
};

uint8_t I2C::read_register(uint8_t reg) {
  start();
  write_byte(DEVICE_ADDR_WRITE);
  write_byte(reg);
  stop();
  start();
  write_byte(DEVICE_ADDR_READ);
  read_byte();
  stop();
  return i2c_data_in;
};
