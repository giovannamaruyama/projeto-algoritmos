#include "procedimentos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PROC 100
#define MAX_DATA 11   // "dd/mm/aaaa" + '\0'

struct procedimento_{
    char nome[MAX_PROC];
    char data[MAX_DATA];
};

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

bool procedimento_apagar(PROCEDIMENTO **p){
    if(p != NULL && *p != NULL){
        free(*p);
        *p = NULL;
        return true;
    }
    return false;
}

const char* procedimento_get_nome(PROCEDIMENTO *p){
    return (p != NULL) ? p->nome : NULL;
}

const char* procedimento_get_data(PROCEDIMENTO *p){
    return (p != NULL) ? p->data : NULL;
}

bool procedimento_set_nome(PROCEDIMENTO *p, const char *nome){
    if(p != NULL && nome != NULL){
        strncpy(p->nome, nome, MAX_PROC-1);
        p->nome[MAX_PROC-1] = '\0';
        return true;
    }
    return false;
}

bool procedimento_set_data(PROCEDIMENTO *p, const char *data){
    if(p != NULL && data != NULL){
        strncpy(p->data, data, MAX_DATA-1);
        p->data[MAX_DATA-1] = '\0';
        return true;
    }
    return false;
}

void procedimento_imprimir(PROCEDIMENTO *p){
    if(p != NULL){
        printf("Procedimento: %s | Data: %s",
               p->nome, p->data);
    }
}


bool procedimento_save(FILE *fp, PROCEDIMENTO *p) {
    if (fp == NULL || p == NULL) {
        return false;
    }
    if (fwrite(p, sizeof(struct procedimento_), 1, fp) != 1) {
        return false;
    }
    return true;
}

PROCEDIMENTO* procedimento_load(FILE *fp) {
    if (fp == NULL) {
        return NULL;
    }
    
    // Aloca memória para a nova estrutura
    PROCEDIMENTO *p = (PROCEDIMENTO*) malloc(sizeof(struct procedimento_));
    if (p == NULL) {
        return NULL;
    }

    // Lê o conteúdo do disco
    if (fread(p, sizeof(struct procedimento_), 1, fp) != 1) {
        // Se a leitura falhar (ex: fim do arquivo), libera a memória e retorna NULL
        free(p);
        return NULL;
    }
    return p;
}
