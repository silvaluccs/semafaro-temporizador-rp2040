#include <stdio.h>
#include "pico/stdlib.h"

const uint pino_led_vermelho = 11; // Define o pino do led vermelho
const uint pino_led_azul = 12; // Define o pino do led azul
const uint pino_led_verde = 13; // Define o pino do led verde

typedef enum CORES_SEMAFARO {VERMELHO, AMARELO, VERDE} CORES_SEMAFARO;

void setup_led(uint pino); // Protótipo da função para inicializar um pino de led

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial

    setup_led(pino_led_vermelho); // Inicializa o led vermelho
    setup_led(pino_led_azul); // Inicializa o led azul
    setup_led(pino_led_verde); // Inicializa o led verde

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

/*
* Função para inicializar um pino de led
*/
void setup_led(uint pino)
{
    gpio_init(pino); // Inicializa o pino
    gpio_set_dir(pino, GPIO_OUT); // Define o pino como saída
    gpio_put(pino, false);  // Desliga o led
}