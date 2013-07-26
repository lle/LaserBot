//	Take a look one day:
//	http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=52601&start=0

void setPWM1()
{
	DDRD |= (1<<PD4) | (1<<PD5);    
	
	TCCR1B |= (0<<WGM13) | (0<<WGM12); 
	TCCR1A |= (1<<WGM11) | (1<<WGM10) | (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0); 
	TCCR1B |= (1<<CS11) | (1<<CS10); 

	TCNT1 = 1; 
	ICR1 = SERVO_ICR;
	OCR1A = SERVO_1A_MID;
	OCR1B = SERVO_1B_MID;
}

void setPWM2()
{
	DDRD |= (1<<PD7);    

	TCCR2B |= (0<<WGM22); 
	TCCR2A |= (1<<WGM21) | (1<<WGM20) | (1<<COM2A1) | (0<<COM2A0) | (1<<COM2B1) | (0<<COM2B0);
	TCCR2B |= (1<<CS21) | (1<<CS20); 

	//ICR2 = icr;
	TCNT2 = 1;
	OCR2A = motorPWM
	OCR2B = motorPWM;
}

void checkOCRa(int min, int max)
{
	if(OCR1A>max)
		OCR2A=max;
	else if(OCR1A<min)
		OCR2A=min;
}

void checkOCRb(int min, int max)
{
	if(OCR1A>max)
		OCR2B=max;
	else if(OCR1A<min)
		OCR2B=min;
}
