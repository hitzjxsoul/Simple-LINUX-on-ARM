#include "DallasTemperature.h"


extern "C" {
#include <string.h>
#include <stdlib.h>
#include "WConstants.h"
}

#define DS18S20MODEL 0x10       // Model ID
#define DS18B20MODEL 0x28       // Model ID
#define DS1822MODEL 0x22       // Model ID

#define STARTCONVO 0x44         // Initalises slaves
#define COPYSCRATCH 0x48 		// Copy EEPROM
#define READSCRATCH 0xBE 		// Read EEPROM
#define WRITESCRATCH 0x4E 		// Write to EEPROM
#define TEMPCOMMAND 0xBE 		// Request temperature
#define RECALLSCRATCH 0xB8 		// Reload from last known

// Slave validation
#define INVALIDCRC 1
#define INVALIDMODEL 2
#define SLAVEGOOD 0

DallasTemperature::DallasTemperature(StratBase* pTBase)
{
  // Allow user to pass in a strategy if required
  if(pStratBase != 0) pStratBase = pTBase;

    // Warning: Nothing will be defined
}


// Start the interface with a new instance of NewOneWire
void DallasTemperature::begin(uint8_t wirePin)
{
 pDataWire = new NewOneWire(wirePin); // Instance object
 reset();

}


// Initalise with a reference to one wire
void DallasTemperature::begin(NewOneWire& NewOneWireRef)
{
  pDataWire = &NewOneWireRef;
  reset();
}


// Search the 1-wire interface for sign of our little device
void DallasTemperature::searchWire(void)
{
  initArr();

  if (!pDataWire->search(arSlaveAddr)){
    pDataWire->reset_search();
    return;
  } // Note: this is enumerating
}

// Return one wire instance if required
NewOneWire DallasTemperature::getNewOneWireInstance(void)
{
    return *pDataWire;
}


// Initalise arrays
void DallasTemperature::initArr(void)
{
  // init array
  for(int i=0;i<8;i++)     arSlaveAddr[i] = 0xFF;
}

// Send command
void DallasTemperature::beginCommunication(void)
{
  pDataWire->reset();
  pDataWire->select(arSlaveAddr);
  pDataWire->write(STARTCONVO,1);	   // start conversion, with parasite power on at the end
  delay(1000);
}

// Send command
void DallasTemperature::requestTemperature(void)
{
  pDataWire->reset();
  pDataWire->select(arSlaveAddr);
  pDataWire->write(READSCRATCH);	   // Read Scratchpad
}

float DallasTemperature::getTemperature() // ~ Double word, expensive
{
    // If we're ready to rock, begin communication channel
    if(isValid()==SLAVEGOOD){
        beginCommunication();
    }else{
        return 0;
    }

    requestTemperature(); // Send appropriate command


  // Originally you would read all n bytes (12~). We only need the first two
  byte lowByte = pDataWire->read();
  byte highByte = pDataWire->read();


    // TODO: Doesn't consider negative.
  int reading = (highByte<<8) + lowByte; // Concat word

  //TODO fix me, should negate
  if (reading & 0x8000) reading = (reading ^ 0xffff) + 1; // 2's comp
  float temp = (6 * reading) + reading / 4;    // multiply by (100 * 0.0625) or 6.25


  return temp/100;    // Divide by 100 to gain decimal.

}

// Validate whether the current address is correct
int DallasTemperature::isValid(void)
{
  // Calculate Cycle-Redudancy-Check (ie: check the data is not invalid
  if ( NewOneWire::crc8( arSlaveAddr, 7) != arSlaveAddr[7]) {
    return INVALIDCRC;
  }

    if(!(arSlaveAddr[0] ==    DS18B20MODEL
    || arSlaveAddr[0] ==    DS18S20MODEL
    || arSlaveAddr[0] ==    DS1822MODEL
    )){
        return INVALIDMODEL;
    }

  // Return all good
  return SLAVEGOOD;

}

// Select and initalise appropriate strategy
int DallasTemperature::loadStrategy(void)
{
  switch(arSlaveAddr[0])
  {
   case DS18B20MODEL:
    pStratBase = new BSeries();
   break;
   // Allow fall through
   case DS18S20MODEL:
   case DS1822MODEL:
    pStratBase = new S20Series();
   break;
   default:
    return INVALIDMODEL;
   break;
  }

  return SLAVEGOOD;
}

// Fires a total reset (Useful for intermittant connections)
void DallasTemperature::reset(void)
{
    initArr(); // reset arrays
    searchWire();

    if(isValid()==SLAVEGOOD)
    {
        loadStrategy();
        beginCommunication();
    }
}

// Convert float celcius to fahrenheit
float DallasTemperature::toFahrenheit(float celcius)
{
    return (celcius*1.8)+32;
}

// MnetCS - Allocates memory for DallasTemperature. Allows us to instance a new object
void* DallasTemperature::operator new(unsigned int size) // Implicit NSS obj size
{
  void * p; // void pointer
  p = malloc(size); // Allocate memory
  memset((DallasTemperature*)p,0,size); // Initalise memory

  //!!! CANT EXPLICITLY CALL CONSTRUCTOR - workaround by using an init() methodR - workaround by using an init() method
  return (DallasTemperature*) p; // Cast blank region to NSS pointer
}

// MnetCS 2009 -  Unallocates the memory used by this instance
void DallasTemperature::operator delete(void* p)
{
  DallasTemperature* pNss =  (DallasTemperature*) p; // Cast to NSS pointer
  pNss->~DallasTemperature(); // Destruct the object

  free(p); // Free the memory
}
