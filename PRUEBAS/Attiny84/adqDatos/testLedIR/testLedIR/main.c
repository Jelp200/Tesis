/*
** #########################################################################################
**  Archivo         :   main.c
**  Proyecto        :   Tesis
**  Herramienta(s)  :   Microchip Studio
**						Visual Studio Code
**  Compilador      :   C/C++ Compiler
**  Autores         :
**                      Jorge E. Pena P.
**						Juan Lopez A.
**  Descripcion     :
**                      Testeo de LED IR (Infrarrojo) para la placa final del dispositivo de
**						medicion PPG
** #########################################################################################
*/

//* DEFINICION VELOCIDAD DE RELOJ
#define	F_CPU	1000000UL

//* DIRECTIVAS DE PREPROCESADOR
#include <avr/io.h>

int main(void) {
	DDRA |= (1 << DDA0);					// PA0 como salida
	DDRA |= (1 << DDA1);					// PA1 como salida
	
    /* BUCLE PRINCIPAL */
    while(1) {
		PORTA |= (1 << PORTA0);				// Pin 13 fisico encendido
		PORTA |= (1 << PORTA1);				// Pin 12 fisico encendido
    }
}

