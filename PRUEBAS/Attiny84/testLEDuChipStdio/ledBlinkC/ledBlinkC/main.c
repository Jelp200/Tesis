/*
** #########################################################################################
**  Archivo         :   main.c
**  Proyecto        :   Tesis
**  Herramienta(s)  :   Microchip Studio
**  Compilador      :   C/C++ Compiler
**  Autores         :
**                      Jorge E. Peña P.
**  Descripcion     :
**                      Control de LED's (Fotorreceptor, fototransmisor, LED verde).
** #########################################################################################
*/

//* DEFINICIÓN DE VELOCIDAD DEL RELOJ (1MHz)
#define F_CPU	1000000UL

//* DIRECTIVAS DE PREPROCESADOR
#include <avr/io.h>
#include <util/delay.h>

//* FUNCIÓN PRINCIPAL
int main(void) {
	// Configuración de pines de salida
	DDRA |= (1 << DDA0);					// PA0 como salida
	DDRA |= (1 << DDA1);					// PA1 como salida
	DDRA |= (1 << DDA2);					// PA2 como salida
	
    /* Replace with your application code */
    while(1) {
		PORTA |= (1 << PORTA1);				// Pin 1 alto (LED siempre encendido)
		PORTA &= ~(1 << PORTA2);			// Pin 2 bajo (LED apagado)
		PORTA |= (1 << PORTA0);				// Pin 0 alto (LED encendido)
		_delay_ms(3000);					// 1s delay
		PORTA |= (1 << PORTA2);				// Pin 2 alto (LED encendido)
		PORTA &= ~(1 << PORTA0);			// Pin 0 bajo (LED apagado)
		_delay_ms(3000);					// 1s delay
    }
}

