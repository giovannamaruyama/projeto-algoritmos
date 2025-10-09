#ifndef LISTA_PACIENTES_H
#define LISTA_PACIENTES_H

#include "paciente.h"//

typedef struct lista ListaPacientes;
typedef struct no NoLista;

ListaPacientes* criar_lista();
int inserir_paciente(ListaPacientes* lista, Paciente* novo_paciente);
Paciente* buscar_paciente(ListaPacientes* lista, int id);
int apagar_paciente(ListaPacientes* lista, int id);
void listar_todos_pacientes(ListaPacientes* lista);
void liberar_lista(ListaPacientes** lista);
NoLista* lista_get_inicio(const ListaPacientes* lista);
NoLista* no_get_proximo(const NoLista* no);
Paciente* no_get_paciente(const NoLista* no);
int lista_get_tamanho(const ListaPacientes* lista);

#endif


