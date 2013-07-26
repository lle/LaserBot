void randomMotorState()
{
	motorState = randomize()%2;
	PORTB = motorState;
}

void forward()
{
	PORTC &= ~(1<<PC0);
	PORTC |= (1<<PC1);

	PORTC &= ~(1<<PC6);
	PORTC |= (1<<PC7);
}

void reverse()
{
	PORTC |= (1<<PC0);
	PORTC &= ~(1<<PC1);

	PORTC |= (1<<PC6);
	PORTC &= ~(1<<PC7);
}

void right()
{
	PORTC &= ~(1<<PC0);
	PORTC |= (1<<PC1);

	PORTC &= ~(1<<PC6);
	PORTC &= ~(1<<PC7);
}


void left()
{
	PORTC &= ~(1<<PC0);
	PORTC &= ~(1<<PC1);

	PORTC &= ~(1<<PC6);
	PORTC |= (1<<PC7);
}

void spinCW()
{
	PORTC |= (1<<PC0);
	PORTC &= ~(1<<PC1);

	PORTC &= ~(1<<PC6);
	PORTC |= (1<<PC7);
}

void spinCCW()
{
	PORTC &= ~(1<<PC0);
	PORTC |= (1<<PC1);

	PORTC |= (1<<PC6);
	PORTC &= ~(1<<PC7);
}

void stop()
{
	PORTC &= ~(1<<PC0);
	PORTC &= ~(1<<PC1);

	PORTC &= ~(1<<PC6);
	PORTC &= ~(1<<PC7);
}


void setMotorState(int state)
{
	switch (state)
	{
		case 1:
			forward();
			break;
		case 2:
			reverse();
			break;
		case 3:
			right();
			break;
		case 4:
			left();
			break;
		case 5:
			spinCW();
			break;
		case 6:
			spinCCW();
			break;
		default:
			reverse();
			break;
	}
}
