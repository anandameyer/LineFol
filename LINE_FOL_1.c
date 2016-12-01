#define F_CPU 16000000
#include <avr/inOut.h>
#include <util/delay.h>

#define hidup true
#define mati false
#define high 1
#define low 0

#define p1 0x01
#define p2 0x02
#define p3 0x04
#define p4 0x08
#define p5 0x10
#define p6 0x20
#define p7 0x40
#define p8 0x80
#define nol 0x00

#define input(port,value) port=(!value)
#define output(port,value) port=value


#define A DDRA
#define B DDRB
#define C DDRC
#define D DDRD

#define pA PORTA
#define pB PORTB
#define pC PORTC
#define pD PORTD

#define inA PINA
#define inB PINB
#define inC PINC
#define inD PIND

uint8_t a, b, c, d, e, f, g, h,port,pin;
bool status;

int8_t inOut(a=nol,b=nol,c=nol,d=nol,e=nol,f=nol,g=nol,h=nol)
	{
		return a|=b|=c|=d|=e|=f|=g|=h;
	}
	
int8_t out(port,pin,status)
	{
		if(status)
		{
			return port|=pin;
		}
		else
		{
			return port^=pin;
		}
	}
	
uint8_t in(port,pin)
	{
		return port&pin;
	}



void main (void)
{
	uint8_t kiri, kanan, maju, sensor, sensor_dalam, sensor_luar, sensor_kiri, sensor_kanan, motor;
	sensor = inOut(p1,p2,p3,p4);
	input(C,sensor);
	
	sensor_dalam = inOut(p2,p3);
	sensor_luar = inOut(p1,p4);
	sensor_kiri = inOut(p1,p2);
	sensor_kanan = inOut(p3,p4);
	
	motor = inOut(p5,p6,p7,p8);
	output(A,motor);
	
	kiri = inOut(p2,p3);
	kanan = inOut(p1,p4);
	maju = inOut(p1,p3);
	
	out(pA,motor,mati);
	
	while(1)			 //Intruksi yang akan di jalankan secara berulang-ulang
	{
		
		if(in(inC,sensor) == low || (in(inC,sensor_dalam) == low && in(inC,sensor_luar) == high))
		{
			out(pA,maju,hidup);
		};
		
		if(in(inC,sensor_kiri) == low || in(inC,sensor_kanan) == low)
		{
			if(in(inC,sensor_kiri) == low)
			{
				out(pA,motor,hidup);
			};
			if(in(inC,sensor_kanan) == low)
			{
				out(pA,motor,hidup);
			};
		};
		
		if(in(inC,sensor) == high)
		{
			out(pA,motor,mati);
		};
	}
}