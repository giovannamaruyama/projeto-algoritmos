#include <stdio.h> 
#include <stdlib.h>
#include "lista_pacientes.h"

// Nó interno da AVL contendo um paciente
typedef struct no_arvore {
    Paciente* paciente;
    struct no_arvore *esq, *dir;
    int altura;
} NoArvore;

// Estrutura principal da lista de pacientes (AVL)
struct arvore {
    NoArvore* raiz;
    int quantidade;
};

// Retorna o maior entre dois valores
int max_val(int a, int b) { return (a > b) ? a : b; }

// Retorna a altura de um nó ou -1 se for NULL
int altura_no(NoArvore* no) { return no ? no->altura : -1; }

// Calcula o fator de balanceamento de um nó
int fator_bal(NoArvore* no) { return no ? altura_no(no->esq) - altura_no(no->dir) : 0; }

// Rotação simples à direita (AVL)
NoArvore* rot_dir(NoArvore* y) {
    NoArvore* x = y->esq;
    NoArvore* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = max_val(altura_no(y->esq), altura_no(y->dir)) + 1;
    x->altura = max_val(altura_no(x->esq), altura_no(x->dir)) + 1;

    return x;
}

// Rotação simples à esquerda (AVL)
NoArvore* rot_esq(NoArvore* x) {
    NoArvore* y = x->dir;
    NoArvore* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = max_val(altura_no(x->esq), altura_no(x->dir)) + 1;
    y->altura = max_val(altura_no(y->esq), altura_no(y->dir)) + 1;

    return y;
}

// Atualiza altura e aplica rotações necessárias para balancear o nó
NoArvore* balancear(NoArvore* no) {
    if (!no) return NULL;

    no->altura = 1 + max_val(altura_no(no->esq), altura_no(no->dir));
    int bal = fator_bal(no);

    if (bal > 1 && fator_bal(no->esq) >= 0) return rot_dir(no);
    if (bal > 1 && fator_bal(no->esq) < 0) { no->esq = rot_esq(no->esq); return rot_dir(no); }

    if (bal < -1 && fator_bal(no->dir) <= 0) return rot_esq(no);
    if (bal < -1 && fator_bal(no->dir) > 0) { no->dir = rot_dir(no->dir); return rot_esq(no); }

    return no;
}

// Insere um paciente na AVL recursivamente
NoArvore* inserir_no(NoArvore* no, Paciente* p, int* sucesso) {
    if (!no) {
        NoArvore* novo = (NoArvore*) malloc(sizeof(NoArvore));
        if (novo) { 
            novo->paciente = p; 
            novo->esq = novo->dir = NULL; 
            novo->altura = 0; 
            *sucesso = 1; 
        }
        return novo;
    }

    int id = get_id_paciente(p);
    int atual = get_id_paciente(no->paciente);

    if (id < atual) no->esq = inserir_no(no->esq, p, sucesso);
    else if (id > atual) no->dir = inserir_no(no->dir, p, sucesso);
    else { 
        *sucesso = 0; 
        return no; 
    }

    return balancear(no);
}

// Cria a lista de pacientes (raiz da AVL)
ListaPacientes* criar_lista() {
    ListaPacientes* l = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    if(l) { 
        l->raiz = NULL; 
        l->quantidade = 0; 
    }
    return l;
}

// Insere paciente na AVL
int inserir_paciente(ListaPacientes* lista, Paciente* p) {
    if (!lista || !p) return 0;
    int sucesso = 0;
    lista->raiz = inserir_no(lista->raiz, p, &sucesso);

    if (sucesso) lista->quantidade++;
    return sucesso;
}

// Busca recursiva por ID dentro da AVL
Paciente* buscar_rec(NoArvore* no, int id) {
    if (!no) return NULL;

    int atual = get_id_paciente(no->paciente);

    if (id == atual) return no->paciente;
    if (id < atual) return buscar_rec(no->esq, id);
    return buscar_rec(no->dir, id);
}

// Busca pública: consulta a partir da raiz
Paciente* buscar_paciente(ListaPacientes* lista, int id) {
    return lista ? buscar_rec(lista->raiz, id) : NULL;
}

// Retorna o nó mais à esquerda (menor ID)
NoArvore* menor_no(NoArvore* no) {
    while (no->esq) no = no->esq;
    return no;
}

// Remove um nó da AVL preservando balanceamento
NoArvore* apagar_no(NoArvore* no, int id, int* sucesso, Paciente** removido) {
    if (!no) return NULL;

    int atual = get_id_paciente(no->paciente);

    if (id < atual) no->esq = apagar_no(no->esq, id, sucesso, removido);
    else if (id > atual) no->dir = apagar_no(no->dir, id, sucesso, removido);
    else {
        *sucesso = 1;
        *removido = no->paciente;

        if (!no->esq || !no->dir) {
            NoArvore* temp = no->esq ? no->esq : no->dir;

            if (!temp) { 
                temp = no; 
                no = NULL; 
            }
            else { 
                *no = *temp; 
                free(temp); 
                temp = NULL; 
            }

            if(temp) free(temp);
        } 
        else {
            NoArvore* temp = menor_no(no->dir);
            no->paciente = temp->paciente;

            Paciente* dummy; 
            no->dir = apagar_no(no->dir, get_id_paciente(temp->paciente), sucesso, &dummy);
        }
    }
    return balancear(no);
}

// Apaga um paciente da AVL e libera sua memória
int apagar_paciente(ListaPacientes* lista, int id) {
    if (!lista) return 0;

    int sucesso = 0;
    Paciente* removido = NULL;

    lista->raiz = apagar_no(lista->raiz, id, &sucesso, &removido);

    if (sucesso) {
        lista->quantidade--;
        liberar_paciente(removido);
    }
    return sucesso;
}

// Impressão em-ordem (classifica por ID)
void in_order_print(NoArvore* no) {
    if(no) {
        in_order_print(no->esq);
        printf("ID: %d | Nome: %s | Prio: %d\n",
               get_id_paciente(no->paciente),
               get_nome_paciente(no->paciente),
               get_prioridade_paciente(no->paciente));
        in_order_print(no->dir);
    }
}

// Lista todos os pacientes em ordem crescente de ID
void listar_todos_pacientes(ListaPacientes* lista) {
    if(lista) in_order_print(lista->raiz);
}

// Percorre árvore em pré-ordem chamando callback (usado para salvar)
void pre_order_save(NoArvore* no, void (*cb)(Paciente*, void*), void* p) {
    if(no) {
        cb(no->paciente, p);
        pre_order_save(no->esq, cb, p);
        pre_order_save(no->dir, cb, p);
    }
}

// Percorre árvore e aplica callback em cada paciente (para salvar em arquivo)
void percorrer_arvore_para_save(ListaPacientes* lista, void (*callback)(Paciente*, void*), void* param) {
    if(lista) pre_order_save(lista->raiz, callback, param);
}

// Libera todos os nós recursivamente
void liberar_nos_rec(NoArvore* no) {
    if(no) {
        liberar_nos_rec(no->esq);
        liberar_nos_rec(no->dir);
        liberar_paciente(no->paciente);
        free(no);
    }
}

// Libera toda a estrutura de lista de pacientes
void liberar_lista(ListaPacientes** lista) {
    if(lista && *lista) {
        liberar_nos_rec((*lista)->raiz);
        free(*lista);
        *lista = NULL;
    }
}

// Retorna a quantidade total de pacientes cadastrados
int lista_get_tamanho(const ListaPacientes* lista) { return lista ? lista->quantidade : 0; }
