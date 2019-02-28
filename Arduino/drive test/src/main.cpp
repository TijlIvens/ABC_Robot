#include <Arduino.h>
#include <Wire.h>
#define h1m1 3 //H1 left side H bridge
#define h1m2 4
#define h2m1 6 //H2 right side H bridge
#define h2m2 7

byte command;
byte speed;
byte correction = 20;
byte comparepwmL;
byte comparepwmR;

void stop();
void forward(byte);
void backwards(byte);
void turnleft();
void turnright();
void receiveEvent(int);
bool start;
/*
	Drive	bit	
	B00000000	0	0 = stop 1 = start
		1	0 = achteruit 1 = vooruit
		23	00 = niets 01 = draai links 11 = draai rechts
		45	00 = niets 01 = corrigeren links 11 = corrigeren rechts
		67	00 = stop 01 = traag 10 = medium 11 = snel
*/
void setup() 
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() 
{
  start = (command & 0X1);
  if(!start &&!(command >> 3 & 0X1))
    stop();
  if(start)
  {
    speed = (command >> 6 & 0X2)*64;
    if(command >> 1 & 0X1)
      forward(speed);
    if(!(command >> 1 & 0X1))
      backwards(speed);
  }
  if(command >> 3 & 0X1)
    {
      if(command >> 2 & 0X1)
        turnleft();
      if(!(command >> 2 & 0X1))
        turnright();
    }
}

void stop()
{
  PORTD |= 1 << h1m1 | 1 << h1m2 | 1 << h2m1 | 1 << h2m2;
}
void forward(byte speed)
{
  comparepwmL = speed;
  comparepwmR = speed;
  if(command >>5 & 0X1)
  {
    if(command >> 4 & 0X1)
      comparepwmR -= correction;
    if(!(command >> 4 & 0X1))
      comparepwmR -= correction;
  }
  PORTD |= 1 << h1m1 | 0 << h1m2 | 1 << h2m1 | 0 << h2m2;
}
void backwards(byte speed)
{
  PORTD |= 0 << h1m1 | 1 << h1m2 | 0 << h2m1 | 1 << h2m2;
}
void turnleft()
{
  PORTD |= 0 << h1m1 | 1 << h1m2 | 1 << h2m1 | 0 << h2m2;
}
void turnright()
{
  PORTD |= 1 << h1m1 | 0 << h1m2 | 0 << h2m1 | 1 << h2m2;
}

void receiveEvent(int howMany) 
{
  command = Wire.read();
  Serial.println(command);
}