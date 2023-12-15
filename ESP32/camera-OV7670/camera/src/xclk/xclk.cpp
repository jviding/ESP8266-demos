#include "xclk.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"


const gpio_config_t XCLK::io_conf = {
  .pin_bit_mask = (1ULL << PIN_XCLK),
  .mode         = GPIO_MODE_OUTPUT,
  .pull_up_en   = GPIO_PULLUP_DISABLE,
  .pull_down_en = GPIO_PULLDOWN_DISABLE,
  .intr_type    = GPIO_INTR_DISABLE,
};

const ledc_timer_config_t XCLK::timer_conf = {
  .speed_mode      = LEDC_LOW_SPEED_MODE,
  .duty_resolution = LEDC_TIMER_1_BIT,          // Resolution = 2
  .timer_num       = LEDC_TIMER_0,
  .freq_hz         = (FREQ_MHz * 1000 * 1000),  // Convert MHz to Hz
  .clk_cfg         = LEDC_AUTO_CLK,
};

const ledc_channel_config_t XCLK::ledc_conf = {
  .gpio_num   = PIN_XCLK,
  .speed_mode = LEDC_LOW_SPEED_MODE,
  .channel    = LEDC_CHANNEL_0,
  .intr_type  = LEDC_INTR_DISABLE,
  .timer_sel  = LEDC_TIMER_0,
  .duty       = LEDC_TIMER_1_BIT, // 50% duty cycle for a square wave (with Resolution = 2)
  .hpoint     = 0,
  .flags      = 0,
};


void XCLK::_init() {
  gpio_config(&io_conf);
  ledc_timer_config(&timer_conf);
  ledc_channel_config(&ledc_conf);
};

void XCLK::start() {
  _init();
  ledc_fade_func_install(0);
};
