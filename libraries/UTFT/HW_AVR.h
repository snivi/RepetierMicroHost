// *** Hardwarespecific functions ***
void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)
{   
	switch (mode)
	{
	case 1:
		if (display_serial_mode==SERIAL_4PIN)
		{
		if (VH==1)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		}
		else
		{
		if (VH==1)
			sbi(P_RS, B_RS);
		else
			cbi(P_RS, B_RS);
		}

		if (VL & 0x80)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x40)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x20)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x10)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x08)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x04)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x02)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x01)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		break;
	case 8:
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		//PORTA = VH;
		//PH4 PH3 PE3 PG5 PE5 PE4 PE1 PE0	

		PORTH = ((VH & 0xC0) >> 3);
		PORTE = ((VH & 0x20) >> 2);
		PORTG = ((VH & 0x10) << 1);
		PORTE |= ((VH & 0x0C) << 2);
		PORTE |= ((VH & 0x03));
		pulse_low(P_WR, B_WR);
		
		//PORTA = VL;
		
		PORTH = ((VL & 0xC0) >> 3);
		PORTE = ((VL & 0x20) >> 2);
		PORTG = ((VL & 0x10) << 1);
		PORTE |= ((VL & 0x0C) << 2);
		PORTE |= ((VL & 0x03));
		pulse_low(P_WR, B_WR);
#else
		PORTD = VH;
		pulse_low(P_WR, B_WR);
		PORTD = VL;
		pulse_low(P_WR, B_WR);
#endif
		break;
	case 16:
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		//not support for this module
#else
		//not support for this module
#endif

		break;
	}
}

void UTFT::_set_direction_registers(byte mode)
{
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	DDRA = 0xFF;
	if (mode==16)
		DDRC = 0xFF;
	//PH4 PH3 PE3 PG5 PE5 PE4 PE1 PE0	
	DDRH = 0x18;
	DDRE = 0x3B;
	DDRG = 0x20;
#else
	DDRD = 0xFF;
	if (mode==16)
	{
		//DDRB |= 0x3F;
		//DDRC |= 0x03;
	}
#endif

}
