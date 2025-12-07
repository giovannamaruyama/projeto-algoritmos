#include "fila_triagem.h"
#include <stdlib.h>
#include <stdio.h>

// Estrutura da fila de triagem implementada como um heap binário (máxima prioridade no topo)
struct fila {
    Paciente **data;   // Vetor de ponteiros para pacientes
    int size;          // Quantidade atual de elementos no heap
    int capacity;      // Capacidade máxima atual (valor aumenta dinamicamente)
};


// Cria uma nova fila (heap) com capacidade inicial de 100 elementos
FilaTriagem* cria_fila() {
    FilaTriagem *f = (FilaTriagem*) malloc(sizeof(FilaTriagem));
    if (f) {
        f->capacity = 100;
        f->data = (Paciente**) malloc(f->capacity * sizeof(Paciente*));
        f->size = 0;
    }
    return f;
}

// Função que compara prioridade entre dois pacientes:
bool maior_prio(Paciente *a, Paciente *b) {
    if (get_prioridade_paciente(a) < get_prioridade_paciente(b)) return true;
    if (get_prioridade_paciente(a) > get_prioridade_paciente(b)) return false;
    return get_ordem_chegada(a) < get_ordem_chegada(b);
}

// Troca dois ponteiros dentro do heap
void swap(Paciente **a, Paciente **b) { 
    Paciente *t = *a; 
    *a = *b; 
    *b = t; 
}

// Função "up" → sobe um elemento no heap enquanto ele for melhor que o pai
void up(FilaTriagem *f, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (maior_prio(f->data[i], f->data[pai])) { 
            swap(&f->data[i], &f->data[pai]); 
            i = pai; 
        }
        else break;
    }
}

// Função "down" → desce um elemento no heap para restaurar a ordem
void down(FilaTriagem *f, int i) {
    int maior = i;
    int e = 2*i + 1, d = 2*i + 2;

    if (e < f->size && maior_prio(f->data[e], f->data[maior])) maior = e;
    if (d < f->size && maior_prio(f->data[d], f->data[maior])) maior = d;

    if (maior != i) { 
        swap(&f->data[i], &f->data[maior]); 
        down(f, maior); 
    }
}

// Insere um paciente no heap (fila de prioridade)
// Realoca memória se necessário e mantém o heap organizado
int inserir_paciente_fila(FilaTriagem *f, Paciente *p) {
    if (!f || !p) return 0;

    if (f->size == f->capacity) {
        f->capacity *= 2;
        f->data = realloc(f->data, f->capacity * sizeof(Paciente*));
    }

    f->data[f->size] = p;
    up(f, f->size);
    f->size++;
    return 1;
}

// Remove o paciente de maior prioridade (topo do heap)
Paciente* remover_paciente_fila(FilaTriagem *f) {
    if (!f || f->size == 0) return NULL;

    Paciente *r = f->data[0];            // paciente do topo
    f->data[0] = f->data[f->size - 1];   // troca com o último
    f->size--;

    if (f->size > 0) down(f, 0);

    return r;
}

// Verifica se um paciente com dado ID está presente no heap
bool fila_contem_paciente(FilaTriagem *f, int id) {
    if (!f) return false;

    for (int i = 0; i < f->size; i++)
        if (get_id_paciente(f->data[i]) == id)
            return true;

    return false;
}

// Retorna o tamanho atual da fila
int get_tamanho_fila(FilaTriagem *f) { 
    return f ? f->size : 0; 
}

// Retorna o paciente armazenado numa posição específica do heap
// Usada pelo IO.c para salvar o estado da fila
Paciente* acessar_posicao_heap(FilaTriagem *f, int i) {
    return (f && i < f->size) ? f->data[i] : NULL;
}

// Funções auxiliares para exibir a fila ordenada 
int cmp_qsort(const void *a, const void *b) {
    Paciente *p1 = *(Paciente**)a;
    Paciente *p2 = *(Paciente**)b;

    if (maior_prio(p1, p2)) return -1;
    if (maior_prio(p2, p1)) return 1;
    return 0;
}

// Imprime a fila ordenada por prioridade e ordem de chegada
void mostrar_fila(FilaTriagem *f) {
    if (!f || f->size == 0) {
        printf("Fila vazia.\n");
        return;
    }

    Paciente **c = malloc(f->size * sizeof(Paciente*));
    for (int i = 0; i < f->size; i++)
        c[i] = f->data[i];

    qsort(c, f->size, sizeof(Paciente*), cmp_qsort);

    for (int i = 0; i < f->size; i++)
        printf("%d. Prio:%d ID:%d %s\n",
               i+1,
               get_prioridade_paciente(c[i]),
               get_id_paciente(c[i]),
               get_nome_paciente(c[i]));

    free(c);
}

// Libera a memória da fila
void apagar_fila(FilaTriagem **f) {
    if (f && *f) {
        free((*f)->data);
        free(*f);
        *f = NULL;
    }
}
