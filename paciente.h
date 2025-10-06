#ifndef PACIENTE_H
#define PACIENTE_H

#include "historico.h"

typedef struct paciente Paciente;

int get_id_paciente(Paciente *p);
char *get_nome_paciente(Paciente *p);
HISTORICO* paciente_get_historico(Paciente *p);
Paciente* criar_paciente(int id, const char *nome);

#endif