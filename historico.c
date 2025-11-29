#include "historico.h" 
#include "procedimentos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct no {
    PROCEDIMENTO *proc;      // dado armazenado
    struct no *anterior;     // ponteiro para o nó anterior (abaixo na pilha)
} NO;

struct historico_{
    int  paciente_id;
    char paciente_nome[100];
    NO *topo;      // nó do topo da pilha
    int tamanho;   // número de elementos
};

HISTORICO* historico_criar(int paciente_id, const char *paciente_nome){
    HISTORICO *h = (HISTORICO*) malloc(sizeof(HISTORICO));
    if (h!=NULL){
        h->paciente_id = paciente_id;
        // copia nome se existir
        if (paciente_nome){
            strncpy(h->paciente_nome, paciente_nome, sizeof(h->paciente_nome)-1);
            h->paciente_nome[sizeof(h->paciente_nome)-1] = '\0';
        } else {
            h->paciente_nome[0] = '\0';
        }
        h->topo = NULL;      // pilha vazia
        h->tamanho = 0;
    }
    return h;
}

bool historico_cheio(HISTORICO *h){
    if (h != NULL){
        NO *novo = (NO*) malloc(sizeof(NO));
        if (novo != NULL){
            free(novo);      // teste bem-sucedido
            return false;
        }
        return true;         // sem memória → considere cheia
        printf("Histórico está cheio!\n");
    }
    return true;
}

bool historico_vazio(HISTORICO *h){
    return (h != NULL) ? (h->tamanho == 0) : true;
}

bool historico_addprocedimento(HISTORICO *h, PROCEDIMENTO *p){
    if (h != NULL && p != NULL && !historico_cheio(h)){
        // cria novo nó
        NO *novo = (NO*) malloc(sizeof(NO));
        if (novo == NULL) return false;
        novo->proc = p;
        novo->anterior = h->topo; // encadeia no topo
        // atualiza topo
        h->topo = novo;
        h->tamanho++;
        return true;
    }
    return false;
}

PROCEDIMENTO* historico_removeprocedimento(HISTORICO *h){
    if (h != NULL && !historico_vazio(h)){
        NO *removido = h->topo;            // nó a remover
        PROCEDIMENTO *proc = removido->proc; // guarda o procedimento
        h->topo = removido->anterior;      // novo topo
        free(removido);                    // libera nó
        h->tamanho--;
        return proc;                       // devolve o procedimento
    }
    return NULL;
}

PROCEDIMENTO* historico_consultar_ultimo(HISTORICO *h){
    if (h != NULL && !historico_vazio(h)){
        return h->topo->proc;
    }
    return NULL;
}

void historico_imprimir(HISTORICO *h){
    if (!h){ 
        puts("Historico inexistente."); 
        return; 
    }
    printf("Historico do paciente ID=%d", h->paciente_id);
    if (h->paciente_nome[0] != '\0') 
        printf(" | Nome=%s", h->paciente_nome);
    puts("");
    if (historico_vazio(h)){
        puts("Historico vazio.");
        return;
    }
    int n = h->tamanho;
    // buffer para inverter ordem
    PROCEDIMENTO **buffer = (PROCEDIMENTO**) malloc(n * sizeof(PROCEDIMENTO*));
    if (buffer == NULL){
        //imprime do topo para a base
        NO *aux = h->topo;
        int i = n;
        while (aux != NULL){
            const char *nome = procedimento_get_nome(aux->proc);
            const char *data = procedimento_get_data(aux->proc);
            printf("%d. %s", i, nome ? nome : "(sem nome)");
            if (data && data[0] != '\0') printf(" | Data: %s", data);
            puts("");
            aux = aux->anterior;
            i--;
        }
        return;
    }
    // copia os ponteiros invertendo posições
    NO *aux = h->topo;
    int idx = n - 1;
    while (aux != NULL){
        buffer[idx] = aux->proc;
        aux = aux->anterior;
        idx--;
    }
    // imprime do mais antigo → mais recente
    for (int i = 0; i < n; i++){
        const char *nome = procedimento_get_nome(buffer[i]);
        const char *data = procedimento_get_data(buffer[i]);
        printf("%d. %s", i+1, nome ? nome : "(sem nome)");
        if (data && data[0] != '\0') printf(" | Data: %s", data);
        puts("");
    }

    free(buffer);
}

void historico_apagar(HISTORICO **h){
    if (h && *h){
        HISTORICO *ptr = *h;
        NO *aux = ptr->topo;
        // percorre liberando todos os nós
        while (aux != NULL){
            NO *proximo = aux->anterior;
            if (aux->proc) 
                procedimento_apagar(&aux->proc);
            free(aux);
            aux = proximo;
        }

        free(ptr);
        *h = NULL;
    }
}

int historico_get_paciente_id(HISTORICO *h){
    return h ? h->paciente_id : -1;
}

const char* historico_get_paciente_nome(HISTORICO *h){
    return h ? h->paciente_nome : NULL;
}

int historico_get_tamanho(HISTORICO *h) {
    return (h != NULL) ? h->tamanho : 0;
}

PROCEDIMENTO* historico_get_procedimento_at(HISTORICO *h, int index) {
    if (h != NULL && index >= 0 && index < h->tamanho) {
        int pos = h->tamanho - 1;   // topo é o último
        NO *aux = h->topo;
        // caminha até a posição correspondente à base
        while (aux != NULL && pos > index){
            aux = aux->anterior;
            pos--;
        }
        if (aux != NULL && pos == index)
            return aux->proc;
    }
    return NULL;
}
