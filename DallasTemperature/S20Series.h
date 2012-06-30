#ifndef S20Series_h
#define S20Series_h

/*
	S20Series.H - Dallas Temperature Control Library 1.0.0
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

    Provides implementation for the DS18S20 & DS1820 Series of temperature IC
 */
#include "StratBase.h"

class S20Series : public StratBase
{
	public:
	S20Series(void);

	float getTemperature(NewOneWire* pDataWire);

	void* operator new (unsigned int size); // Initalise memory area
    void operator delete(void* p); // delete memory reference
};
#endif
