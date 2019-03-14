#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin(); //join i2c bus (address optional for master)
}

void loop() {
  Wire.beginTransmission(8);  //transmit to device #8
  Wire.write(0b00001011);     //snelheid medium
                              //vooruit
                              //enable
  Wire.endTransmission();
  
  delay(1000);
}