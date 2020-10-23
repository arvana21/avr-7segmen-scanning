/*
 * Created: 10/20/2020 6:36:41 PM
 * Author : Dwi Setia Fardhana
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

const uint8_t SevenSegmen[] = {
	0b11000000,			//display 7 segment angka 0
	0b11111001,			//display 7 segment angka 1
	0b10100100,			//display 7 segment angka 2
	0b10110000,			//display 7 segment angka 3
	0b10011001,			//display 7 segment angka 4
	0b10010010,			//display 7 segment angka 5
	0b10000010,			//display 7 segment angka 6
	0b11111000,			//display 7 segment angka 7
	0b10000000,			//display 7 segment angka 8
	0b10010000,			//display 7 segment angka 9
	0b11111111,			//display 7 segment mati
};

#define __DELAY__ 1	//mendefinisikan waktu delay scanning 1ms
#define __KANAN__ 1 //mendefinisikan arah scan dari kiri ke kanan
#define __KIRI__ 0 //mendefinisikan arah scan dari kanan ke kiri

// Deklarasi Fungsi Static Void dengan parameter nilai default 0b11111111 
static void scanSvnSegmen(uint8_t arahScan = __KIRI__, uint8_t digitA = SevenSegmen[10], uint8_t digitB = SevenSegmen[10],  uint8_t digitC = SevenSegmen[10],  uint8_t digitD = SevenSegmen[10]){
	for(uint8_t i = 0; i < __DELAY__ * 4 ; i++) {
		//jika arah ke kanan (kanan ke kiri)
		if (arahScan == 1) {
					
			PORTB |= (1 << PB3);
			PORTC = ~digitA;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB3);
						
			PORTB |= (1 << PB2);
			PORTC = ~digitB;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB2);			
						
			PORTB |= (1 << PB1);
			PORTC = ~digitC;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB1);
						
			PORTB |= (1 << PB0);
			PORTC = ~digitD;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB0);
		}
		//Ke kiri
		else {
			PORTB |= (1 << PB0);
			PORTC = digitA;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB0);
			
			PORTB |= (1 << PB1);
			PORTC = digitB;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB1);
			
			PORTB |= (1 << PB2);
			PORTC = digitC;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB2);
			
			PORTB |= (1 << PB3);
			PORTC = digitD;
			_delay_ms(__DELAY__);
			PORTB &= ~(1 << PB3);
			
		}
		
	}
	
}

int main(void){
	DDRB  = 0xFF; //Port B sebagai OUTPUT
	DDRC  = 0xFF; //Port C sebagai OUTPUT
	while (1)
	{
		scanSvnSegmen(__KIRI__);
		scanSvnSegmen(__KIRI__, SevenSegmen[1]);
		scanSvnSegmen(__KIRI__, SevenSegmen[2], SevenSegmen[1]);
		scanSvnSegmen(__KIRI__, SevenSegmen[3], SevenSegmen[2], SevenSegmen[1]);
		scanSvnSegmen(__KIRI__,	SevenSegmen[4], SevenSegmen[3], SevenSegmen[2], SevenSegmen[1]); 
	}
}

