#include <Arduino.h>
#include <Wire.h>

#define LDIR PD2
#define LSTEP PD3
#define RDIR PD4
#define RSTEP PD5

bool couldLeftStep = false;
bool couldRightStep = false;

// enum mode
// {
//   cwMode,
//   ccwMode,
//   parkedMode
// } operationMode;
enum operationSpeed
{
  slowSpeed = 20,
  mediumSpeed = 10,
  fastSpeed = 2
} speed;

volatile long leftTimer = 0;
volatile long rightTimer = 0;
long rightPrevTimer = 0;
long leftPrevTimer = 0;

long stepsToTake = 1000;

ISR(TIMER0_COMPA_vect)
{
  //snelheid aanpassen & var optellen voor stapjes
  leftTimer++;
  OCR0A = speed;
}
ISR(TIMER1_COMPA_vect)
{
  rightTimer++;
  OCR1AL = speed;
}

void CouldLeftStep()
{
  //kan hij stappen? maw is er een compare geweest?
  if (leftPrevTimer != leftTimer)
  {
    leftPrevTimer = leftTimer;
    couldLeftStep = true;
  }
}
void CouldRightStep()
{
  if (rightPrevTimer != rightTimer)
  {
    rightPrevTimer = rightTimer;
    couldRightStep = true;
  }
}

void DoLeftStep()
{
  if (couldLeftStep)
  {
    PORTD ^= (1 << LSTEP);
    PORTD |= (1 << LDIR);
    couldLeftStep = false;
  }
}
void DoRightStep()
{
  if (couldRightStep)
  {
    PORTD ^= (1 << RSTEP);
    PORTD |= (1 << RDIR);
    couldRightStep = false;
  }
}

// void receiveEvent(int numBytes)
// {
//   while (Wire.available())
//   {
//     char rb = Wire.read();

//     if (rb & 0x01)
//     {
//       Serial.println("operationMode = cwMode");
//       operationMode = cwMode;
//     }
//     else
//     {
//       Serial.println("operationMode = ccwMode");
//       operationMode = ccwMode;
//     }

//     switch (rb & 0x06)
//     {
//     case 0x00:
//       operationMode = parkedMode;
//       Serial.println("operationMode = parkedMode");
//       break;
//     case 0x02:
//       operationSpeed = slowSpeed;
//       Serial.println("operationSpeed = slowSpeed");
//       break;
//     case 0x04:
//       operationSpeed = mediumSpeed;
//       Serial.println("operationSpeed = mediumSpeed");
//       break;
//     case 0x06:
//       operationSpeed = fastSpeed;
//       Serial.println("operationSpeed = fastSpeed");
//       break;
//     default:
//       Serial.println("something wrong");
//       break;
//     }
//     Serial.println("========================");
//   }
// }

int main(void)
{

  sei();
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR2A = 0;
  TCCR2B = 0;
  /*TCCR0A |= (1 << COM0A0);              //toggle OC0A (PD6)
                                          niet meer connected omdat dan altijd een
                                          signaal aan de STEP hangt en dan minder controle*/
  TCCR0A |= (1 << WGM01);              //CTC mode
  TCCR0B |= (1 << CS01) | (1 << CS00); //prescaler 64  ==> 488 Hz  <--> 62500 Hz
  TCCR1B |= (1 << WGM12);              //CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10); //prescaler 64
  OCR1AH = 0;

  TIMSK0 |= (1 << OCIE0A); //Output Compare A Match Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);

  OCR0A = 1; //dit zal de snelheid bepalen van de stappenmotor, hoe kleiner hoe sneller
  OCR1AL = 1;

  DDRD |= (1 << LSTEP); //LEFT STEP
  DDRD |= (1 << LDIR);  //LEFT DIR
  DDRD |= (1 << RSTEP); //RIGHT STEP
  DDRD |= (1 << RDIR);  //RIGHT DIR

  //I2C setup
  //Wire.begin(8);
  //Wire.onReceive(receiveEvent);

  //for testing
  //operationMode = cwMode;
  speed = fastSpeed;

  Serial.begin(9600);

  while (1)
  {
    CouldLeftStep();
    CouldRightStep();
    DoLeftStep();
    DoRightStep();
  }
}