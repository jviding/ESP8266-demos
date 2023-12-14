// OV7670 Camera / SCCB (Serial Camera Control Bus)

// SIO_C - Clock Frequency   - max. 400 Khz (2500ns/cycle)
// LOW   - Clock Low Period  - min. 1300 ns
// HIGH  - Clock High Period - min. 600 ns

// SU:STA - START condition Setup time - min. 600 ns
// HD:STA - START condition Hold time  - min. 600 ns
// SU:STO - STOP condition Setup time  - min. 600 ns
// BUF    - Bus free time before new START - min. 1300 ns

// HD:DAT - Data-in Hold time  - min. 0 ns
// SU:DAT - Data-in Setup time - min. 100ns
// DH     - Data-out Hold time - min. 50 ns
// AA     - SIO_C low to Data out valid - min. 100 ns / max. 900 ns

#include "sccb.h"
#include <Arduino.h>
#include <stdint.h>

// OV7670 SCCB device addresses
const uint8_t SCCB::SCCB_WRITE_ADDRESS = 0x42;
const uint8_t SCCB::SCCB_READ_ADDRESS = 0x43;

uint8_t SCCB::pin_SDA;
uint8_t SCCB::pin_SCL;

void SCCB::init(uint8_t pin_SDA, uint8_t pin_SCL) {
  SCCB::pin_SDA = pin_SDA;
  SCCB::pin_SCL = pin_SCL;
  _init();
  delay(200);
};

void SCCB::_init() {
  pinMode(pin_SDA, OUTPUT);
  pinMode(pin_SCL, OUTPUT);
  digitalWrite(pin_SDA, HIGH); // SDA High
  digitalWrite(pin_SCL, HIGH); // SCL High
};

void SCCB::start() {
  delayMicroseconds(1);     // SU:STA
  digitalWrite(pin_SDA, 0); // Generate start condition
  delayMicroseconds(1);     // HD:STA
  digitalWrite(pin_SCL, 0);
};

void SCCB::stop() {
  delayMicroseconds(1);
  digitalWrite(pin_SDA, 0);
  delayMicroseconds(1);
  digitalWrite(pin_SCL, 1);
  delayMicroseconds(1);     // SU:STO
  digitalWrite(pin_SDA, 1); // Generate stop condition
  delayMicroseconds(2);     // BUF
};

void SCCB::clockTick() {
  digitalWrite(pin_SCL, 1);
  delayMicroseconds(1);
  digitalWrite(pin_SCL, 0);
};

void SCCB::ack() {
  // No ACK in SCCB, only "don't care bit"
  delayMicroseconds(2);
  clockTick();
};

void SCCB::writeBit(uint8_t bit) {
  delayMicroseconds(1);       // DH
  digitalWrite(pin_SDA, bit); // Bit out
  delayMicroseconds(1);
  clockTick();
};

void SCCB::writeByte(uint8_t data) {
  for (int8_t i = 7; i >= 0; i--) {
    uint8_t bit = (data >> i) & 1;
    writeBit(bit);
  }
  ack();
};

uint8_t SCCB::_readByte() {
  uint8_t data = 0;
  for (int8_t i = 7; i >= 0; i--) {
    delayMicroseconds(1); // DH & AA
    data |= (digitalRead(pin_SDA) << i);
    delayMicroseconds(1);
    clockTick();
  }
  return data;
};

uint8_t SCCB::readByte() {
  // SDA input mode
  digitalWrite(pin_SDA, 0);
  pinMode(pin_SDA, INPUT);
  // Byte in
  uint8_t data = _readByte();
  // SDA output mode
  digitalWrite(pin_SDA, 1);
  pinMode(pin_SDA, OUTPUT);
  // Send ACK
  ack();
  return data;
};

void SCCB::writeRegister(uint8_t reg, uint8_t val) {
  start();
  writeByte(SCCB_WRITE_ADDRESS);
  writeByte(reg);
  writeByte(val);
  stop();
};

uint8_t SCCB::readRegister(uint8_t reg) {
  start();
  writeByte(SCCB_WRITE_ADDRESS);
  writeByte(reg);
  stop();
  start();
  writeByte(SCCB_READ_ADDRESS);
  uint8_t val = readByte();
  stop();
  return val;
};
