#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin(); //join i2c bus (address optional for master)

  int count = 0;
}

int count = 0;

void loop() {
  if(count==5){
    Wire.beginTransmission(8);  //transmit to device #8
    Wire.write(0b00000101);     //snelheid medium
                                //vooruit
    Wire.endTransmission();
  }
  else if(count==10){
    Wire.beginTransmission(8);  //transmit to device #8
    Wire.write(0b00000111);     //snelheid fast
                                //vooruit
    Wire.endTransmission();
  }
  else if(count==15){
    Wire.beginTransmission(8);  //transmit to device #8
    Wire.write(0b00000011);     //snelheid slow
                                //vooruit
    Wire.endTransmission();
  }
  else if (count == 20) count = 0;
  delay(1000);
  count++;
  
}