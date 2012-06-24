#ifndef DallasTemperature_h
#define DallasTemperature_h

/*
	DallasTemperature.h -  Dallas Temperature Control Library 1.0.0
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

*/
#include <inttypes.h>

#include "NewOneWire.h"

// Strategies to calculate tempreture for specific device
#include "StratBase.h" // Base Strategy
#include "BSeries.h"   // Concrete Strat for 'b' series
#include "S20Series.h" // Concrete strat for S and '20' series
// The measurement we're taking

class DallasTemperature
{
	private:

	NewOneWire* pDataWire;  	    // One Wire Instance (a copy of)
    uint8_t arSlaveAddr[8];    // 64bit address of device

    // I wont justify this
    void searchWire();

    // Send request temperature command
    void requestTemperature();

    // initalise arrays
    void initArr();

    // Initalise 1-wire communication
    void beginCommunication();

    // Pointer to temperature strategy
    StratBase* pStratBase;

    // Load appropriate strat
    int loadStrategy(); // Returns invalid model or good [-1]

	public:
    DallasTemperature(StratBase* = 0); // Strategy

    // Process temperature in given format (default is C*)
    float getTemperature();

    // Initalise to pin
	void begin(uint8_t);

    // is the slave valid
    int isValid(); // strangely, 0 is "GOOD"

    // reset everything. Useful if you knock the power cable etc
    void reset();

	// Begin with existing instance if 'NewOneWire' - could be useful
	void begin(NewOneWire&);

    // Allow user to repurpose onewire
	NewOneWire getNewOneWireInstance();

    // Convert from celcius to farenheit if required
    static float toFahrenheit(float);

    void* operator new (unsigned int size); // Initalise memory area
    void operator delete(void* p); // delete memory reference
};
#endif
