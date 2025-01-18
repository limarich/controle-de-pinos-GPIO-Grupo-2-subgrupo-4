#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

// FUNÇÃO PARA LER COMANDOS VIA SERIAL
int read_serial_command(char *command, size_t size);
// FUNÇÃO PARA PROCESSAR OS COMANDOS LIDOS
void process_command(const char *command);

int main()
{
    stdio_init_all();
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
    else
    {
        printf("Comando não reconhecido: %s\n", command);
    }
}