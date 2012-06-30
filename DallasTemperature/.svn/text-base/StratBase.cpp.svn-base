/*
	StratBase.CPP - Dallas Temperature Control Library 1.0.0
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

    Provides the base interface for a temperature strategy, different devices have different precitions. Dependancy injection enables
    changability
 */

#include "StratBase.h"


// Factor out these later
extern "C" {
#include <string.h>
#include <stdlib.h>
#include "WConstants.h"
#include <avr/io.h>
#include "pins_arduino.h"
}


StratBase::StratBase(){}

float StratBase::getTemperature(NewOneWire* pDataWire)
{
    return 0;
}

// MnetCS - Allocates memory for NewSoftSerial. Allows us to instance a new object
void* StratBase::operator new(unsigned int size) // Implicit NSS obj size
{
  void * p; // void pointer
  p = malloc(size); // Allocate memory
  memset((StratBase*)p,0,size); // Initalise memory

  //!!! CANT EXPLICITLY CALL CONSTRUCTOR - workaround by using an init() methodR - workaround by using an init() method
  return (StratBase*) p; // Cast blank region to NSS pointer
}

// MnetCS 2009 -  Unallocates the memory used by this instance
void StratBase::operator delete(void* p)
{
  StratBase* pNss =  (StratBase*) p; // Cast to NSS pointer
  pNss->~StratBase(); // Destruct the object

  free(p); // Free the memory
}

