#include "AD5667R.h"

#define AD5667R_MASK_BYTE_SELECTION 0x40


AD5667R::AD5667R(uint8_t i2cAddress):
  address(i2cAddress)
{  
}

uint8_t AD5667R::sendCommand(uint8_t selection, Command command, Dac dac, uint8_t high, uint8_t low, uint64_t timeout){
  uint8_t header = 0;
  if (selection){
    header |= AD5667R_MASK_BYTE_SELECTION;
  }

  header |= static_cast<uint8_t>(command);

  header |= static_cast<uint8_t>(dac);

  Wire.beginTransmission(address);
  Wire.write(header);
  Wire.write(high);
  Wire.write(low);
  Wire.endTransmission();
  
  if (!timeout){
    //if timeout is 0, we dont want to verify the command success. we always return success (0)
    return 0;
  }

  Wire.requestFrom(0x0F, 3);
  
  uint64_t start = micros();
  while (Wire.available() < 3 && micros() - start < timeout) {
    delayMicroseconds(1);
  }
  if (micros() - start >= timeout){
    return 1;
  }
  if (Wire.read() != header){
    return 2;
  }
  if (Wire.read() != high){
    return 3;
  }
  if (Wire.read() != low){
    return 4;
  }

  return 0;
}

