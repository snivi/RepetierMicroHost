/*
  ArduCAM_Touch.h - Arduino library support for ArduCAM Touch function
  Copyright (C)2010 www.ArduCAM.com. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ArduCAM. You can find the latest version of the library at
  http://www.ArduCAM.com

  
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

  Version:   1.0  - Dec  21 2012  - initial release

*/



#ifndef ArduCAM_Touch_h
#define ArduCAM_Touch_h

#include "Arduino.h"

#define PORTRAIT	0
#define LANDSCAPE	1

#define PREC_LOW		1
#define PREC_MEDIUM		2
#define PREC_HI			3
#define PREC_EXTREME	4

class ArduCAM_Touch
{
	public:
		word	TP_X ,TP_Y;

				ArduCAM_Touch( byte tcs, byte irq);

		void	InitTouch(byte orientation = PORTRAIT);
		void	read();
		bool	dataAvailable();
		int		getX();
		int		getY();
		void	setPrecision(byte precision);
    
    private:
		byte	T_CS, T_IRQ;
		byte	orient;
		byte	prec;

		void	touch_WriteData(byte data);
		word	touch_ReadData();
};

#endif