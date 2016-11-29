#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define sensL PIND&0x01 //sensor kiri pin PD0
#define sensR PINC&0x01 //sensor kanan pin PC0


void main (void)
{
	uint8_t LSENS,RSENS,L,R,S,F; //variabel untuk menampung nilai sensor
	LSENS = RSENS = L = R = S = F = 0;
	DDRA = 0xff;		 //Set semua Pin PA menjadi Output
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