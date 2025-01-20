#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "pico/bootrom.h"

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
//FUNÇÃO PARA LIGAR LED VERDE
void ligar_led_verde();

// Define os pinos GPIO para o LED RGB
#define LED_G_PIN 11 // VERDE
#define LED_B_PIN 12 // AZUL
#define LED_R_PIN 13 // VERMELHO

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
    if (strcmp(command, "ON") == 0)
    {
        //    E CONTINUA DAQUI
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
