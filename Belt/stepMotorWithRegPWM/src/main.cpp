#include <Arduino.h>
#include <Wire.h>

#define RDIR PD2
#define LDIR PD3
#define RSTEP PD6
#define LSTEP PB1

bool shouldBeOutput = true;

ISR(TIMER0_COMPA_vect)
{
  //hier moet worden ingesteld of de freq op de output moet worden gezet of niet
}
ISR(TIMER1_COMPA_vect)
{
  //idem TIMER0_COMPA_vect
  if (shouldBeOutput)
    TCCR1A |= (1 << COM1A0);
  else
    TCCR1A &= ~(1 << COM1A0);
  //Serial.println("hij komt hier wel");
}

int main(void)
{

  sei();
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR0A |= (1 << COM0A0);             /*toggle OC0A (PD6)
                                          niet meer connected omdat dan altijd een
                                          signaal aan de STEP hangt en dan minder controle*/
  TCCR0A |= (1 << WGM01);              //CTC mode
  TCCR0B |= (1 << CS01) | (1 << CS00); //prescaler 64  ==> 488 Hz  <--> 62500 Hz
  TCCR1A |= (1 << COM1A0);             //toggle OC1A (PB1)
  TCCR1B |= (1 << WGM12);              //CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10); //prescaler 64
  OCR1AH = 0;

  TIMSK0 |= (1 << OCIE0A); //Output Compare A Match Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);

  OCR0A = 4; //dit zal de snelheid bepalen van de stappenmotor, hoe kleiner hoe sneller
  OCR1AL = 7;

  DDRD |= (1 << LDIR);
  DDRD |= (1 << RDIR);
  DDRD |= (1 << LSTEP);
  DDRB |= (1 << RSTEP);

  PORTD |= (1 << LDIR);
  PORTD |= (1 << RDIR);

  //I2C setup
  //Wire.begin(8);
  //Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  while (1)
  {
  }
}