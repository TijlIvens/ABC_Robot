#include <Arduino.h>
#include <Wire.h>

bool couldStep = false;

enum mode{cwMode,ccwMode,parkedMode}operationMode;
enum speed{slowSpeed = 20,mediumSpeed = 10,fastSpeed = 4}operationSpeed;

volatile long timer = 0;
long prevTimer = 0;

long stepsToTake = 1000;




ISR(TIMER0_COMPA_vect){
  //snelheid aanpassen & var optellen voor stapjes
  timer++;
  OCR0A = operationSpeed;
}





void CouldIStep(){
  //kan hij stappen? maw is er een compare geweest?
  if(prevTimer != timer){
    prevTimer = timer;
    couldStep = true;
  }
}

void DoStep(){
  if (couldStep) {
    
    //if (prevTimer < stepsToTake) {
      switch(operationMode){
        case cwMode:
          PORTD &= ~(1<<PD2);
          PORTD ^= (1<<PD3);
          break;
        case ccwMode:
          PORTD |= (1<<PD2);
          PORTD ^= (1<<PD3);
          break;
        case parkedMode:
          PORTD |= (1<<PD3);
          break;
        default:
          Serial.println("Something is wrong with mode");
      } 
    //}
    
    couldStep = false;
  }
}

void receiveEvent(int numBytes){
  while(Wire.available()){
    char rb = Wire.read();

    if(rb & 0x01) Serial.println("enabled");

    if(rb & 0x02) Serial.println("vooruit");
    else Serial.println("achteruit");
    
    switch(rb & 0x0C){
      case 0x04:
        Serial.println("slow");
        break;
      case 0x08:
        Serial.println("medium");
        break;
      case 0x0C:
        Serial.println("fast");
        break;
      default:
        Serial.println("something wrong");
        break;
    }  
  }
}



int main(void){

  sei();
  TCCR0A = 0;
  TCCR0B = 0;
  //TCCR0A |= (1 << COM0A0);              //toggle OC0A (PD6)
  TCCR0A |= (1 << WGM01);               //CTC mode
  TCCR0B |= (1 << CS02)|(1 << CS00);    //prescaler 1024

  TIMSK0 |= (1 << OCIE0A);              //Output Compare A Match Interrupt Enable
  
  OCR0A = 16;                           //dit zal de snelheid bepalen van de stappenmotor, hoe kleiner hoe sneller


  DDRD |= (1<<PD3);           //STEP
  DDRD |= (1<<PD2);           //DIR

  //I2C setup
  Wire.begin(8);
  Wire.onReceive(receiveEvent);

  //for testing
  operationMode = cwMode;
  operationSpeed = fastSpeed;

  Serial.begin(9600);

  while(1){
    CouldIStep();
    DoStep();
  }
}