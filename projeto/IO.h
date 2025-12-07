#ifndef IO_H
#define IO_H
#include "lista_pacientes.h"
#include "fila_triagem.h"
#include <stdbool.h>

bool SAVE(ListaPacientes *lista, FilaTriagem *fila, void *unused);
bool LOAD(ListaPacientes **lista, FilaTriagem **fila, void *unused);

#endif