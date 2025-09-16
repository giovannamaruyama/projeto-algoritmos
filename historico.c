#include "historico.h"
#include <stdbool.h>
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

    void historico_imprimir(HISTORICO *historico){
        if((historico != NULL) && (!historico_vazio(historico))){
            printf("Histórico de procedimentos do paciente:\n");
            for(int i = 0; i < historico->tamanho; i++){
                printf("%s \n", item[i]);
            }
        }

    }

    void historico_apagar(HISTORICO **historico){

    }