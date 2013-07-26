volatile int romAdr = 0x00;

void boottest()
{
	PORTB = 0x00;
	_delay_ms(500);
	for(int i=1; i<255; i=i*2)
	{
		PORTB = i;
		_delay_ms(50);
	}

}

void LEDB(int position)
{
	PORTB = (0x01<<position);
}

void pwmInputTest()
{
	OCR1A = SERVO_1A_MID;
	OCR1B = SERVO_1B_MID;	

	while(1)
	{
		while(!(PINA & (1<<PA1)))
		{
			OCR1A+=10;
			LEDB(0);
			_delay_ms(1000);
		}
		while(!(PINA & (1<<PA2)))
		{
			OCR1A-=10;
			LEDB(1);
			_delay_ms(1000);
		}
		while(!(PINA & (1<<PA3)))
		{
			OCR1B+=10;
			LEDB(2);
			_delay_ms(1000);
		}
		while(!(PINA & (1<<PA4)))
		{
			OCR1B-=10;
			LEDB(3);
			_delay_ms(1000);
		}
		PORTB = 0x00;
		
		/*
		if(OCR1A>=servoMax)
		{
			OCR1A = servoMax-10;
			PORTB = 0b11000000;
		}
		else if(OCR1B>=servoMax)
		{
			OCR1B = servoMax-10;
			PORTB = 0b00110000;
		}
		else if(OCR1A<=servoMin)
		{
			OCR1A = servoMin+10;
			PORTB = 0b00111000;
		}
		else if(OCR1B<=servoMin)
		{
			OCR1A = servoMin+10;
			PORTB = 0b00001110;
		}
		else
		{
			PORTB = 0x00;
		}
		*/

		_delay_ms(100);
	}
}

void infinitePwmTest()
{
	for(int i=SERVO_1A_MIN; i<SERVO_1A_MAX; i++)
	{
		OCR1A = i;
		OCR1B = i;
		_delay_ms(10);
	}

	while(1)
	{
		/*
		OCR1B = 15400;
		_delay_ms(500);
		OCR1B = 15500;
		_delay_ms(500);
		*/
		/*
		while(OCR1B<15500)	//top (max left)
		{
			OCR1B++;
			_delay_ms(10);
		}
		while(OCR1B>15400)	//bottom (max right)
		{
			OCR1B--;
			_delay_ms(10);
		}
		*/
	}
}

void infiniteMotorTest()
{
	while(1)
	{
		forward();
		_delay_ms(1000);
		reverse();
		_delay_ms(1000);
		right();
		_delay_ms(1000);
		left();
		_delay_ms(1000);
		spinCW();
		_delay_ms(1000);
		spinCCW();
		_delay_ms(1000);
		stop();
		_delay_ms(1000);
	}
}	

void debug()
{
	PORTB = 0x00;
	_delay_ms(100);
	PORTB = 0xFF;
	_delay_ms(100);
		PORTB = 0x00;
	_delay_ms(100);
}

int testRandom()
{
	return randomize(89);
}
