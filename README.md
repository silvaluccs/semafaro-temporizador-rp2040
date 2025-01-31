# Simulador de Semáforo com Raspberry Pi Pico

Este projeto simula o funcionamento de um semáforo utilizando um Raspberry Pi Pico e três LEDs representando as cores vermelho, amarelo e verde. A troca das cores ocorre automaticamente em intervalos regulares, utilizando um temporizador da biblioteca `hardware/timer.h`.

## Componentes Necessários
- Raspberry Pi Pico
- 3 LEDs (Vermelho, Amarelo e Verde)
- 3 resistores (330Ω)
- Jumpers
- Protoboard

## Funcionamento
O programa utiliza um `enum` chamado `CORES_SEMAFARO` para representar as cores do semáforo. O temporizador (timer) alterna a cor do semáforo a cada 3 segundos, controlando os LEDs correspondentes.

### Lógica de Mudança de Cores
1. **Vermelho** (ligado inicialmente)
2. **Amarelo** (após 3 segundos)
3. **Verde** (após mais 3 segundos)
4. **Vermelho** novamente, repetindo o ciclo.

Cada LED é acionado individualmente dentro da função `repeating_timer_callback`, garantindo que apenas um LED esteja ligado por vez.

## Explicação do Código

### Definição dos Pinos
```c
const uint pino_led_vermelho = 11;
const uint pino_led_amarelo = 12;
const uint pino_led_verde = 13;
```
Essas constantes definem os pinos GPIO onde os LEDs estão conectados no Raspberry Pi Pico.

### Enumeração para Representação das Cores
```c
typedef enum CORES_SEMAFARO {VERMELHO, AMARELO, VERDE} CORES_SEMAFARO;
```
Aqui, criamos um `enum` para representar os três estados do semáforo.

### Configuração dos LEDs
```c
void setup_led(uint pino) {
    gpio_init(pino);
    gpio_set_dir(pino, GPIO_OUT);
    gpio_put(pino, false);
}
```
Cada LED é configurado como saída digital e inicia desligado.

### Configuração do Temporizador
```c
struct repeating_timer timer;
add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
```
Essa função configura um temporizador que chama `repeating_timer_callback` a cada 3.000 milissegundos (3 segundos).

### Callback do Temporizador
```c
bool repeating_timer_callback(struct repeating_timer *t) {
    switch (cor_semaforo) {
        case VERMELHO:
            gpio_put_all(false);
            gpio_put(pino_led_vermelho, true);
            cor_semaforo = AMARELO;
            break;
        case AMARELO:
            gpio_put_all(false);
            gpio_put(pino_led_amarelo, true);
            cor_semaforo = VERDE;
            break;
        case VERDE:
            gpio_put_all(false);
            gpio_put(pino_led_verde, true);
            cor_semaforo = VERMELHO;
            break;
    }
    return true;
}
```
Nesta função:
- O estado do semáforo é atualizado.
- Apenas o LED correspondente ao novo estado é ligado.
- Retornamos `true` para manter o temporizador ativo.

### Loop Principal
```c
while (true) {
    printf("Cor do semáforo: %d\n", cor_semaforo);
    sleep_ms(1000);
}
```
Aqui, imprimimos continuamente o estado atual do semáforo no console, a cada segundo.

## Compilando e Executando
1. Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no seu ambiente.
2. Compile o código usando `CMake` e `Make`:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
3. Envie o arquivo `.uf2` para o Raspberry Pi Pico.
4. O semáforo iniciará automaticamente, alternando as cores a cada 3 segundos.

## Explicação Detalhada do Temporizador
O temporizador funciona utilizando a função `add_repeating_timer_ms`, que configura uma interrupção para ser acionada a cada período especificado (3 segundos). Quando a interrupção ocorre, a função `repeating_timer_callback` é chamada.

Dentro do `repeating_timer_callback`, a cor do semáforo é alterada seguindo a lógica especificada no `switch case`, garantindo que o ciclo vermelho → amarelo → verde → vermelho seja repetido indefinidamente. 

O retorno `true` no final da `repeating_timer_callback` informa que o temporizador deve continuar rodando, caso contrário, ele seria desativado.

## Autor
Desenvolvido por Lucas. Projeto para aprendizado e simulação de sistemas embarcados com Raspberry Pi Pico.

