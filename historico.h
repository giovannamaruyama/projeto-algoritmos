#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>
#include "procedimentos.h"

    typedef struct historico_ HISTORICO;
    HISTORICO* historico_criar(int paciente_id, const char *paciente_nome);
    bool historico_cheio(HISTORICO *h);
    bool historico_vazio(HISTORICO *h);
    bool historico_addprocedimento(HISTORICO *h, PROCEDIMENTO *p);
    PROCEDIMENTO* historico_removeprocedimento(HISTORICO *h);
    PROCEDIMENTO* historico_consultar_ultimo(HISTORICO *h);
    void historico_imprimir(HISTORICO *h);
    void historico_apagar(HISTORICO **h);
    int historico_get_paciente_id(HISTORICO *h);
    const char* historico_get_paciente_nome(HISTORICO *h);

    #endif




    
