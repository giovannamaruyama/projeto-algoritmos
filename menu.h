
#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "lista_pacientes.h" 
#include "fila_triagem.h"    


int exibirMenuPrincipal();
bool processarAcao(int acao, ListaPacientes *lista, FilaTriagem *fila); // manipula os tads

#endif 