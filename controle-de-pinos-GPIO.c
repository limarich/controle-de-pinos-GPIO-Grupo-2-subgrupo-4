#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "pico/bootrom.h"
#include "hardware/pwm.h"

// FUNÇÃO PARA LER COMANDOS VIA SERIAL
int read_serial_command(char *command, size_t size);
// FUNÇÃO PARA PROCESSAR OS COMANDOS LIDOS
void process_command(const char *command);
// FUNÇÃO PARA INCIALIZAR OS PINOS GPIOS
void setup_gpio();
// FUNÇÃO PARA COMBINAR TODAS AS CORES NO LED RGB E GERAR A BRANCA
void ligar_led_branco();
// FUNÇÃO PARA LIGAR LED VERMELHO
void ligar_led_vermelho();
// FUNÇÃO PARA LIGAR LED AZUL
void ligar_led_azul();
// FUNÇÃO PARA LIGAR LED VERDE
void ligar_led_verde();
// FUNÇÃO PARA EMITIR SOM NO BUZZER
void emitir_som();
// FUNÇÃO PARA DESLIGAR TODAS AS CORES DO LED RGB
void desligar_led_completamente();

// Define os pinos GPIO para o LED RGB
#define LED_G_PIN 11  // VERDE
#define LED_B_PIN 12  // AZUL
#define LED_R_PIN 13  // VERMELHO
#define BUZZER_PIN 10 // Pino do buzzer

int main()
{
    stdio_init_all();
    setup_gpio(); // Inicialização da GPIOs
    char command[20];
    printf("Escreva algum comando: \n");
    while (true)
    {
        if (read_serial_command(command, sizeof(command)))
        {
            printf("comando lido: %s\n", command);
            process_command(command);
        }
    }
}

// FUNÇÃO PARA LER COMANDOS VIA SERIAL-> retorna 1 se tiver alguma leitura e 0 caso contrário
int read_serial_command(char *command, size_t size)
{
    static int index = 0;

    int ch = getchar_timeout_us(10000); // período máximo de 10 milissegundos
    if (ch != PICO_ERROR_TIMEOUT)
    {
        if (ch == '\n' || ch == '\r')
        {
            if (index > 0)
            {
                command[index] = '\0';
                index = 0; // após ler o comando volta reseta o índice
                return 1;  // indica que houve leitura
            }
        }
        else if (index < size - 1)
        {
            command[index++] = (char)ch;
        }
    }
    return 0; // indica que não houve leitura
}

void process_command(const char *command)
{
    if (strcmp(command, "OFF") == 0)
    {
        // APAGA o LED
        gpio_put(LED_R_PIN, 0);
        gpio_put(LED_G_PIN, 0);
        gpio_put(LED_B_PIN, 0);
    }
    else if (strcmp(command, "BRANCA") == 0)
    {
        // Acende o LED RGB na cor branca
        ligar_led_branco();
    }
    else if (strcmp(command, "VERMELHO") == 0)
    {
        // Acende o LED RGB na cor vermelha
        ligar_led_vermelho();
    }
    else if (strcmp(command, "SOM") == 0)
    {
        // Emite som no buzzer por 2 segundos
        emitir_som();
    }
    else if (strcmp(command, "AZUL") == 0)
    {
        // Acende o LED RGB na cor azul
        ligar_led_azul();
    }
    else if (strcmp(command, "VERDE") == 0)
    {
        // Acende o LED RGB na cor azul
        ligar_led_verde();
    }
    else if (strcmp(command, "LEDSOFF") == 0)
    {
        // Acende o LED RGB na cor azul
        desligar_led_completamente();
    }
    else if (strcmp(command, "BOOT") == 0)
    {
        // SÓ FUNCIONA NO HARDWARE - NA SIMULAÇÃO N FAZ NADA :-P
        printf("Reiniciando no modo bootloader...\n");
        sleep_ms(500);
        reset_usb_boot(0, 0);
    }
    else
    {
        printf("Comando não reconhecido: %s\n", command);
    }
}

// Função para inicialização dos pinos GPIO
void setup_gpio()
{
    // Configuração do LED RGB como saída
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);
    // Configuração do pino do buzzer como PWM
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_wrap(slice_num, 1250); // Define um valor inicial para o top do PWM
    pwm_set_enabled(slice_num, true);
}

// Função para ligar o LED RGB na cor branca
void ligar_led_branco()
{
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 1);
}

// Função para ligar o LED RGB na cor vermelha
void ligar_led_vermelho()
{
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
}

// Função para ligar o LED RGB na cor azul
void ligar_led_azul()
{
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 1);
}


// Função para ligar o LED RGB na cor verde
void ligar_led_verde()
{
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
}

// Função para desligar o LED RGB completamente
void desligar_led_completamente() {
  gpio_put(LED_R_PIN, 0); // Desliga LED RED
  gpio_put(LED_G_PIN, 0); // Desliga LED GREEN
  gpio_put(LED_B_PIN, 0); // Desliga LED BLUE
}

// Função para emitir som no buzzer (2 segundos)
void emitir_som()
{
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    // Configura a frequência do buzzer (440 Hz = Lá)
    uint freq_hz = 440;     // Frequência ajustável
    uint clock = 125000000; // Frequência do clock do PWM
    uint top = clock / freq_hz;

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(BUZZER_PIN, top / 2); // 50% duty cycle para som audível

    sleep_ms(2000); // Emite som por 2 segundos

    pwm_set_gpio_level(BUZZER_PIN, 0); // Desliga o buzzer
}
