#include <Arduino.h>
#include <Wire.h>

void testForwardsToBackwards()
{
  for (int i = 127; i > 0; i--)
  {
    Wire.beginTransmission(8);
    Wire.write(128 + i);
    Wire.endTransmission();

    delay(10);
  }
  for (int i = 1; i < 128; i++)
  {
    Wire.beginTransmission(8);
    Wire.write(i);
    Wire.endTransmission();

    delay(10);
  }
  delay(5000);
  for (int i = 127; i > 0; i--)
  {
    Wire.beginTransmission(8);
    Wire.write(i);
    Wire.endTransmission();

    delay(10);
  }
  for (int i = 1; i < 128; i++)
  {
    Wire.beginTransmission(8);
    Wire.write(128 + i);
    Wire.endTransmission();

    delay(10);
  }
  delay(5000);
}

void setup()
{
  Wire.begin(); //join i2c bus (address optional for master)
}

void loop()
{
  testForwardsToBackwards();
}

//if(count==5){
//   Wire.beginTransmission(8);  //transmit to device #8
//   Wire.write(0b00000101);     //snelheid medium
//                               //vooruit
//   Wire.endTransmission();
// }
// else if(count==10){
//   Wire.beginTransmission(8);  //transmit to device #8
//   Wire.write(0b00000111);     //snelheid fast
//                               //vooruit
//   Wire.endTransmission();
// }
// else if(count==15){
//   Wire.beginTransmission(8);  //transmit to device #8
//   Wire.write(0b00000011);     //snelheid slow
//                               //vooruit
//   Wire.endTransmission();
// }
// else if (count == 20) count = 0;
// delay(1000);
// count++;
