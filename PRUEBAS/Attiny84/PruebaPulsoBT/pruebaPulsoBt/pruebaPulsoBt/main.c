/*
** #########################################################################################
**  Archivo         :   main.c
**  Proyecto        :   Tesis
**  Herramienta(s)  :   Microchip Studio
**  Compilador      :   C/C++ Compiler
**  Autores         :
**                      Jorge E. Pena P.
**  Descripcion     :
**                      Marcaje de pulso y envio de voltaje v�a bluetooth.
** #########################################################################################
*/

//* DEFINICION DE LA VELOCIDAD DEL RELOJ
#define F_CPU   1000000UL                       // 1MHz

//* DIRECTIVAS DE PREPROCESADOR
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

int main(void) {	
	//* Configuraci�n de pines de salida
    DDRA |= (1 << DDA0);                        // PA0 como salida (LED infrarrojo)
	DDRA |= (1 << DDA3);                        // PA3 como salida

    //* Configuraci�n del ADC
    ADMUX = 0b00000010;                         // ADC2 como entrada (con referencia Vcc)
    ADCSRA = 0b10000011;                        // ADC habilitado, prescaler 8 (125kHz)
	
    /* Replace with your application code */
    while (1) {	
		//* Inicia una nueva conversion
        ADCSRA |= (1 << ADSC);

        //* Espera a que termine la conversion
        while (ADCSRA & (1 << ADSC));           // Espera a que ADSC se limpie (conversion completa)

        //* Lee el valor del ADC (10 bits combinando ADCH y ADCL)
        int ADC_Low = ADCL;                     // Lee primero ADCL (8 bits bajos)
        int ADC_Val = (ADCH << 8) | ADC_Low;    // Combina ADCH y ADCL en un valor de 10 bits
		
		PORTA |= (1 << PORTA0);
		
		// Si el valor del ADC esta dentro del rango deseado, enciende el LED
		if (ADC_Val >= 410 && ADC_Val <= 1000) { // Prende si el valor del ADC es (2V, ~5V)
			PORTA |= (1 << PORTA3);  // Enciende el LED
		} else {
		PORTA &= ~(1 << PORTA3);  // Apaga el LED
		}
	}
}
