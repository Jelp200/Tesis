/*
** #########################################################################################
**  Archivo         :   main.c
**  Proyecto        :   Tesis
**  Herramienta(s)  :   Microchip Studio
**  Compilador      :   C/C++ Compiler
**  Autores         :
**                      Jorge E. Pena P.
**  Descripcion     :
**                      Control de LED's (Fotorreceptor y fototransmisor), funcionamiento
**						del ADC correctamente y marcaje de pulso con LED externo.
** #########################################################################################
*/

//* DEFINICION DE VELOCIDAD DE RELOJ
#define F_CPU   1000000UL                           // 1MHz

//* DIRECTIVAS DE PREPROCESADOR
#include <avr/io.h>
#include <util/delay.h>

//* FUNCION PRINCIPAL
int main(){
    //* Configuracion de pines de salida
    DDRA |= (1 << DDA0);                            // PA0 como salida
    DDRA |= (1 << DDA1);                            // PA1 como salida

    //* Configuracion del ADC
    // Configuracion del registro de ADC de seleccion de multiplexor
    ADMUX = 0b00000010;                             // Vcc como referencia, ADC2 como canal de entrada

    // Configuracion del regitro A de control y status del ADC
    ADCSRA = 0b10000011;                            // ADC habilitado, con prescaler igual a 8 (125kHz)

    while(1){
        //* LED's de marcaje del pulso
        PORTA |= (1 << PORTA0);                     // Pin 0 alto (LED Siempre Encendio)
        PORTA |= (1 << PORTA1);						// Pin 1 alto (LED Siempre Encendio)

        //* Inicia una nueva conversion
        ADCSRA |= (1 << ADSC);

        //* Espera a que termine la conversion
        while(ADCSRA & (1 << ADSC));                // Espera a que ADSC se limpie (conversion completa)

        //* Lee el valor del ADC (10 bits combinando ADCH y ADCL)
        int ADC_Low = ADCL;                         // Lee primero ADCL (8 bits bajos)
        int ADC_Val = (ADCH << 8) | ADC_Low;        // Combina ADCH y ADCL en un valor de 10 bits

        // Si el valor del ADC esta dentro del rango deseado, enciende el LED
        if (ADC_Val >= 410 && ADC_Val <= 615) {		// Prende si el valor del ADC es (2V, ~3V)
            PORTA |= (1 << PORTA2);                 // Enciende el LED
        } else {
            PORTA &= ~(1 << PORTA2);                // Apaga el LED
        }
    }
}
