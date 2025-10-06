#include "paciente.h"
#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct paciente {
    int id; 
    char nome[100];
    HISTORICO *historico;
};

int get_id_paciente(Paciente *p){
    return p->id;
}
char *get_nome_paciente(Paciente *p){
    return p->nome;
}


HISTORICO* paciente_get_historico(Paciente *p){
    if (p == NULL) {
        return NULL;
    }
    return p->historico;
}

Paciente* criar_paciente(int id, const char *nome) {
    Paciente *p = (Paciente*) malloc(sizeof(struct paciente));
    
    if (p == NULL) {
        return NULL;
    }
    
    p->id = id;
    
    if (nome != NULL) {
        strncpy(p->nome, nome, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0'; // Garante terminação nula
    } else {
        p->nome[0] = '\0';
    }
    
    p->historico = historico_criar(p->id, p->nome);
    
    if (p->historico == NULL){
        free(p);
        return NULL;
    }
    
    return p;
}