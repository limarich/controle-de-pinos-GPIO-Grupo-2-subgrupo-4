# **Controle de Pinos GPIO - Grupo 2, Subgrupo 4**

## **Descrição Geral**
Este projeto implementa uma interface serial para interagir com uma placa baseada no microcontrolador RP2040. Por meio de comandos recebidos via serial, é possível controlar funcionalidades específicas, como entrada no modo bootloader ou manipulação de pinos GPIO.

---

## **Recursos Implementados**

### **1. Comandos Disponíveis**
- **`BOOT`**: Reinicia a placa no modo bootloader para atualizações ou reconfiguração.
- Comandos desconhecidos exibem uma mensagem informativa no console.

### **2. Modularização**
O código é composto pelas seguintes funções principais:

#### a) `read_serial_command`
Responsável por capturar entradas de comando via serial.
- Retorna `1` se um comando válido for recebido.
- Retorna `0` se não houver entrada ou timeout.

#### b) `process_command`
Responsável por interpretar e executar ações baseadas no comando recebido. Atualmente, suporta os comandos:
- `BOOT` para reinício em modo bootloader.

---

## **Como Usar**

### **1. Ambiente Necessário**
- Placa compatível com o SDK Pico (ex: Raspberry Pi Pico).
- IDE e ferramenta de compilação configurada com o Pico SDK.
- Emulador ou hardware real conectado via serial.

### **2. Compile e envie o código para a Raspberry pico w**
3. Abra o aplicativo Putty.
4. Abra o terminal serial com o baud rate configurado de 115200.
5. Envie os comandos suportados e observe as respostas no terminal.

---

## **Exemplos de Uso**

### **Execução no Terminal**
**Saída esperada para o comando `BOOT`**:
```plaintext
Escreva algum comando:
comando lido: BOOT
Reiniciando no modo bootloader...
```

**Saída esperada para comandos desconhecidos**:
```plaintext
Escreva algum comando:
comando lido: INVALIDO
Comando não reconhecido: INVALIDO
```

---

## **Detalhes do Código**

### **Arquivo Principal (`main.c`)**
#### Função `read_serial_command`
- Entrada: Buffer para o comando e tamanho máximo.
- Lógica de leitura via `getchar_timeout_us` com verificação de finalização de linha (`\n` ou `\r`).
- Reseta o índice após completar o comando.

#### Função `process_command`
- Entrada: Comando recebido.
- Executa ações específicas para cada comando reconhecido.

#### Estrutura de Loop Principal
1. Inicializa a comunicação serial.
2. Aguarda comandos via `read_serial_command`.
3. Exibe o comando no console.
4. Processa comandos via `process_command`.

## **Créditos**
Desenvolvido pelo Grupo 2, Subgrupo 4, como parte do estudo e prática de microcontroladores com a arquitetura RP2040.

