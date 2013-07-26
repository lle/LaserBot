#include <avr/io.h>

#define F_CPU 8000000
#define SERVO_ICR 10000
//servoB is up-down and servoA is left-right
#define SERVO_1A_MAX 970	//absolute max = 980
#define SERVO_1A_MIN 890	//absolute min = 880
#define SERVO_1B_MAX 935	//absolute max = 980
#define SERVO_1B_MIN 925	//absolute min = 880
#define SERVO_1A_MID (uint16_t)(SERVO_1A_MIN+SERVO_1A_MAX)/2
#define SERVO_1B_MID (uint16_t)(SERVO_1B_MIN+SERVO_1B_MAX)/2
#define motorPWM 80;

volatile int motorState = 0;
volatile int angle1 = 1;
volatile int angle2 = 1;
volatile int interruptCount = 0;
volatile int interruptCount2 = 0;
volatile int speedFactor = 2;

#include <util/delay.h>
#include <stdlib.h>
#include "randomize.h"
#include "servoControl.h"
#include "motorControl.h"
#include "debug.h"
#include <avr/interrupt.h>

void setInterrupt();
void checkInput();

int main(void) 
{
	//set pins
	PORTB=0x00;
	DDRB=0xFF;	//output
	DDRC=0xFF;
	DDRD=0x00;	//input
	
	boottest();
	PORTB=0x00;
	setPWM1();
	setPWM2();
	setInterrupt();

	int stateRotate	= 0;	//this variable handles the movement of the servo left-right and remove variable 'angle1'
	while(1)
	{
		if(stateRotate)	//used to be: if(OCR1A<angle1)
		{
			OCR1A+=1;
			if(OCR1A>SERVO_1A_MAX)
				stateRotate = 0;
		}
		else	//used to be if(OCR1A>angle1)
		{
			OCR1A-=1;
			if(OCR1A<SERVO_1A_MIN)
				stateRotate = 1;
		}
		/*else
		{
			angle1 = SERVO_1A_MIN + (randomize()% (uint16_t)((SERVO_1A_MAX-SERVO_1A_MIN)/1) );
		}*/

		if(OCR1B<angle2)
		{
			OCR1B+=1;
		}
		else if(OCR1B>angle2)
		{
			OCR1B-=1;
		}
		else
		{
			//angle2 = SERVO_1B_MIN + (randomize()% (uint16_t)((SERVO_1B_MAX-SERVO_1B_MIN)/1) );
		}
		
		checkInput();
		_delay_ms(10*speedFactor);
	}


}

void setInterrupt()
{	
	cli();
	OCR0B = 255;
	TCCR0A = 0x40;
	TCCR0B = 0x09; //start Timer
	MCUCR = 0x00;
	TIMSK0 = 0x04; //timer interrupt sources
	sei(); 
}

void checkInput()
{
	if(PINA>=32)
	{
		speedFactor = 1;
	}
	else if(PINA>=16)
	{
		speedFactor = 2;
	}
	else if(PINA>=8)
	{
		speedFactor = 3;
	}
	else if(PINA>=4)
	{
		speedFactor = 4;
	}
	else if(PINA>=2)
	{
		speedFactor = 5;
	}
	else if(PINA>=1)
	{
		speedFactor = 6;
	}
	else
	{
		speedFactor = 7;
	}
	//PORTB = PINA;
}

ISR(TIMER0_COMPB_vect) 
{ 
	
	interruptCount++;
	interruptCount2++;

	if (interruptCount==3000*speedFactor)
	{
		angle1 = SERVO_1A_MIN + (randomize()% (uint16_t)((SERVO_1A_MAX-SERVO_1A_MIN)/1) );
		angle2 = SERVO_1B_MIN + (randomize()% (uint16_t)((SERVO_1B_MAX-SERVO_1B_MIN)/1) );
		interruptCount=0;
	}

	if (interruptCount2==30000)
	{
		randomMotorState();
		setMotorState(motorState);
		interruptCount2=0;
	}

	//PORTB = angle1;
} 
