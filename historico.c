#include "historico.h"
#include <stdbool.h>
#define TAM 10
typedef struct no NO;

    struct no{
        ITEM* item[TAM];
        NO* anterior;
    };

    struct historico_{
        NO* topo;
        int tamanho;
    };

    HISTORICO* historico_criar(void){
        HISTORICO* historico = (HISTORICO*)malloc(sizeof(HISTORICO));
        if(historico != NULL){
            historico->topo = NULL;
            historico->tamanho = 0;
        }
        return(historico);    
    }
    