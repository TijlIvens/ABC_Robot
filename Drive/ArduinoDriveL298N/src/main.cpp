#include <Arduino.h>
#include <Wire.h>

int dirPins[] = {2, 3, 4, 7};

enum lDirection
{
  lForward,
  lBackward,
  lParked
} leftDirection;
enum rDirection
{
  rForward,
  rBackward,
  rPardked
} rightDirection;
enum lSpeed
{
  lSlow = 50,
  lMedium = 100,
  lFast = 200
} lTrackSpeed;
enum rSpeed
{
  rSlow = 50,
  rMedium = 100,
  rFast = 200
} rTrackSpeed;

void setTrackDirections()
{
}

void setTracksSpeed()
{
}

int main(void)
{

  sei();
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR0A |= (1 << COM0A1);               //OC0A connected (PD6 if output) --> non-inverting mode
  TCCR0A |= (1 << COM0B1);               //OC0B connected (PD5 if output) --> non-inverting mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00); //Fast pwm mode
  TCCR0B |= (1 << CS01) | (1 << CS00);   /*Prescaler = 64
                                          zorgt voor een signaal aan de motoren
                                          met een freq van ongeveer 1kHz*/
  //initial speed
  lTrackSpeed = lFast;
  rTrackSpeed = rSlow;
  OCR0A = 255;
  OCR0B = 100;

  DDRD |= (1 << PD5);
  DDRD |= (1 << PD6);

  for (int i = 0; i < 4; i++)
  {
    pinMode(dirPins[i], OUTPUT);
  }

  //initial direction
  digitalWrite(dirPins[0], HIGH); //2
  digitalWrite(dirPins[1], LOW);  //3
  digitalWrite(dirPins[2], HIGH); //4
  digitalWrite(dirPins[3], LOW);  //7

  while (1)
  {
    //setTrackDirections();
    //setTracksSpeed();
  }
}