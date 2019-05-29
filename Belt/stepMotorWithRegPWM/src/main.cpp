#include <Arduino.h>
#include <Wire.h>

#define RDIR PD2
#define LDIR PD3
#define RSTEP PD6
#define LSTEP PB1

bool shouldBeOutput = true;
int byteToOCR = 18;

ISR(TIMER0_COMPA_vect)
{
  //hier moet worden ingesteld of de freq op de output moet worden gezet of niet
  OCR0A = byteToOCR;
}
ISR(TIMER1_COMPA_vect)
{
  //idem TIMER0_COMPA_vect
  if (shouldBeOutput)
    TCCR1A |= (1 << COM1A0);
  else
    TCCR1A &= ~(1 << COM1A0);
  //Serial.println("hij komt hier wel");

  OCR1AL = byteToOCR;
}

void receiveEvent(int numBytes)
{
  while (Wire.available())
  {
    char rb = Wire.read();
    int val = rb & 0x7F;
    byteToOCR = map(val, 1, 127, 255, 18);

    if (rb & 0x80) //dit leest de vooruit/achteruit uit
    {
      Serial.print("Vooruit : ");
      PORTD |= (1 << RDIR) | (1 << LDIR);
    }
    else
    {
      Serial.print("Achteruit : ");
      PORTD &= ~(1 << RDIR) & ~(1 << LDIR);
    }

    Serial.println(byteToOCR);
  }
}

int main(void)
{

  sei();
  TCCR0A = 0;
  TCCR0B = 0;
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR0A |= (1 << COM0A0); /*toggle OC0A (PD6)
                                          niet meer connected omdat dan altijd een
                                          signaal aan de STEP hangt en dan minder controle*/
  TCCR0A |= (1 << WGM01);  //CTC mode
  TCCR0B |= (1 << CS01);   //prescaler 8  ==> 3900 Hz  <--> 500000 Hz
  TCCR1A |= (1 << COM1A0); //toggle OC1A (PB1)
  TCCR1B |= (1 << WGM12);  //CTC mode
  TCCR1B |= (1 << CS11);   //prescaler 8
  OCR1AH = 0;

  TIMSK0 |= (1 << OCIE0A); //Output Compare A Match Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);

  OCR0A = byteToOCR; //dit zal de snelheid bepalen van de stappenmotor, hoe kleiner hoe sneller
  OCR1AL = byteToOCR;

  DDRD |= (1 << RDIR);
  DDRD |= (1 << LDIR);
  DDRD |= (1 << RSTEP);
  DDRB |= (1 << LSTEP);

  PORTD |= (1 << LDIR);
  PORTD |= (1 << RDIR);

  //I2C setup
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);

  while (1)
  {
  }
}