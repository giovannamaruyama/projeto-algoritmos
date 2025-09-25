#ifndef PROCEDIMENTOS_H
#define PROCEDIMENTOS_H

#include <stdbool.h>

typedef struct procedimento_ PROCEDIMENTO;

PROCEDIMENTO* procedimento_criar(const char *descricao, const char *data);
bool procedimento_apagar(PROCEDIMENTO **p);
const char* procedimento_get_nome(PROCEDIMENTO *p);
const char* procedimento_get_data(PROCEDIMENTO *p)
bool procedimento_set_nome(PROCEDIMENTO *p, const char *nome);
bool procedimento_set_data(PROCEDIMENTO *p, const char *data);
void procedimento_imprimir(PROCEDIMENTO *p);

#endif
