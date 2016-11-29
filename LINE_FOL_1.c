#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define hidup true


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

#define pA PORTA
#define pB PORTB
#define pC PORTC
#define pD PORTD

class pin_select(){
public:
int io(a=nol,b=nol,c=nol,d=nol,e=nol,f=nol,g=nol,h=nol){
	return a|=b|=c|=d|=e|=f|=g|=h;
};
void out(port,pin,status){
if(status == true)
{
	return port|=pin;
}
else{
	return port^=pin;
};

}
void ~io();
private:
uint8_t a, b, c, d, e, f, g, h,port,pin;
bool status;
};

/*8		4		2		1		8		4		2		1*/

void main ()
{
	uint8_t LSENS,RSENS,L,R,S,F,sensor,motor; //variabel untuk menampung nilai sensor
	LSENS = RSENS = L = R = S = F = 0;
	
	pin_select pilih;
	sensor = pilih.io(p1,p2,p3,p4);
	input(C,sensor);
	
	motor = pilih.io(p5,p6,p7,p8);
	output(A,motor);
	
	out(motor,)
	
	PORTA = 0x00;		 //Set semua Pin PA menjadi output low
	DDRD = 0x00;		 //Set semua Pin PD menjadi input
	DDRC = 0x00;
	while(1)			 //Intruksi yang akan di jalankan secara berulang-ulang
	{
		LSENS = (sensL);//mengisi variabel dengan hasil baca digital input sensor
		_delay_ms(50);
		RSENS = (sensR);
		
		while((LSENS == 0) && (RSENS == 0)) //kondisi melaju
		{
			if ( L == 1 || R == 1 || S == 1 )
			{
				PORTA &= 0x00;
			}
			else 
			{
				PORTA |= 0b00000101; //Memberikan nilai output high pada pin PA
				_delay_ms(50);
			}
			
			F = 1;
			L = R = S = 0;
			break;
		}
		
		while((LSENS == 1) && (RSENS == 0)) //kondisi belok kanan
		{
			if ( L == 1 || F == 1 || S == 1 )
			{
				PORTA &= 0x00;		 //set semua pin PA menjadi low
				_delay_ms(10);
			}
			else
			{
				PORTA |= 0b00001001;
				_delay_ms(10);
			}
			R = 1;
			L = F = S = 0;
			break;
		}
		
		while((LSENS == 0) && (RSENS == 1)) //kondisi belok kiri
		{
			if( R == 1 || F == 1 || S == 1)
			{
				PORTA &= 0x00;
				_delay_ms(10);
			}
			else
			{
				PORTA |= 0b00000110;
				_delay_ms(10);
			}
			L = 1;
			R = F = S = 0;
			break;
		}
		
		while((LSENS == 1) && (RSENS == 1)) //kondisi berhenti
		{
			PORTA &= 0x00;
			_delay_ms(50);
			break;
		}
		
	}
}