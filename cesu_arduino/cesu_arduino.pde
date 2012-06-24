#include "MsTimer2.h"
#define ENCODER_READ 5
unsigned int encoderPos,a;
void setup()
{  
    Serial.begin(9600);
    MsTimer2::set(1000, flash); // 500ms period
    MsTimer2::start();
    counterStart();
}

void loop()
{
}
void counterStart()
{
  TCCR1A=0;                       
  TCCR1B=0;                
  TCNT1=0;                     
  TCCR1B = TCCR1B | 7; 
}
unsigned int getCount()
{
  unsigned int count;
  count = TCNT1;  
  TCNT1=0;  
  TCCR1B = TCCR1B & ~7;                      
  TCCR1B = TCCR1B | 7;                  
  return count;                             
}
void flash() {
encoderPos = getCount();
a=encoderPos*6;
Serial.print("rotate speed = ");
Serial.print(a);
Serial.println(" RPM");
}
