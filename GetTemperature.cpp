#include <DallasTemperature.h>

#include "WProgram.h"
void setup(void);
void loop(void);
DallasTemperature tempSensor;

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
  tempSensor.begin(12); // begin on port 10
  Serial.println("Dallas Temperature IC Control Library 1.0. Miles Burton");
}



void loop(void) {

    // Validate device
    switch(tempSensor.isValid())
    {
        case 1:
            Serial.println("Invalid CRC");
            return;
        case 2:
            Serial.println("Not a valid device");
            return;
    }

  Serial.print(tempSensor.getTemperature());
  Serial.print("C");
  Serial.println();
  Serial.print(DallasTemperature::toFahrenheit(tempSensor.getTemperature()));
  Serial.print("F");
  Serial.println();
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

