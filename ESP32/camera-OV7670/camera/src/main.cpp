#include "xclk/xclk.h"
#include "i2c/i2c.h"
//#include "cam_config/cam_config.h"
//#include "cam_data/cam_data.h"
//#include "cam/cam.h"
//#include "logger/logger.h"

#include "driver/uart.h"

uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
};

extern "C" {
  void app_main(void);
}

/*cam_config_t config = {
  .pin_sccb_sda = 26,
  .pin_sccb_scl = 27,
  .pin_xclk = 0,
  .pin_pclk = 22,
  .pin_href = 23,
  .pin_vsync = 25,
  .pin_d0 = 5,
  .pin_d1 = 18,
  .pin_d2 = 19,
  .pin_d3 = 21,
  .pin_d4 = 36,
  .pin_d5 = 39,
  .pin_d6 = 34,
  .pin_d7 = 35,
  .xclk_freq_MHz = 20,
};*/

void setup() {
  XCLK::start();
  I2C::init();

  //Serial.begin(115200);
  //Cam::init(config);

  //Serial.println("Testing VGA...");
  //CamConfig::setOutputVGAAndFormatRGB565();
};

void loop() { 
  //Serial.println("Image!");
  //Cam::captureImage();
  //CamData::testing();
  //delay(5000);

  printf("Next\n");
  fflush(stdout);

  //I2C::writeRegister(0x0A, 0x44);
  uint8_t val = I2C::readRegister(0x0A); // Returns 0x76

  printf("Val: %#x\n", static_cast<int>(val));
  fflush(stdout);

  //printf("Val read...");
  //printf("Val: %#x\n", static_cast<int>(0xAB));
  //fflush(stdout);

};

void app_main() {
  printf("Started");
  fflush(stdout);
  setup();
  while (1) { 
    loop();
    vTaskDelay(pdMS_TO_TICKS(500));
  }
};