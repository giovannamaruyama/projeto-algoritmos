
#ifndef FILA_TRIAGEM_H
#define FILA_TRIAGEM_H

#include "paciente.h"

#define TAMANHO_FILA 50 

typedef struct fila FilaTriagem;

FilaTriagem* cria_fila();

int fila_vazia(FilaTriagem *fila);

int fila_cheia(FilaTriagem *fila);

int inserir_paciente_fila(FilaTriagem *fila, Paciente paciente);

Paciente remover_paciente_fila(FilaTriagem *fila);

void mostrar_fila(FilaTriagem *fila);

void apagar_fila(FilaTriagem **fila);


#endif