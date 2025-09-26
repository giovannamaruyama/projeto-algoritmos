#include "historico.h"
#include "procedimentos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define TAM_HIST 10

struct historico_{
    int  paciente_id;
    char paciente_nome[100];
    PROCEDIMENTO* itens[TAM_HIST];
    int tamanho;
};

HISTORICO* historico_criar(int paciente_id, const char *paciente_nome){
    HISTORICO *h = (HISTORICO*) malloc(sizeof(HISTORICO));
    if (h!=NULL){
        h->paciente_id = paciente_id;
        if (paciente_nome){
            strncpy(h->paciente_nome, paciente_nome, sizeof(h->paciente_nome)-1);
            h->paciente_nome[sizeof(h->paciente_nome)-1] = '\0';
        } else {
            h->paciente_nome[0] = '\0';
        }
        h->tamanho = 0;
        for (int i=0;i<TAM_HIST;i++) h->itens[i] = NULL;
    }
    return h;
}

bool historico_cheio(HISTORICO *h){
    return (h != NULL) ? (h->tamanho == TAM_HIST) : false;
}

bool historico_vazio(HISTORICO *h){
    return (h != NULL) ? (h->tamanho == 0) : false;
}

bool historico_addprocedimento(HISTORICO *h, PROCEDIMENTO *p){
    if (h!= NULL && p!=NULL && !historico_cheio(h)){
        h->itens[h->tamanho++] = p;
        return true;
    }
    return false;
}

PROCEDIMENTO* historico_removeprocedimento(HISTORICO *h){
    if (h && !historico_vazio(h)){
        PROCEDIMENTO *aux = h->itens[h->tamanho - 1];
        h->itens[--h->tamanho] = NULL;
        return aux;
    }
    return NULL;
}

PROCEDIMENTO* historico_consultar_ultimo(HISTORICO *h){
    if (h && !historico_vazio(h)){
        return h->itens[h->tamanho - 1];
    }
    return NULL;
}

void historico_imprimir(HISTORICO *h){
    if (!h){ puts("Historico inexistente."); return; }
    printf("Historico do paciente ID=%d", h->paciente_id);
    if (h->paciente_nome[0] != '\0') printf(" | Nome=%s", h->paciente_nome);
    puts("");

    if (historico_vazio(h)){
        puts("Historico vazio.");
        return;
    }

    for (int i=0;i<h->tamanho;i++){
        const char *nome = procedimento_get_nome(h->itens[i]);
        const char *data = procedimento_get_data(h->itens[i]);
        printf("%d. %s", i+1, nome ? nome : "(sem nome)");
        if (data && data[0] != '\0') printf(" | Data: %s", data);
        puts("");
    }
}

void historico_apagar(HISTORICO **h){
    if (h && *h){
        HISTORICO *ptr = *h;
        for (int i=0;i<ptr->tamanho;i++){
            if (ptr->itens[i]) procedimento_apagar(&ptr->itens[i]);
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

