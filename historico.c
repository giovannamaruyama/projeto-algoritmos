#include "historico.h"
#include <stdbool.h>
#include <stdlib.h>
#define TAM 10

    struct historico_{
        ITEM* item[TAM];
        int tamanho;
    };

    HISTORICO* historico_criar(void){
        HISTORICO* historico = (HISTORICO*)malloc(sizeof(HISTORICO));
        if(historico != NULL){
            historico->tamanho = 0;
        }
        return(historico);    
    }
    
    bool historico_cheio(HISTORICO *historico){
        if(historico != NULL)
            return((historico->tamanho == TAM) ? true : false);
        return(false);
    }

    bool historico_vazio(HISTORICO *historico){
        if(historico != NULL)
            return((historico->tamanho == 0) ? true : false);
        return(false);
    }

    bool historico_addprocedimento(HISTORICO *historico, ITEM *procedimento){
        if((historico != NULL) && (!historico_cheio(historico))){
            historico->item[historico->tamanho] = procedimento;
            historico->tamanho++;
            return(true);
        }
        return(false);
    }
    
    ITEM* historico_removeprocedimento(HISTORICO *historico){
        ITEM* provisorio;
        if((historico != NULL) && (!historico_vazio(historico))){
            provisorio = historico->item[historico->tamanho -1];
            historico->item[historico->tamanho -1] = NULL;
            historico->tamanho--;
            return(provisorio);
        }
        return(NULL);
    }

   void historico_imprimir(HISTORICO *historico) {
    if (historico == NULL) {
        printf("Historico inexistente.\n");
        return;
    }
    if (historico_vazio(historico)) {
        printf("Historico vazio.\n");
        return;
    }
    printf("Historico de procedimentos do paciente:\n");
    for (int i = 0; i < historico->tamanho; i++) {
        printf("%d. %s\n", i + 1, item_get_chave(historico->item[i]));
    }
    }

    void historico_apagar(HISTORICO **historico){
        if (historico != NULL && *historico != NULL) {
        HISTORICO *h = *historico;
            for (int i = 0; i < h->tamanho; i++) {
                if (h->item[i] != NULL) {
                    item_apagar(&(h->item[i])); 
                }
            }
            free(h);
            *historico = NULL;
        }
    }