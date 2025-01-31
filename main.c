#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

const uint pino_led_vermelho = 11; // Define o pino do led vermelho
const uint pino_led_amarelo = 12; // Define o pino do led amarelo 
const uint pino_led_verde = 13; // Define o pino do led verde


typedef enum CORES_SEMAFARO {VERMELHO, AMARELO, VERDE} CORES_SEMAFARO; // Enumeração para as cores do semáforo

static volatile CORES_SEMAFARO cor_semaforo = VERMELHO; // Variável para armazenar a cor atual do semáforo

void setup_led(uint pino); // Protótipo da função para inicializar um pino de led
bool repeating_timer_callback(struct repeating_timer *t);

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial

    setup_led(pino_led_vermelho); // Inicializa o led vermelho
    setup_led(pino_led_amarelo); // Inicializa o led amarelo
    setup_led(pino_led_verde); // Inicializa o led verde


    struct repeating_timer timer; // Cria uma estrutura para o timer

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); // Inicializa o timer

    while (true) {
        printf("Cor do semáforo: %d\n", cor_semaforo); // Imprime a cor do semáforo
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


/*
* Função de callback para o timer
*/
bool repeating_timer_callback(struct repeating_timer *t) {

    switch (cor_semaforo)
    {
        case VERMELHO:
            gpio_put_all(false); // Desliga todos os leds
            gpio_put(pino_led_vermelho, true); // Liga o led vermelho
            cor_semaforo = AMARELO;
            break;
        case AMARELO:
            gpio_put_all(false); // Desliga todos os leds
            gpio_put(pino_led_amarelo, true); // Liga o led azul
            cor_semaforo = VERDE;
            break;
        case VERDE:
            gpio_put_all(false); // Desliga todos os leds
            gpio_put(pino_led_verde, true); // Liga o led verde
            cor_semaforo = VERMELHO;
            break;
    }

    return true;
}