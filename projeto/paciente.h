#ifndef PACIENTE_H
#define PACIENTE_H

#include "historico.h"

typedef struct paciente Paciente;

// Cria com prioridade e ordem
Paciente* criar_paciente(int id, const char *nome, int prioridade, unsigned long ordem_chegada);
void liberar_paciente(Paciente *p);
int get_id_paciente(Paciente *p);
char *get_nome_paciente(Paciente *p);
int get_prioridade_paciente(Paciente *p);
unsigned long get_ordem_chegada(Paciente *p);
HISTORICO* paciente_get_historico(Paciente *p);
void paciente_set_historico(Paciente *p, HISTORICO *h);

#endif