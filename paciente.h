#ifndef PACIENTE_H
#define PACIENTE_H

#include "historico.h"

typedef struct paciente Paciente;

int get_id_paciente(Paciente *p);
void set_id_paciente (Paciente *p, int index);
char *get_nome_paciente(Paciente *p);
HISTORICO* paciente_get_historico(Paciente *p);
void paciente_set_historico(Paciente *p, HISTORICO *h);
Paciente* criar_paciente(int id, const char *nome);
void liberar_paciente(Paciente *p);

#endif