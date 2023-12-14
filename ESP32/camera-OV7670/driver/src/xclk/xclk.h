#pragma once

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define PIN_XCLK  GPIO_NUM_4
#define FREQ_MHz  20

class XCLK {
public:
  // Functions
  static void start();

private:
  // Variables
  static const gpio_config_t io_conf;
  static const ledc_timer_config_t timer_conf;
  static const ledc_channel_config_t ledc_conf;

  // Functions
  static void _init();
};
