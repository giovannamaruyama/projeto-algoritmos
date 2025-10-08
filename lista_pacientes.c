#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_pacientes.h"
#include "paciente.h"// tem q ser .h aqui

ListaPacientes* criar_lista() {
    ListaPacientes* lista = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

int inserir_paciente(ListaPacientes* lista, Paciente *novo_paciente) { 
    if (lista == NULL) return 0;

    if (buscar_paciente(lista, get_id_paciente(novo_paciente)) != NULL) {
        printf("Erro: ID de paciente ja cadastrado.\n");
        return 0;
    }

    NoLista* pnovo = (NoLista*) malloc(sizeof(NoLista));
    if (pnovo == NULL) return 0;
    // Cria novo paciente e insere na lista
    pnovo->paciente = novo_paciente;
    pnovo->anterior = NULL;

    if (lista->inicio == NULL) {
        pnovo->proximo = NULL;
        lista->fim = pnovo;
    } else {
        pnovo->proximo = lista->inicio;
        lista->inicio->anterior = pnovo;
    }

    lista->inicio = pnovo;
    lista->tamanho++;
    return 1;
}

Paciente* buscar_paciente(ListaPacientes* lista, int id) {
    if (lista == NULL) return NULL;
    NoLista* p = lista->inicio;
    while (p != NULL && get_id_paciente(p->paciente) != id) {
        p = p->proximo;
    }
    if (p != NULL) {
        return (p->paciente);
    }
    return NULL;
}

int apagar_paciente(ListaPacientes* lista, int id) {
    if (lista == NULL || lista->inicio == NULL) return 0;

    NoLista* p = lista->inicio;
    while (p != NULL && get_id_paciente(p->paciente) != id) {
        p = p->proximo;
    }

    if (p == NULL) return 0;

    if (p == lista->inicio) {
        lista->inicio = p->proximo;
    } else {
        p->anterior->proximo = p->proximo;
    }
    if (p == lista->fim) {
        lista->fim = p->anterior;
    } else {
        p->proximo->anterior = p->anterior;
    }
    free(p);
    lista->tamanho--;
    return 1;
}

void liberar_lista(ListaPacientes** lista) {
    if (*lista == NULL) return;

    NoLista* no_atual = (*lista)->inicio;
    while (no_atual != NULL) {
        NoLista* proximo = no_atual->proximo;
        free(no_atual);
        no_atual = proximo;
    }
    free(*lista);
    *lista = NULL;
}

void listar_pacientes(ListaPacientes* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    printf("Listagem de Todos os Pacientes\n");
    NoLista* atual = lista->inicio;
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", get_id_paciente(atual->paciente), get_nome_paciente(atual->paciente));
        atual = atual->proximo;
    }
}

Paciente* buscar_paciente_por_id(ListaPacientes *lista, int id) {
    if (lista == NULL) {
        return NULL;
    }

    NoLista *no_atual = lista->inicio;

    while (no_atual != NULL) {
        // Se o ID do paciente no nó atual for igual ao ID procurado
        if (get_id_paciente(no_atual->paciente) == id) {
            // Retorna o ponteiro para a struct Paciente dentro do nó
            return (no_atual->paciente);
        }
        no_atual = no_atual->proximo;
    }

    // paciente não foi encontrado
    return NULL;
}

