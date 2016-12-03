#include<avr/io.h>
#include<util/delay.h>
#include"simpleIO.h"

void main()
{
	int test = io(SINGLE,p1,p2,p3,p4);
	setMode('A',test);
	
	while(1)
	{
		writeIO('A', test, HIGH);
		_delay_ms(500);
		writeIO('A', test, LOW);
		_delay_ms(500);
		
	}
}