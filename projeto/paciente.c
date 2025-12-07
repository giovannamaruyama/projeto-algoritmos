#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que representa um paciente no sistema
struct paciente {
    int id;                          // Identificador único escolhido pelo usuário
    char nome[100];                  // Nome do paciente
    int prioridade;                  // Prioridade 
    unsigned long ordem_chegada;     // Ordem de chegada usada para desempate na fila
    HISTORICO *historico;            // Ponteiro para o histórico de procedimentos
};

// Cria um novo paciente preenchendo seus dados básicos
Paciente* criar_paciente(int id, const char *nome, int prioridade, unsigned long ordem_chegada) {
    Paciente *p = (Paciente*) malloc(sizeof(struct paciente));
    if (!p) return NULL;
    
    p->id = id;
    p->prioridade = prioridade;
    p->ordem_chegada = ordem_chegada;

    // Copia segura do nome
    strncpy(p->nome, nome ? nome : "", 99);
    p->nome[99] = '\0';

    // Todo paciente é criado já com um histórico associado
    p->historico = historico_criar(id, p->nome);
    return p;
}

// Libera memória do paciente e também seu histórico
void liberar_paciente(Paciente *p){
    if(p){
        if(p->historico) historico_apagar(&p->historico);
        free(p);
    }
}

// Retorna o ID do paciente
int get_id_paciente(Paciente *p){ 
    return p->id; 
}

// Retorna o nome do paciente
char *get_nome_paciente(Paciente *p){
    return p->nome; 
    }

// Retorna a prioridade do paciente
int get_prioridade_paciente(Paciente *p) {
    return p->prioridade; 
}

// Retorna a ordem de chegada do paciente
unsigned long get_ordem_chegada(Paciente *p) {
     return p->ordem_chegada; 
    }

// Retorna o histórico associado ao paciente
HISTORICO* paciente_get_historico(Paciente *p){
     return p ? p->historico : NULL; 
    }

// Troca o histórico do paciente 
void paciente_set_historico(Paciente *p, HISTORICO *h) {
     if(p) p->historico = h; 
    }
