/*
	BSeries.CPP - Dallas Temperature Control Library 1.0.0
 	Author: Miles Burton, miles@mnetcs.com
 	Copyright (c) 2009 Miles Burton All Rights Reserved

 	This library is free software; you can redistribute it and/or
 	modify it under the terms of the GNU Lesser General Public
 	License as published by the Free Software Foundation; either
 	version 2.1 of the License, or (at your option) any later version.

 	This library is distributed in the hope that it will be useful,
 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 	Lesser General Public License for more details.

 	You should have received a copy of the GNU Lesser General Public
 	License along with this library; if not, write to the Free Software
 	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 	This code has been derived from: http://www.arduino.cc/playground/Learning/OneWire. Unknown author, unknown date

    Provides implementation for the DS18B20 Series of temperature IC
 */

#include "BSeries.h"

// Factor out these later
extern "C" {
#include <string.h>
#include <stdlib.h>
#include "WConstants.h"
#include <avr/io.h>
#include "pins_arduino.h"
}


BSeries::BSeries():StratBase(){}

float BSeries::getTemperature(NewOneWire* pDataWire)
{
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

// MnetCS - Allocates memory for NewSoftSerial. Allows us to instance a new object
void* BSeries::operator new(unsigned int size) // Implicit NSS obj size
{
  void * p; // void pointer
  p = malloc(size); // Allocate memory
  memset((BSeries*)p,0,size); // Initalise memory

  //!!! CANT EXPLICITLY CALL CONSTRUCTOR - workaround by using an init() methodR - workaround by using an init() method
  return (BSeries*) p; // Cast blank region to NSS pointer
}

// MnetCS 2009 -  Unallocates the memory used by this instance
void BSeries::operator delete(void* p)
{
  BSeries* pNss =  (BSeries*) p; // Cast to NSS pointer
  pNss->~BSeries(); // Destruct the object

  free(p); // Free the memory
}
