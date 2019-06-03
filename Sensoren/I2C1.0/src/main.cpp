#include <Wire.h>
#include <VL53L0X.h>

//#define XSHUT_pin6 not required for address change

//ADDRESS_DEFAULT 0b0101001 or 41
//#define Sensor1_newAddress 41 not required address change
#define Sensor2_newAddress 42
#define Sensor3_newAddress 43
#define Sensor4_newAddress 44
#define Sensor5_newAddress 45
#define Sensor6_newAddress 46
#define Sensor7_newAddress 47
#define Sensor8_newAddress 48

uint8_t addresses[] = {41,42,43,44,45,46,47,48};
byte bytes[] = {B00000010,B00000100,B00001000,B10000000,B01000000,B00000001,B00100000,B00010000};

int latchPin = 14;
int clockPin = 32;
int dataPin = 15;

VL53L0X sensors[8];


void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(9600);

  Wire.begin();
  for (int i=0; i < 5; i+=1){
    digitalWrite(latchPin, LOW);
    delay(20);
    shiftOut(dataPin, clockPin, MSBFIRST, bytes[i]);
    delay(20);
    digitalWrite(latchPin, HIGH);
    delay(20);
    sensors[i].init();
    delay(20);
    sensors[i].setAddress(addresses[i]);
    delay(50);
    //sensors[i].startContinuous();
  }
    
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);
  
  for (int i=0; i < 5; i+=1){
    delay(5);
     //sensors[i].startContinuous();
    delay(5);
  }
}

void loop()
{
  for (int i=0; i < 5; i+=1){
    Serial.print(sensors[i].readRangeContinuousMillimeters());
    Serial.print(',');
    delay(20);
  }
  Serial.println();
}