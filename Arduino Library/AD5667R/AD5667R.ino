#include <Wire.h>

#include "AD5667R.h"

void setup() {
  Serial.begin(115200);
  Wire.begin(); //master
  Serial.println("start");

  uint8_t error = AD5667R::setReference(AD5667R::Dac::BOTH, AD5667R::Reference::_INTERNAL);
  if ( !error )
    Serial.println("set internal reference");
  else
    Serial.println("error setting reference adc");

  error = AD5667R::setLdac(AD5667R::Dac::BOTH, AD5667R::Ldac::DISABLE);
  if ( !error )
    Serial.println("disaled ldac");
  else
    Serial.println("error setting ldac");  
}

void loop() {
  uint8_t error;
  error = AD5667R::setOutput(AD5667R::Dac::BOTH, 0xFFFF);
  if ( !error )
    Serial.println("output set 0xFFFF");
  else
    Serial.println("error setting output to 0xFFFF");  
  
  delay(5000);

  error = AD5667R::setOutput(AD5667R::Dac::BOTH, 0x00);
  if ( !error )
    Serial.println("output set 0x00");
  else
    Serial.println("error setting output to 0x00");  

  delay(5000);

  error = AD5667R::setOutput(AD5667R::Dac::BOTH, 0x00FF);
  if ( !error )
    Serial.println("output set 0x00FF");
  else
    Serial.println("error setting output to 0x00FF");  

  delay(5000);
}
