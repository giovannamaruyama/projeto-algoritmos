#include "fila_triagem.h"
#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>


struct fila{
    Paciente *pacientes[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
};

FilaTriagem* cria_fila() {
    FilaTriagem *fila = (FilaTriagem*) malloc(sizeof(FilaTriagem));
    if (fila != NULL) {
        fila->inicio = 0;
        fila->fim = -1;
        fila->quantidade = 0;
    }
    return fila;
}

int get_inicio_fila (FilaTriagem *fila){
    return fila->inicio;
}

int get_fim_fila (FilaTriagem *fila){
    return fila->fim;
}

int get_tamanho_fila (FilaTriagem *fila){
    return fila->quantidade;
}

// Retorna o Paciente * no índice dado 
Paciente* get_paciente_at_fila(FilaTriagem *fila, int index) {
    if (fila != NULL && index >= 0 && index < TAMANHO_FILA) {
        return fila->pacientes[index];
    }
    return NULL;
}


int fila_vazia(FilaTriagem *fila) {
    return fila->quantidade == 0;
}


int fila_cheia(FilaTriagem *fila) {
    return fila->quantidade == TAMANHO_FILA;
}


int inserir_paciente_fila(FilaTriagem *fila, Paciente *novo_paciente) { 
    if (fila_cheia(fila)) {
        return 0;
    }
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    fila->pacientes[fila->fim] = novo_paciente;
    fila->quantidade++;
    return 1; 
}

// verificar se a fila esta vazia antes de chamar esta funcao
Paciente* remover_paciente_fila(FilaTriagem *fila) {
    if (fila_vazia(fila)) {
        return NULL;
    }

    Paciente *pacienteAtendido = fila->pacientes[fila->inicio];
    
    fila->pacientes[fila->inicio] = NULL; 
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->quantidade--;
    
    // dar free(pacienteAtendido) onde chamar essa funcao
    return pacienteAtendido;
}


void mostrar_fila(FilaTriagem *fila) {
    if (fila_vazia(fila)) {
        printf("A fila de espera está vazia.\n");
        return;
    }

    printf("Fila de espera (ordem de atendimento):\n");
    int i = fila->inicio;
    int count = 0;
    while (count < fila->quantidade) {
        Paciente *p = fila->pacientes[i];
        printf("ID: %d, Nome: %s\n", get_id_paciente(p), get_nome_paciente(p));
        i = (i + 1) % TAMANHO_FILA;
        count++;
    }
}

void apagar_fila(FilaTriagem **fila) {
    if(fila != NULL && *fila != NULL) {
        free(*fila);
        *fila = NULL;
    }
}

