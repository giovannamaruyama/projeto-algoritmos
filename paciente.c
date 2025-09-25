#include "fila_triagem.h"
#include "paciente.h"
#include <stdio.h>


struct paciente {
    int id; 
    char nome[100];
    // seria bom colocar a pilha de historico aqui
    // PilhaHistorico *historico;
};

int get_id_paciente(Paciente *p){
    return p->id;
}
char *get_nome_paciente(Paciente *p){
    return p->nome;
}

