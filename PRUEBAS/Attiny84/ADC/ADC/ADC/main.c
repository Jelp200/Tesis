/*
** #########################################################################################
**  Archivo         :   main.c
**  Proyecto        :   Tesis
**  Herramienta(s)  :   Microchip Studio
**  Compilador      :   C/C++ Compiler
**  Autores         :
**                      Jorge E. Pena P.
**  Descripcion     :
**                      Configuracion ADC
** #########################################################################################
*/

#define F_CPU 1000000UL  //* Definicion de la frecuencia del reloj (1 MHz)

#include <avr/io.h>

//* FUNCIONES
void pin_Setup() {
    //* Configuracion pin salida
	DDRA |= (1 << DDA0);					    // PA0 como salida
}

void ADC_Setup() {
    //* Configuracion del registro de ADC de seleccion de multiplexor
    ADMUX = 0x01;                               // Vcc como referencia, ADC1 como canal de entrada

    //* Configuracion del regitro A de control y status del ADC
    ADCSRA = 0x83;                              // ADC habilitado, con prescaler igual a 8 (125kHz)
}

int main(void) {
    pin_Setup();
    ADC_Setup();

    while (1) {
        //* Inicia una nueva conversion
        ADCSRA |= (1 << ADSC);

        //* Espera a que termine la conversion
        while (ADCSRA & (1 << ADSC));           // Espera a que ADSC se limpie (conversion completa)


        //* Lee el valor del ADC (10 bits combinando ADCH y ADCL)
        int ADC_Low = ADCL;                     // Lee primero ADCL (8 bits bajos)
        int ADC_Val = (ADCH << 8) | ADC_Low;    // Combina ADCH y ADCL en un valor de 10 bits

        // Si el valor del ADC esta dentro del rango deseado, enciende el LED
        if (ADC_Val >= 410 && ADC_Val <= 1000) { // Prende si el valor del ADC es (2V, ~5V)
            PORTA |= (1 << PORTA0);  // Enciende el LED
        } else {
            PORTA &= ~(1 << PORTA0);  // Apaga el LED
        }
    }
}