/*
#include "IO.h"
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA *lista, FILA *fila) {
    if(!lista || !fila) 
        return false;
    
    ITEM *it; // Variável auxiliar 

    // Salvando os itens da lista

    FILE *fp_lista = fopen("lista_itens.bin", "wb");
    if(!fp_lista)
        return false;

    it = LISTA_remover_inicio(lista);
    int chave;
    while(it != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = ITEM_get_chave(it);
        fwrite(&chave, sizeof(int), 1, fp_lista);
        // Apaga o item removido
        ITEM_apagar(&it);
        // Atualiza a variável auxiliar
        it = LISTA_remover_inicio(lista);
    }
    // Libera memória
    LISTA_apagar(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os itens da fila

    FILE *fp_fila = fopen("fila_itens.bin", "wb");
    if(!fp_fila)
        return false;

    it = FILA_remover(fila);
    while(it != NULL) { // Se mantém no while enquanto a fila não estiver vazia
        // Escreve a chave no arquivo
        chave = ITEM_get_chave(it);
        fwrite(&chave, sizeof(int), 1, fp_fila);
        // Apaga o item removido
        ITEM_apagar(&it);
        // Atualiza a variável auxiliar
        it = FILA_remover(fila);
    }
    // Libera memória
    FILA_apagar(&fila);
    fclose(fp_fila); fp_fila = NULL;

    return true;
}

bool LOAD(LISTA **lista, FILA **fila) {
    if(!*lista || !*fila) 
        return false;

    int chave; // Variável auxiliar

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_itens.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        ITEM *it = ITEM_criar(chave);
        LISTA_inserir(*lista, it);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_itens.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
        ITEM *it = ITEM_criar(chave);
        FILA_inserir(*fila, it);
    }
    fclose(fp_fila); // Libera memória

    return true;
}*/

#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include "fila_triagem.h"
#include "paciente.h"
#include "paciente.c"

bool SAVE(LISTA *lista, FilaTriagem *fila) {
    if(!lista || !fila)
        return false;

    // Salvando os itens (pacientes) da lista
    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if(!fp_lista)
        return false;

    ITEM *it;
    int chave;
    it = LISTA_remover_inicio(lista);
    while (it != NULL) {
        chave = ITEM_get_chave(it); // obtém o id do paciente
        fwrite(&chave, sizeof(int), 1, fp_lista);
        ITEM_apagar(&it);
        it = LISTA_remover_inicio(lista);
    }
    LISTA_apagar(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os itens da fila

    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if(!fp_fila)
        return false;

    Paciente paciente;
    while (!fila_vazia(fila)) {
        paciente = remover_paciente_fila(fila);
        chave = paciente.id;
        fwrite(&chave, sizeof(int), 1, fp_fila);
    }
    apagar_fila(&fila);
    fclose(fp_fila); fp_fila = NULL;

    return true;
}

bool LOAD(LISTA **lista, FilaTriagem **fila) {
    
    if(!*lista || !*fila) 
        return false;

    int chave; // Variável auxiliar

    // Carregando os itens do arquivo na lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        Paciente *paciente = malloc(sizeof(Paciente));
        paciente->id = chave; //mudar funcao
        LISTA_inserir(*lista, paciente); //mudar funcao
    }
    fclose(fp_lista); // Libera memória

    // Carregando os itens do arquivo na fila

    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if(!fp_fila)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
        Paciente *paciente = malloc(sizeof(Paciente));
        paciente->id = chave; //mudar funcao
        inserir_paciente_fila(*fila, *paciente); 
    }
    fclose(fp_fila); // Libera memória

    return true;
}