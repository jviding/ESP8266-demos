#pragma once

#include <stdint.h>


class SCCB {
public:
  // Functions
  static void init(uint8_t pin_SDA, uint8_t pin_SCL);
  static uint8_t readRegister(uint8_t reg);
  static void writeRegister(uint8_t reg, uint8_t val);

private:
  // Variables
  static const uint8_t SCCB_WRITE_ADDRESS;
  static const uint8_t SCCB_READ_ADDRESS;
  static uint8_t pin_SDA;
  static uint8_t pin_SCL;

  // Functions
  static void _init();
  static void start();
  static void stop();
  static void clockTick();
  static void ack();
  static void writeBit(uint8_t bit);
  static void writeByte(uint8_t data);
  static uint8_t _readByte();
  static uint8_t readByte();
};
