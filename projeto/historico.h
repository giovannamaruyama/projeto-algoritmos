#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>
#include "procedimentos.h"

typedef struct historico_ HISTORICO;

HISTORICO* historico_criar(int paciente_id, const char *paciente_nome);
void historico_apagar(HISTORICO **h);
bool historico_addprocedimento(HISTORICO *h, PROCEDIMENTO *p);
PROCEDIMENTO* historico_removeprocedimento(HISTORICO *h);
void historico_imprimir(HISTORICO *h);
int historico_get_tamanho(HISTORICO *h);
// Acessa item em índice específico (útil para salvar em disco)
PROCEDIMENTO* historico_get_procedimento_at(HISTORICO *h, int index);

#endif