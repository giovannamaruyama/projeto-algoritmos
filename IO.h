#ifndef IO_H
	#define IO_H
	#include "paciente.h" 
    #include "fila_triagem.h" 
    #include "lista_pacientes.h" 
    #include "historico.h" 
    #include <stdbool.h>

    bool SAVE(ListaPacientes *lista, FilaTriagem *fila, HISTORICO *historico); // Salva os itens da lista e da fila em arquivos
    bool LOAD(ListaPacientes **lista, FilaTriagem **fila, HISTORICO **historico); // Carrega os itens dos arquivos na lista e na fila

#endif