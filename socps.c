#include "contiki.h"
#include <stdio.h>
#include <random.h>
#include "sys/etimer.h"

// Definição dos processos
PROCESS(batimentos, "Batimentos");
PROCESS(saturacao, "Saturacao");
PROCESS(temperatura, "Temperatura");
PROCESS(alerta, "Alerta");

// Autostart dos processos
AUTOSTART_PROCESSES(&batimentos, &saturacao, &temperatura, &alerta); // Define quais processos iniciar automaticamente.

// Processo para medir batimentos cardíacos
PROCESS_THREAD(batimentos, ev, data)
{
    static struct etimer timer; // Cria uma instância de um temporizador.
    PROCESS_BEGIN(); // Inicia a execução do processo.
    etimer_set(&timer, CLOCK_SECOND * 3); // Inicializa um temporizador para gerar eventos a cada 3 segundos.
    static char msg[50]; // Cria um buffer para armazenar mensagens.

    while (true) {
        int numeroBatimento = 20 + rand() % 121; // Gera um número aleatório representando batimentos cardíacos entre 20 e 140.
        
        // Verificação e alerta se os batimentos estiverem abaixo de 50
        if (numeroBatimento < 50) {
            sprintf(msg, "Batimentos Baixos: %d", numeroBatimento); // Formata a mensagem.
            process_post(&alerta, PROCESS_EVENT_MSG, &msg); // Publica um evento de mensagem no processo de alerta.
        }
        // Verificação e alerta se os batimentos estiverem acima de 90
        else if (numeroBatimento > 90) {
            sprintf(msg, "Batimentos Altos: %d", numeroBatimento); // Formata a mensagem.
            process_post(&alerta, PROCESS_EVENT_MSG, &msg); // Publica um evento de mensagem no processo de alerta.
        }

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer)); // Espera até que o temporizador expire.
        etimer_reset(&timer); // Reinicia o temporizador para o próximo ciclo.
    }

    PROCESS_END(); // Finaliza a execução do processo.
}

// Processo para medir a saturação de oxigênio
PROCESS_THREAD(saturacao, ev, data)
{
    static struct etimer timer; // Cria uma instância de um temporizador.
    PROCESS_BEGIN(); // Inicia a execução do processo.
    etimer_set(&timer, CLOCK_SECOND * 3); // Inicializa um temporizador para gerar eventos a cada 3 segundos.
    static char msg[50]; // Cria um buffer para armazenar mensagens.

    while (true) {
        int numeroSaturacao = 80 + rand() % 21; // Gera um número aleatório representando saturação de oxigênio entre 80 e 100.
        
        // Verificação e alerta se a saturação estiver abaixo de 90
        if (numeroSaturacao < 90) {
            sprintf(msg, "Saturacao Baixa: %d", numeroSaturacao); // Formata a mensagem.
            process_post(&alerta, PROCESS_EVENT_MSG, &msg); // Publica um evento de mensagem no processo de alerta.
        }

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer)); // Espera até que o temporizador expire.
        etimer_reset(&timer); // Reinicia o temporizador para o próximo ciclo.
    }

    PROCESS_END(); // Finaliza a execução do processo.
}

// Processo para medir a temperatura
PROCESS_THREAD(temperatura, ev, data)
{
    static struct etimer timer; // Cria uma instância de um temporizador.
    PROCESS_BEGIN(); // Inicia a execução do processo.
    etimer_set(&timer, CLOCK_SECOND * 3); // Inicializa um temporizador para gerar eventos a cada 3 segundos.
    static char msg[50]; // Cria um buffer para armazenar mensagens.

    while (true) {
        float numeroTemp = 34.0 + ((float)rand() / RAND_MAX) * 7; // Gera um número aleatório representando temperatura entre 34 e 41 graus Celsius.
        
        // Verificação e alerta se a temperatura estiver abaixo de 35
        if (numeroTemp < 35) {
            sprintf(msg, "Hipotermia: %.2f", numeroTemp); // Formata a mensagem.
            process_post(&alerta, PROCESS_EVENT_MSG, &msg); // Publica um evento de mensagem no processo de alerta.
        }
        // Verificação e alerta se a temperatura estiver acima de 37
        else if (numeroTemp > 37) {
            sprintf(msg, "Febre: %.2f", numeroTemp); // Formata a mensagem.
            process_post(&alerta, PROCESS_EVENT_MSG, &msg); // Publica um evento de mensagem no processo de alerta.
        }

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer)); // Espera até que o temporizador expire.
        etimer_reset(&timer); // Reinicia o temporizador para o próximo ciclo.
    }

    PROCESS_END(); // Finaliza a execução do processo.
}

// Processo para lidar com alertas e imprimir mensagens
PROCESS_THREAD(alerta, ev, data)
{
    PROCESS_BEGIN(); // Inicia a execução do processo.

    while (true) {
        PROCESS_WAIT_EVENT(); // Aguarda por qualquer evento.
        
        // Verificação se o evento é uma mensagem e, em caso afirmativo, imprime o alerta
        if (PROCESS_EVENT_MSG == ev) {
            printf("Alerta - %s\n", (char *)data); // Imprime a mensagem de alerta.
        }
    }

    PROCESS_END(); // Finaliza a execução do processo.
}
