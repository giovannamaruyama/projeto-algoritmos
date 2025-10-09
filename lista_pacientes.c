#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_pacientes.h"
#include "paciente.h"// tem q ser .h aqui
typedef struct no {
    Paciente* paciente;
    struct no* proximo;
    struct no* anterior;
} NoLista;

struct lista {
    NoLista* inicio;
    NoLista* fim;
    int tamanho;
};

ListaPacientes* criar_lista() {
    ListaPacientes* lista = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    if (lista) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

int inserir_paciente(ListaPacientes* lista, Paciente* novo_paciente) {
    if (lista == NULL || novo_paciente == NULL) return 0;

    NoLista* pnovo = (NoLista*) malloc(sizeof(NoLista));
    if (!pnovo) return 0;

    pnovo->paciente = novo_paciente;
    pnovo->anterior = NULL;
    pnovo->proximo = lista->inicio;

    if (lista->inicio)
        lista->inicio->anterior = pnovo;
    else
        lista->fim = pnovo;

    lista->inicio = pnovo;
    lista->tamanho++;
    return 1;
}

Paciente* buscar_paciente(ListaPacientes* lista, int id) {
    if (!lista) return NULL;
    NoLista* p = lista->inicio;

    while (p) {
        if (get_id_paciente(p->paciente) == id)
            return p->paciente;
        p = p->proximo;
    }
    return NULL;
}

int apagar_paciente(ListaPacientes* lista, int id) {
    if (!lista) return 0;

    NoLista* p = lista->inicio;
    while (p && get_id_paciente(p->paciente) != id) {
        p = p->proximo;
    }
    if (!p) return 0;

    if (p->anterior)
        p->anterior->proximo = p->proximo;
    else
        lista->inicio = p->proximo;

    if (p->proximo)
        p->proximo->anterior = p->anterior;
    else
        lista->fim = p->anterior;

    // NÃO dá free no paciente, pois é responsabilidade externa
    free(p);
    lista->tamanho--;
    return 1;
}

void listar_todos_pacientes(ListaPacientes* lista) {
    if (!lista || !lista->inicio) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    NoLista* atual = lista->inicio;
    while (atual) {
        printf("ID: %d | Nome: %s\n",
               get_id_paciente(atual->paciente),
               get_nome_paciente(atual->paciente));
        atual = atual->proximo;
    }
}

void liberar_lista(ListaPacientes** lista) {
    if (!lista || !*lista) return;

    NoLista* atual = (*lista)->inicio;
    while (atual) {
        NoLista* prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    free(*lista);
    *lista = NULL;
}

NoLista* lista_get_inicio(const ListaPacientes* lista) {
    if (lista) {
        return lista->inicio;
    }
    return NULL;
}

NoLista* no_get_proximo(const NoLista* no) {
    if (no) {
        return no->proximo;
    }
    return NULL;
}

Paciente* no_get_paciente(const NoLista* no) {
    if (no) {
        return no->paciente;
    }
    return NULL;
}

int lista_get_tamanho(const ListaPacientes* lista) {
    if (lista) {
        return lista->tamanho;
    }
    return 0;
}

