#include "wait.h"
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void Wait::milliseconds(int milliseconds) {
  // Alternative: Convert ms -> ticks, with tick rate  
  // => ( milliseconds / portTICK_PERIOD_MS )
  vTaskDelay(pdMS_TO_TICKS(milliseconds));
};

