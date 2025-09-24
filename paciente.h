#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct paciente Paciente;

struct paciente {
    int id; 
    char nome[100];
    // seria bom colocar a pilha de historico aqui
    // PilhaHistorico *historico;
};

#endif