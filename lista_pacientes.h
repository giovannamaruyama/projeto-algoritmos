#ifndef LISTA_PACIENTES_H
#define LISTA_PACIENTES_H

#include "paciente.h"// a merda do erro, q boosstaaaaa

typedef struct No {
    Paciente *paciente;
    struct No* anterior;
    struct No* proximo;
} NoLista;

typedef struct {
    NoLista* inicio;
    NoLista* fim;
    int tamanho;
} ListaPacientes;

ListaPacientes* criar_lista();
int inserir_paciente(ListaPacientes* lista, Paciente *novo_paciente);
Paciente* buscar_paciente(ListaPacientes* lista, int id);
int apagar_paciente(ListaPacientes* lista, int id);
void listar_todos_pacientes(ListaPacientes* lista);
void liberar_lista(ListaPacientes** lista);
Paciente* buscar_paciente_por_id(ListaPacientes *lista, int id);

#endif


