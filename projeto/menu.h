#ifndef MENU_H
#define MENU_H
#include <stdbool.h>
#include "lista_pacientes.h"
#include "fila_triagem.h"

//Exibe o menu principal na tela e retorna a opção escolhida
int exibirMenuPrincipal();

//Processa a ação escolhida no menu e retorna true para continuar o programa e false para encerrar.
bool processarAcao(int acao, ListaPacientes *lista, FilaTriagem *fila);

void limpar_buffer();

//Define o valor atual do contador de ordem de chegada dos pacientes
void set_seqchegada(unsigned long valor);

//Retorna o valor atual do contador de ordem de chegada
unsigned long get_seqchegada();

#endif
