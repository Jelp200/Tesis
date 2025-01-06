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

//* LIBRERIA PARA EMULAR TRX VIA UART
#include <SoftwareSerial.h>

//! Configuracion para los pines de TX y RX
#define RX_PIN 11                               // PB0 (Pin físico 3)
#define TX_PIN 12                               // PB1 (Pin físico 2)

//! Llamada a la funcion para comenzar la transmision
SoftwareSerial btSerial(RX_PIN, TX_PIN);        // RX, TX

//* DEFINICION DE LA VELOCIDAD DEL RELOJ
#define F_CPU   1000000UL                       // 1MHz

//* DIRECTIVAS DE PREPROCESADOR
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

//* Función para calcular el promedio (DC)
float calcular_DC(int *valores, int tamano) {
    float suma = 0;
    for (int i = 0; i < tamano; i++) {
        suma += valores[i];
    }
    return suma / tamano;
}

//* Función para calcular la amplitud AC
float calcular_AC(int *valores, int tamano, float DC) {
    float max_valor = 0, min_valor = 1023;      // Rango máximo para un ADC de 10 bits
    for (int i = 0; i < tamano; i++) {
        if (valores[i] > max_valor) max_valor = valores[i];
        if (valores[i] < min_valor) min_valor = valores[i];
    }
    return max_valor - min_valor;               // Amplitud (pico a pico)
}

//* Función para detectar picos y calcular BPM
int detectar_picos(int *valores, int tamano, int umbral) {
    int picos = 0;
    for (int i = 1; i < tamano - 1; i++) {
        if (valores[i] > umbral && valores[i] > valores[i-1] && valores[i] > valores[i+1]) {
            picos++;
        }
    }
    return picos;
}

//* Función para leer el ADC
int leer_ADC() {
    ADCSRA |= (1 << ADSC);                      // Inicia la conversión
    while (ADCSRA & (1 << ADSC));               // Espera a que termine
    int ADC_Low = ADCL;
    return (ADCH << 8) | ADC_Low;               // Combina ADCH y ADCL
}

//* Función para inicializar UART
void uart_init() {
    btSerial.begin(9600);                       // Inicializa el puerto serial con el HC-05 a 9600 baudios
}

//* Función para enviar un caracter por UART
void uart_send_char(char c) {
    btSerial.write(c);                          // Envía un carácter a través de Bluetooth
}

//* Función para enviar una cadena por UART
void uart_send_string(const char *str) {
    while (*str) {
        uart_send_char(*str);
        str++;
    }
}

//* FUNCION PRINCIPAL
int main() {
    //* Configuración de pines de salida
    DDRA |= (1 << DDA0);                        // PA0 como salida (LED infrarrojo)
    DDRA |= (1 << DDA1);                        // PA1 como salida (LED rojo)

    //* Configuración del ADC
    ADMUX = 0b00000010;                         // ADC2 como entrada (con referencia Vcc)
    ADCSRA = 0b10000011;                        // ADC habilitado, prescaler 8 (125kHz)

    // Inicializar UART para comunicación serial con HC-05
    uart_init();

    int muestras[100];                          // Arreglo para almacenar las muestras
    float AC_infra, DC_infra, AC_rojo, DC_rojo; // Variables para componentes AC y DC
    float bpm, SpO2;                            // Variables para BPM y SpO2 (oxigenación)

    while (1) {
        // Medición con LED infrarrojo (BPM y oxigenación)
        PORTA |= (1 << PORTA0);                 // Enciende LED infrarrojo
        PORTA &= ~(1 << PORTA1);                // Apaga LED rojo
        _delay_ms(30);                          // Espera para estabilizar

        // Tomar 100 muestras con el LED infrarrojo
        for (int i = 0; i < 100; i++) {
            muestras[i] = leer_ADC();           // Leer ADC para infrarrojo
            _delay_ms(30);                      // 30 ms para cubrir ~3 segundos
        }
        DC_infra = calcular_DC(muestras, 100);  // Calcula la componente DC
        AC_infra = calcular_AC(muestras, 100, DC_infra);  // Calcula la componente AC

        // Medición con LED rojo (oxigenación)
        PORTA |= (1 << PORTA1);                 // Enciende LED rojo
        PORTA &= ~(1 << PORTA0);                // Apaga LED infrarrojo
        _delay_ms(30);                          // Espera para estabilizar

        // Tomar 100 muestras con el LED rojo
        for (int i = 0; i < 100; i++) {
            muestras[i] = leer_ADC();           // Leer ADC para rojo
            _delay_ms(30);                      // 30 ms para cubrir ~3 segundos
        }
        DC_rojo = calcular_DC(muestras, 100);   // Calcula la componente DC
        AC_rojo = calcular_AC(muestras, 100, DC_rojo);  // Calcula la componente AC

        //* Cálculo de la relación R
        float R = (AC_rojo / DC_rojo) / (AC_infra / DC_infra);

        //* Proceso adicional para convertir R en SpO2 (curva de calibración)
        SpO2 = 110 - (25 * R);                  // Ejemplo de cálculo (ajustar según calibración)

        //* Cálculo de BPM
        int umbral = (DC_infra + AC_infra) / 2;  // Umbral para detectar picos
        int picos = detectar_picos(muestras, 100, umbral);

        // Si 100 muestras son ~3 segundos (por _delay_ms(30) * 100)
        bpm = (picos * 60) / 3.0;               // Convertir picos en BPM

        // Enviar BPM y SpO2 a través de UART (Bluetooth HC-05)
        char buffer[50]; 
        snprintf(buffer, sizeof(buffer), "BPM: %.2f\r\nSpO2: %.2f%%\r\n", bpm, SpO2);
        uart_send_string(buffer);               // Envía los datos a través de UART

        _delay_ms(1000);                        // Pausa de 1 segundo antes de volver a medir
    }
}