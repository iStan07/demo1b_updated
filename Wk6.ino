#define F_CPU 16000000UL

#include <QTRSensors.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motors.h"
#include "Sensors.h"


#define THRESHOLD 80
#define FULL_SPEED 64
#define HALF_SPEED FULL_SPEED/4

int i;
const int ADC_CHANNELS = 7;
int var[ADC_CHANNELS];

int main()
{
  
  //initalise peripherals
  timer0_init();
  
  ADC_init();
  ADC_init1();
  
  

  //create variables
  uint8_t motorSpeeds[2] = {0,0};
  

  
  while(1){
   
    //query sensor
   int sensorReading = SensorValue();
    
    //determine motor speeds using bang-bang logic
    //if(ADC4 `<128){motorSpeeds[0] = 255;}
    if(sensorReading >= THRESHOLD){
      motorSpeeds[0] = FULL_SPEED;
      motorSpeeds[1] = FULL_SPEED;
       
    }
    if(sensorReading >= THRESHOLD){
      motorSpeeds[0] = FULL_SPEED;
      motorSpeeds[1] = FULL_SPEED;
       
    }
    else{motorSpeeds[0] = 0;
      motorSpeeds[1] = 0;}
    setMotorSpeeds(motorSpeeds);
    
  }return 0;
}




  
ISR(ADC_vect)           
  {
 //Count up to n channels
 (var[i]) = ADCH;
 
  if (++i >= ADC_CHANNELS)
      {i=0;} 

  ADMUX = (1<<ADLAR) | (1<<REFS1)|(1<<REFS0)|(1<<MUX2)|(1<<MUX1); //Select ADC Channel
  ADCSRA |= (1 << ADSC);    // Start A2D Conversions 
  //ADCSRB |= (1<<MUX5);
  } 
   





 
