#include "fila_triagem.h"
#include "historico.h"
#include "paciente.h"
#include <stdio.h>


struct paciente {
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