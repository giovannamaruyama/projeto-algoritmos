#include "fila_triagem.h"
#include "paciente.c"
#include <stdio.h>




typedef struct fila{
    Paciente pacientes[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
};

void inicia_fila(FilaTriagem *fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->quantidade = 0;
}


int fila_vazia(FilaTriagem *fila) {
    return fila->quantidade == 0;
}


int fila_cheia(FilaTriagem *fila) {
    return fila->quantidade == TAMANHO_FILA;
}


int inserir_paciente_fila(FilaTriagem *fila, Paciente paciente) { 
    if (filaCheia(fila)) {
        return 0;
    }
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    fila->pacientes[fila->fim] = paciente;
    fila->quantidade++;
    return 1; 
}

// verificar se a fila esta vazia antes de chamar esta funcao
Paciente remover_paciente_fila(FilaTriagem *fila) {
    if (filaVazia(fila)) {
        // retorna um paciente invalido
        Paciente pacienteInvalido;
        pacienteInvalido.id = -1;
        return pacienteInvalido;
    }
   
    Paciente pacienteAtendido = fila->pacientes[fila->inicio];
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    fila->quantidade--;
    return pacienteAtendido;
}


void mostrar_fila(FilaTriagem *fila) {
    if (filaVazia(fila)) {
        printf("A fila de espera está vazia.\n");
        return;
    }

    printf("Fila de espera (ordem de atendimento):\n");
    int i = fila->inicio;
    int count = 0;
    while (count < fila->quantidade) {
        printf("ID: %d, Nome: %s\n", fila->pacientes[i].id, fila->pacientes[i].nome);
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

void salvarFila(FilaTriagem *fila) {
    // usar arquivos
}

void carregarFila(FilaTriagem *fila) {
    // usar arquivos
}