#include "lista_pacientes.h"
#include "fila_triagem.h"
#include "menu.h"
#include "IO.h" 
#include <stdio.h>

int main() {
    ListaPacientes *lista = criar_lista();
    FilaTriagem *fila = cria_fila();

    if (LOAD(&lista, &fila, NULL)) {
        printf("Dados carregados do disco.\n");
    } else {
        printf("Iniciando sistema vazio.\n");
    }

    while (processarAcao(exibirMenuPrincipal(), lista, fila));

    liberar_lista(&lista);
    apagar_fila(&fila);
    return 0;
}