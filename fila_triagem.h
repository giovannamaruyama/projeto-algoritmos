
#include "paciente.h"


void cria_fila();

int fila_vazia(FilaTriagem *fila);

int fila_cheia(FilaTriagem *fila);

int inserir_paciente_fila(FilaTriagem *fila, Paciente paciente);

Paciente remover_paciente_fila(FilaTriagem *fila);

void mostrar_fila(FilaTriagem *fila);

void salvar_fila(FilaTriagem *fila);
void carregar_fila(FilaTriagem *fila);