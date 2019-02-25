#include <Wire.h>
#include <VL53L0X.h>

//#define XSHUT_pin6 not required for address change
#define XSHUT_pin3 14
#define XSHUT_pin2 13
#define XSHUT_pin1 12

//ADDRESS_DEFAULT 0b0101001 or 41
//#define Sensor1_newAddress 41 not required address change
#define Sensor2_newAddress 42
#define Sensor3_newAddress 43

VL53L0X Sensor1;
VL53L0X Sensor2;
VL53L0X Sensor3;

void setup()
{ /*WARNING*/
  //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(XSHUT_pin3, OUTPUT);
  
  Serial.begin(9600);
  
  Wire.begin();
  Sensor3.setAddress(Sensor3_newAddress);
  pinMode(XSHUT_pin2, INPUT);
  delay(10);
  Sensor2.setAddress(Sensor2_newAddress);
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  
  Sensor1.init();
  Sensor2.init();
  Sensor3.init();
  
  Sensor1.setTimeout(500);
  Sensor2.setTimeout(500);
  Sensor3.setTimeout(500);
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  Sensor1.startContinuous();
  Sensor2.startContinuous();
  Sensor3.startContinuous();

}

void loop()
{
  Serial.print(Sensor1.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(Sensor2.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print(Sensor3.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.println();
}