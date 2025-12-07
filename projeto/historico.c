#include "historico.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// nó da pilha de procedimentos (lista encadeada ligada pelo campo 'anterior')
typedef struct no {
    PROCEDIMENTO *proc;
    struct no *anterior;
} NO;

// estrutura do histórico de um paciente
struct historico_{
    int  paciente_id;           // ID do paciente dono do histórico
    char paciente_nome[100];    // nome do paciente (cópia)
    NO *topo;                   // topo da pilha (último procedimento feito)
    int tamanho;                // quantidade de procedimentos
};

// cria e inicializa um novo histórico para um paciente
HISTORICO* historico_criar(int paciente_id, const char *paciente_nome){
    HISTORICO *h = (HISTORICO*) malloc(sizeof(HISTORICO));
    if (h){
        h->paciente_id = paciente_id;
        if (paciente_nome) strncpy(h->paciente_nome, paciente_nome, 99);
        else h->paciente_nome[0] = '\0';
        h->topo = NULL;
        h->tamanho = 0;
    }
    return h;
}

// empilha um novo procedimento no histórico (push)
bool historico_addprocedimento(HISTORICO *h, PROCEDIMENTO *p){
    if (!h || !p) return false;

    NO *novo = (NO*) malloc(sizeof(NO));
    if (!novo) return false;

    novo->proc = p;
    novo->anterior = h->topo;   // novo aponta para o antigo topo
    h->topo = novo;             // atualiza topo
    h->tamanho++;
    return true;
}

// remove o procedimento mais recente do histórico (pop)
PROCEDIMENTO* historico_removeprocedimento(HISTORICO *h){
    if (!h || h->tamanho == 0) return NULL;

    NO *removido = h->topo;
    PROCEDIMENTO *proc = removido->proc;

    h->topo = removido->anterior;   // "desempilha" o nó
    free(removido);
    h->tamanho--;
    return proc;
}

// imprime todos os procedimentos do histórico, do mais recente para o mais antigo
void historico_imprimir(HISTORICO *h){
    if (!h) return;

    printf("Historico (ID %d - %s): %d procedimentos\n",
           h->paciente_id, h->paciente_nome, h->tamanho);

    NO *aux = h->topo;
    while(aux){
        printf(" - %s [%s]\n",
               procedimento_get_nome(aux->proc),
               procedimento_get_data(aux->proc));
        aux = aux->anterior;
    }
}

// devolve o tamanho da pilha de procedimentos
int historico_get_tamanho(HISTORICO *h) { return h ? h->tamanho : 0; }

// libera todos os procedimentos e destrói o histórico
void historico_apagar(HISTORICO **h){
    if (h && *h){
        while((*h)->topo){
            PROCEDIMENTO *p = historico_removeprocedimento(*h);
            procedimento_apagar(&p);
        }
        free(*h);
        *h = NULL;
    }
}

// acessa o procedimento na posição 'index', onde 0 = mais antigo e tamanho-1 = mais recente
PROCEDIMENTO* historico_get_procedimento_at(HISTORICO *h, int index) {
    if (!h || index < 0 || index >= h->tamanho) return NULL;

    // o índice 0 representa a base da pilha, então precisamos caminhar
    // (tamanho - 1 - index) nós a partir do topo
    NO *aux = h->topo;
    int passos = (h->tamanho - 1) - index;

    for(int i = 0; i < passos; i++) {
        if(aux) aux = aux->anterior;
    }

    return aux ? aux->proc : NULL;
}
