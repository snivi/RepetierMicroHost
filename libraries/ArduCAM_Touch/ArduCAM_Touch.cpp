/*
  ArduCAM_Touch.cpp - Arduino library support for ArduCAM Touch function
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

#define PixSizeX	-6.93
#define PixOffsX	171
#define PixSizeY	4.90
#define PixOffsY	222

#include "Arduino.h"
#include "ArduCAM_Touch.h"
#include <avr/pgmspace.h>
#include <SPI.h>

ArduCAM_Touch::ArduCAM_Touch(byte tcs,byte irq)
{
		T_IRQ = irq;
		T_CS  = tcs;
    SPI.begin();
}

void ArduCAM_Touch::InitTouch(byte orientation)
{
	orient = orientation;
	pinMode(T_CS,   OUTPUT);
	pinMode(T_IRQ,  INPUT);
	digitalWrite(T_CS,  HIGH);
}

void ArduCAM_Touch::touch_WriteData(byte data)
{
	SPI.transfer(data);
}

word ArduCAM_Touch::touch_ReadData()
{
	byte nop = 0;
	word data;
	data = SPI.transfer(nop);
	data = data << 8;
	data |= SPI.transfer(nop);
	data = data >> 4;
	return(data);
}

void ArduCAM_Touch::read()
{
	unsigned long tx=0;
	unsigned long ty=0;

	digitalWrite(T_CS,LOW);                    

	for (int i=0; i<prec; i++)
	{
		touch_WriteData(0x90);        
		ty+=touch_ReadData();

		touch_WriteData(0xD0);      
		tx+=touch_ReadData();
		
	}

	digitalWrite(T_CS,HIGH);

	TP_X=tx/prec;
	TP_Y=ty/prec;
	
}

bool ArduCAM_Touch::dataAvailable()
{
  bool avail;
  avail = !digitalRead(T_IRQ);
  return avail;
}

int ArduCAM_Touch::getX()
{
	int value;

	if (orient == PORTRAIT)
	{
		if (PixSizeX>=0)
		{
			value = 240-((TP_X-PixOffsX)/PixSizeX);
		}
		else
		{
			value = (TP_X-PixOffsX)/-(PixSizeX);
		}
	}
	else
	{
		if (PixSizeY<0)
			value = 400-((TP_Y-PixOffsY)/-PixSizeY);
		else
			value = ((TP_Y-PixOffsY)/PixSizeY);
	}

	if (value < 0)
		value = 0;
	return value;
}

int ArduCAM_Touch::getY()
{
	int value;

	if (orient == PORTRAIT)
	{
		if (PixSizeY<0)
			value = ((TP_Y-PixOffsY)/-PixSizeY);
		else
			value = 320-((TP_Y-PixOffsY)/PixSizeY);
	}
	else
	{
		if (PixSizeX>=0)
		{
			value = 240-((TP_X-PixOffsX)/PixSizeX);
		}
		else
		{
			value = (TP_X-PixOffsX)/-(PixSizeX);
		}
	}

	if (value < 0)
		value = 0;
	return value;  
}

void ArduCAM_Touch::setPrecision(byte precision)
{
	switch (precision)
	{
		case PREC_LOW:
			prec=1;
			break;
		case PREC_MEDIUM:
			prec=10;
			break;
		case PREC_HI:
			prec=25;
			break;
		case PREC_EXTREME:
			prec=100;
			break;
		default:
			prec=10;
			break;
	}
}