#ifndef FILA_H
	#define FILA_H
	#include "../Item/item.h"

	typedef struct fila_ FILA;

	FILA *fila_criar(int capacidade); // lembrar de definiir um tam max
	bool fila_inserir(FILA *fila, ITEM *item);
	ITEM *fila_remover(FILA *fila);
	void fila_apagar(FILA **fila);

	ITEM *fila_frente(FILA *fila);
	int fila_tamanho(FILA *fila);
	bool fila_vazia(FILA *fila);
	bool fila_cheia(FILA *fila);
	void fila_imprimir(FILA *fila);

	  
#endif
