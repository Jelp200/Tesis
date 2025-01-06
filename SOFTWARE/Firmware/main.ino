/*
** #########################################################################################
**  Archivo         :   main.ino
**  Proyecto        :   Tesis
**  Herramienta(s)  :   Microchip Studio
**  Compilador      :   C/C++ Compiler
**  Autores         :
**                      Jorge E. Pena P.
**  Descripcion     :
**                      Marcaje de pulso y envio de datos via bluetooth.
** #########################################################################################
*/

//* LIBRERIA PARA EMULAR TRX VIA UART
#include <SoftwareSerial.h>

//! Configuracion para los pines de TX y RX
#define RX_PIN 9                                // PB0 (Pin físico 3)
#define TX_PIN 10                               // PB1 (Pin físico 2)

//* DEFINICION DE LA VELOCIDAD DEL RELOJ
#define F_CPU   1000000UL                       // 1MHz

//! Llamada a la funcion para comenzar la transmision
SoftwareSerial btSerial(RX_PIN, TX_PIN);        // RX, TX

//* DIRECTIVAS DE PREPROCESADOR
#include <avr/io.h>
#include <util/delay.h>

//* Función para inicializar UART
void uart_init() {
    btSerial.begin(9600);                       // Inicializa el puerto serial con el HC-05 a 9600 baudios
}

//* Función para enviar un carácter por UART
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
    //*! CONFIGURACION DE LOS PINES
    //* Pines de salida
    DDRA |= (1 << DDA1);                                        // PA1 como salida (LED infrarrojo)
    //* Pines de entrada
    DDRA &= ~(1 << DDA2);                                       // PA2 como entrada
    PORTA |= (1 << PA2);                                        // Activa la resistencia de pull-up

    volatile uint8_t edoAnterior = 0;                           // Estado anterior del pin
    volatile uint8_t pulseCount = 0;                            // Contador de pulsos
    unsigned long lastTime = 0;                                 // Tiempo del último pulso
    unsigned long startTime = 0;                                // Tiempo inicial para conteo de 1 segundos

    // Inicializar UART para comunicación serial con HC-05
    uart_init();

    startTime = 0; // Inicia el temporizador de 3 segundos

    while (1) {
        // Leer el estado del pin de entrada
        volatile uint8_t edoActual = PINA & (1 << PINA2);       // Lee el estado del pin PA2

        // Encendido y apagado del LED infrarrojo
        PORTA ^= (1 << PORTA1);                                 // Toggle del LED infrarrojo
        _delay_ms(20);                                          // Pausa de 20 ms

        // Detectar cambio de estado (LOW -> HIGH o HIGH -> LOW)
        if (edoActual != edoAnterior) {
          if (edoActual) pulseCount++;                          // Solo cuenta flancos ascendentes
          edoAnterior = edoActual;                              // Actualiza el estado anterior
        }
        // Simulación de tiempo de 3 segundos utilizando un contador de bucles
        startTime++;
        if (startTime >= 60) {                                  // Aproximadamente 3 segundos con delay de 50 ms
          int bpm = pulseCount * 20;                            // Calcula BPM (pulsos en 3 seg * 20)
          
          char buffer[10];                                      // Buffer para convertir número a texto
          itoa(bpm, buffer, 10);                                // Convierte el valor BPM a cadena de texto
          
          uart_send_string("BPM: ");
          uart_send_string(buffer);                             // Envía la cadena completa
          uart_send_string("\n");
          
          pulseCount = 0;                                       // Reinicia el contador de pulsos
          startTime = 0;                                        // Reinicia el temporizador
        }
    }
}
