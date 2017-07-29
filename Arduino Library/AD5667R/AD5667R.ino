#include <Wire.h>

#include "AD5667R.h"

AD5667R dac; //use default i2c address
//AD5667R dac(0xAA); //use 0xAA as i2c address

void setup() {
  Serial.begin(115200);
  Wire.begin(); //master
  Serial.println("start");



  uint8_t error = dac.setReference(Dac::BOTH, Reference::_EXTERNAL);
  if ( !error )
    Serial.println("set internal reference");
  else
    Serial.println("error setting reference adc");

  error = dac.setLdac(Dac::BOTH, Ldac::DISABLE);
  if ( !error )
    Serial.println("disaled ldac");
  else
    Serial.println("error setting ldac");  

}

void loop() {
  uint8_t error;
  error = dac.setOutput(Dac::BOTH, 0xFFFF);
  if ( !error )
    Serial.println("output set 0xFFFF");
  else
    Serial.println("error setting output to 0xFFFF");  
  
  delay(5000);

  error = dac.setOutput(Dac::BOTH, 0x00);
  if ( !error )
    Serial.println("output set 0x00");
  else
    Serial.println("error setting output to 0x00");  

  delay(5000);

  error = dac.setOutput(Dac::BOTH, 0x00FF);
  if ( !error )
    Serial.println("output set 0x00FF");
  else
    Serial.println("error setting output to 0x00FF");  

  delay(5000);
}
