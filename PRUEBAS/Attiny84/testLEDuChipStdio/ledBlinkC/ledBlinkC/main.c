/*
 * ledBlinkC.c
 *
 * Created: 29/09/2024 07:18:53 p. m.
 * Author : nikob
 */ 

#define F_CPU	1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//* Pin PA0 como salida
	DDRA |= (1 << DDA0);
	DDRA |= (1 << DDA1);
	
	
    /* Replace with your application code */
    while (1) 
    {
		PORTA |= (1 << PORTA1);
		PORTA |= (1 << PORTA0);				// Pin alto (LED encendido)
		_delay_ms(3000);					// 1s delay
		PORTA &= ~(1 << PORTA0);			// Pin bajo (LED apagado)
		_delay_ms(3000);					// 1s delay
    }
}

