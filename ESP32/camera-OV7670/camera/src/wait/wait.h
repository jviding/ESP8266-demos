#pragma once

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


class Wait {
public:
  // Functions
  static void milliseconds(int milliseconds);
};
