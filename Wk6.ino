#define F_CPU 16000000UL

#include <QTRSensors.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motors.h"
#include "Sensors.h"


#define THRESHOLD 20
#define FULL_SPEED 150
#define HALF_SPEED FULL_SPEED/4

int i;
const int ADC_CHANNELS = 13;
int var[ADC_CHANNELS];
//void adc_setup
//{
//  ADMUX |= (1 << REFS0);     // Set ADC reference to AVCC
//  ADMUX |= (1 << ADLAR);     // Left Adjust the result 
//  ADCSRA |= (1 << ADEN);     // Enable ADC
//  ADCSRA |= (1 << ADIE);     // Enable ADC Interrupt
//  sei();                     // Enable Global Interrupts
//  ADCSRA |= (1 << ADSC);     // Start A2D Conversions
//  return;  
//}
int main()
{
  
  //initalise peripherals
  timer0_init();
  
  ADC_init();
 // ADC_init1();
  
  

  //create variables
  uint8_t motorSpeeds[2] = {0,0};
  

  
  while(1){
     // active reading
     int speed = 64;
     //setMotorSpeeds(var[8]/4,var[11]/4);
     OCR0A = var[11]/2;
      OCR0B = var[8]/2;
     if (var[8]<THRESHOLD || var[11]<THRESHOLD)
     {
      OCR0A = var[8]/4;
      OCR0B = var[11]/4;
     }
     
    //query sensor
   //int sensorReading = SensorValue();
    
    //determine motor speeds using bang-bang logic
    //if(ADC4 `<128){motorSpeeds[0] = 255;}
    
//    if(var[8] >= THRESHOLD && var[11] >=THRESHOLD){
//      motorSpeeds[0] = FULL_SPEED;
//      motorSpeeds[1] = FULL_SPEED;
//       
//    }
//    else if(var[8] <= THRESHOLD && var[11] >= THRESHOLD ){
//      motorSpeeds[0] = HALF_SPEED;
//      motorSpeeds[1] = FULL_SPEED/2;
//       
//    }
//    else if(var[8] >= THRESHOLD && var[11] <= THRESHOLD ){
//      motorSpeeds[0] = FULL_SPEED/2;
//      motorSpeeds[1] = HALF_SPEED;
//    }
//    else{motorSpeeds[0] = 0;
//      motorSpeeds[1] = 0;}
//    setMotorSpeeds(motorSpeeds);
    
  }return 0;
}



//ISR(ADC_vect)           
//  {
// //Count up to n channels
// (var[i]) = ADCH;
// 
//  if (++i >= ADC_CHANNELS)
//      {i=0;} 
//
//  ADMUX = (1<<ADLAR) | (1<<REFS1)|(1<<REFS0)|i; //Select ADC Channel
//  ADCSRA |= (1 << ADSC);    // Start A2D Conversions 
//  //ADCSRB |= (1<<MUX5);
//  } 
   
ISR(ADC_vect)           
  {
 //Count up to n channels
 //(myvar[i]) = ADCH;
 //Serial.println(i);
  if (++i >= ADC_CHANNELS)
      {i=0;} 
      
  if (i <=7){
     (var[i]) = ADCH;
     //ADCSRB |= (0<<MUX5);
     ADCSRB = 0b00000000;
     ADMUX = (1<<ADLAR) | (1<<REFS0) | i; //Select ADC Channel
    }
  if (i>7){
    (var[i]) = ADCH;
     //ADCSRB |=  (1<<MUX5);
     ADCSRB = 0b00100000;
     int value = i - 7; //back to 0 1 2 3 4 
     ADMUX = (1<<ADLAR) | (1<<REFS0) | value; //Select ADC Channel
    }
  
 
  ADCSRA |= (1 << ADSC);    // Start A2D Conversions 
  } 




 
