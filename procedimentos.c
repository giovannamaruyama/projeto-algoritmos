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
