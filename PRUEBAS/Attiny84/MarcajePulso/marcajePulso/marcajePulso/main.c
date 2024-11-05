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

//* PROTOTIPOS DE FUNCIONES
void pin_Setup();
void ADC_Setup();

//* FUNCION PRINCIPAL
int main(){
    pin_Setup();
    ADC_Setup();

    while(1){
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

//* FUNCIONES
void pin_Setup(){                                   // Configuracion de pines
    //! Configuracion de pines de salida
    DDRA |= (1 << DDA0);                            // PA0 como salida
    DDRA |= (1 << DDA1);                            // PA1 como salida
    DDRA |= (1 << DDA2);                            // PA2 como salida
}

void ADC_Setup(){                                   // Configuracion del ADC
    //* Configuracion del registro de ADC de seleccion de multiplexor
    ADMUX = 0x03;                                   // Vcc como referencia, ADC3 como canal de entrada

    //* Configuracion del regitro A de control y status del ADC
    ADCSRA = 0x83;                                  // ADC habilitado, con prescaler igual a 8 (125kHz)
}

