#ifndef LISTA_PACIENTES_H
#define LISTA_PACIENTES_H

#include "paciente.h"

typedef struct arvore ListaPacientes; 

ListaPacientes* criar_lista();
void liberar_lista(ListaPacientes** lista);
int inserir_paciente(ListaPacientes* lista, Paciente* novo_paciente);
Paciente* buscar_paciente(ListaPacientes* lista, int id);
int apagar_paciente(ListaPacientes* lista, int id);
void listar_todos_pacientes(ListaPacientes* lista);
int lista_get_tamanho(const ListaPacientes* lista);
// Callback para o IO percorrer a árvore
void percorrer_arvore_para_save(ListaPacientes* lista, void (*callback)(Paciente*, void*), void* param);

#endif