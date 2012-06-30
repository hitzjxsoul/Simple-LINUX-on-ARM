#ifndef NewOneWire_h
#define NewOneWire_h

#include <OneWire.h>

/*
	NewOneWire.H - Dallas Temperature Control Library 1.0.0
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

    This class extends the OneWire library to enable the new/delete operator for dynamic instantiation
 */

class NewOneWire : public OneWire
{
	public:

    NewOneWire(uint8_t pin);

     // MnetCS 2009 - Allow OW to construst and destrust dynamically (useful for object composition)
     void* operator new (unsigned int size);
     void operator delete(void* p); // delete memory reference
};
#endif
