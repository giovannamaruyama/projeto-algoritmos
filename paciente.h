#ifndef PACIENTE_H
#define PACIENTE_H

#inlcude "historico.h"

typedef struct paciente Paciente;

int get_id_paciente(Paciente *p);
char *get_nome_paciente(Paciente *p);
HISTORICO* paciente_get_historico(Paciente *p);

#endif