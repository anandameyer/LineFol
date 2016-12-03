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

int io(mode, a, b, c, d, e, f, g, h)
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
	
int setMode(char port, int pin)
	{
			if(port == 'A'){return DDRA = pin;}
			else if(port == 'B'){return DDRB = pin;}
			else if(port == 'C'){return DDRC = pin;}
			else if(port == 'D'){return DDRD = pin;}
	}
	
int readIO(char port, int pin)
	{
		if(port == 'A'){return PINA & pin;}
		else if(port == 'B'){return PINB & pin;}
		else if(port == 'C'){return PINC & pin;}
		else if(port == 'D'){return PIND & pin;}
	}
	
int writeIO(char port,int pin,int state)		
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