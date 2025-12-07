#ifndef FILA_TRIAGEM_H
#define FILA_TRIAGEM_H

#include "paciente.h"
#include <stdbool.h>

typedef struct fila FilaTriagem;

FilaTriagem* cria_fila();
void apagar_fila(FilaTriagem **fila);
int inserir_paciente_fila(FilaTriagem *fila, Paciente *p);
Paciente* remover_paciente_fila(FilaTriagem *fila);
int get_tamanho_fila(FilaTriagem *fila);
bool fila_contem_paciente(FilaTriagem *fila, int id);
void mostrar_fila(FilaTriagem *fila);
Paciente* acessar_posicao_heap(FilaTriagem *fila, int index);

#endif