#include <stdio.h>
#include <stdlib.h>
#include "lista_pacientes.h"
#include "fila_triagem.h"
#include "IO.h"
#include "menu.h"

int main(){
    ListaPacientes *lista = criar_lista(); 
    FilaTriagem *fila = cria_fila();       

    LOAD(&lista, &fila, NULL); 

    int acao;
    bool continuar_programa = true;

    while(continuar_programa){
        acao = exibirMenuPrincipal();
        continuar_programa = processarAcao(acao, lista, fila);
    }

    liberar_lista(&lista);
    apagar_fila(&fila); 

    return 0;
}