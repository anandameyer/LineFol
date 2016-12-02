#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000

#define p1 0x01
#define p2 0x02
#define p3 0x04
#define p4 0x08
#define p5 0x10
#define p6 0x20
#define p7 0x40
#define p8 0x80
#define nol 0x00

#define A DDRA
#define B DDRB
#define C DDRC
#define D DDRD

#define OUTPUT 0x01
#define INPUT 0x00
#define SINGLE 0x02

#define HIGH 0x01
#define LOW 0x00


unsigned int a, b, c, d, e, f, g, h;
int pin,mode,state;
char port;

int io(mode,a, b, c, d, e, f, g, h)
{
	if(mode == 1 || mode == 2)
	{
		return a | b | c | d | e | f | g | h;
	}
	else if(mode == 0)
	{
			
		return (~a) | (~b) | (~c) | (~d) | (~e) | (~f) | (~g) | (~h);
	}
}
	
int setMode(port, pin)
	{
			if(port == 'A'){return DDRA = pin;}
			else if(port == 'B'){return DDRB = pin;}
			else if(port == 'C'){return DDRC = pin;}
			else if(port == 'D'){return DDRD = pin;}
	}
	
int readIO(port, pin)
	{
		if(port == 'A'){return PINA & pin;}
		else if(port == 'B'){return PINB & pin;}
		else if(port == 'C'){return PINC & pin;}
		else if(port == 'D'){return PIND & pin;}
	}
	
int writeIO(port,pin,state)		
	{
		if(state == 1)
		{
			if(port == 'A'){return PORTA = pin;}
			else if(port == 'B'){return PORTB = pin;}
			else if(port == 'C'){return PORTC = pin;}
			else if(port == 'D'){return PORTD = pin;}
		}
			
		if(state == 0)
		{
			if(port == 'A'){return PORTA = ~pin;}
			else if(port == 'B'){return PORTB = ~pin;}
			else if(port == 'C'){return PORTC = ~pin;}
			else if(port == 'D'){return PORTD = ~pin;}
		}
	}
	
	

void main ()
{
	int TLeft, TRight, MForward, center, outer, left, right, sensor, motor, STOP, all;
	sensor = io(INPUT,p1,p2,p3,p4);
	setMode('C',sensor);
	
	center = io(SINGLE,p2,p3);
	outer = io(SINGLE,p1,p4);
	left = io(SINGLE,p1,p2);
	right = io(SINGLE,p3,p4);
	all = io(SINGLE,p1,p2,p3,p4);
	
	motor = io(OUTPUT,p5,p6,p7,p8);
	setMode('A',motor);
	
	TLeft = io(SINGLE,p2,p3);
	TRight = io(SINGLE,p1,p4);
	MForward = io(SINGLE,p1,p3);
	STOP = io(SINGLE,p1,p2,p3,p4);
	
	writeIO('A',motor,LOW);
	
	while(1)
	{
		
		if(readIO('C',center) == LOW || (readIO('C',center) == LOW && readIO('C',outer) == HIGH))
		{
			writeIO('A',MForward,HIGH);
		};
		
		if(readIO('C',left) == LOW || readIO('C',right) == LOW)
		{
			if(readIO('C',left) == LOW)
			{
				writeIO('A',TLeft,HIGH);
			}
			
			if(readIO('C',right) == LOW)
			{
				writeIO('A',TRight,HIGH);
			}	
		}
		
		if(readIO('C',all) == HIGH)
		{
			writeIO('A',STOP,LOW);
		};
	}
}