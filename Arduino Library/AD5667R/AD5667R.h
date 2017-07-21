#ifndef AD5667R_H
#define AD5667R_H

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>

class AD5667R{
  
  public:
  enum class Dac{
    A = 0x00,
    B = 0x01,
    BOTH = 0x07
  };
  
  enum class Reference{
    _INTERNAL = 0x00,
    _EXTERNAL = 0x01
  };

  enum class Ldac{
    ENABLE = 0x00,
    DISABLE = 0x01
  };
  
  enum class Command{
    CMD_WRITE_REG = (0x00 << 3),
    CMD_WRITE_DAC = (0x01 << 3),
    CMD_WRITE_UPD_REG = (0x02 << 3),
    CMD_WRITE_UPD_DAC = (0x03 << 3),
    CMD_SETUP_PWR = (0x04 << 3),
    CMD_SETUP_RST = (0x05 << 3),
    CMD_SETUP_LDAC = (0x06 << 3),
    CMD_SETUP_REF = (0x07 << 3)
  };
  
  static uint8_t sendCommand(uint8_t selection, Command command, Dac dac, uint8_t high, uint8_t low, uint64_t timeout);
  
  static uint8_t setReference(Dac dac, Reference ref, uint64_t timeout = 0){
    return sendCommand(0, Command::CMD_SETUP_REF, dac, 0, static_cast<int>(ref), timeout);
  }

  static uint8_t setLdac(Dac dac, Ldac ldac, uint64_t timeout = 0){
    return sendCommand(0, Command::CMD_SETUP_LDAC, dac, 0, static_cast<int>(ldac), timeout);
  }

  static uint8_t setOutput(Dac dac, uint16_t value, uint64_t timeout = 0){
    return sendCommand(0, Command::CMD_WRITE_REG, dac, value>>8, value & 0xFF, timeout);
  }
  
};
#endif
