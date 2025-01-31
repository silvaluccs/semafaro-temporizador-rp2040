#include <stdio.h>
#include "pico/stdlib.h"

const uint pino_led_vermelho = 11;
const uint pino_led_azul = 12;
const uint pino_led_verde = 13;

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
