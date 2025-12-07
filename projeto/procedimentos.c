#include "procedimentos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PROC 100    // Tamanho máximo permitido para o nome do procedimento
#define MAX_DATA 20     // Tamanho máximo para o texto da data

// Estrutura que representa um procedimento feito no paciente
struct procedimento_{
    char nome[MAX_PROC];    // Nome ou descrição do procedimento
    char data[MAX_DATA];    // Data e horário em formato string
};

// Cria um novo procedimento copiando nome e data
PROCEDIMENTO* procedimento_criar(const char *nome, const char *data){
    PROCEDIMENTO *p = (PROCEDIMENTO*) malloc(sizeof(PROCEDIMENTO));
    if(p != NULL){
        strncpy(p->nome, nome, MAX_PROC-1);
        p->nome[MAX_PROC-1] = '\0';

        strncpy(p->data, data, MAX_DATA-1);
        p->data[MAX_DATA-1] = '\0';
    }
    return p;
}

// Libera memória de um procedimento e zera o ponteiro
bool procedimento_apagar(PROCEDIMENTO **p){
    if(p != NULL && *p != NULL){
        free(*p);
        *p = NULL;
        return true;
    }
    return false;
}

// Retorna o nome do procedimento
const char* procedimento_get_nome(PROCEDIMENTO *p){ return (p ? p->nome : NULL); }

// Retorna a data do procedimento
const char* procedimento_get_data(PROCEDIMENTO *p){ return (p ? p->data : NULL); }

// Salva um procedimento no arquivo binário
bool procedimento_save(FILE *fp, PROCEDIMENTO *p) {
    if (!fp || !p) return false;
    if (fwrite(p, sizeof(struct procedimento_), 1, fp) != 1) return false;
    return true;
}

// Carrega um procedimento a partir do arquivo binário
PROCEDIMENTO* procedimento_load(FILE *fp) {
    if (!fp) return NULL;

    PROCEDIMENTO *p = (PROCEDIMENTO*) malloc(sizeof(struct procedimento_));
    if (!p) return NULL;

    if (fread(p, sizeof(struct procedimento_), 1, fp) != 1) {
        free(p);
        return NULL;
    }
    return p;
}
