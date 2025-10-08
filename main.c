
#include "lista_pacientes.h"
#include "fila_triagem.h"
#include "menu.h"
#include "IO.h" 


void pausar_tela() {
    printf("\nPressione ENTER para continuar...");
    fflush(stdout); 
    limpar_buffer();
    getchar();
}

int main() {
    ListaPacientes *lista = criar_lista();
    FilaTriagem *fila = cria_fila();
    HISTORICO *historico_principal = NULL; 

    
    if (LOAD(&lista, &fila, &historico_principal)) {
        printf("Dados carregados com sucesso!\n");
        pausar_tela();

    } else {
        printf("Nenhum dado salvo encontrado ou erro ao carregar. Iniciando com estruturas vazias.\n");
        pausar_tela();
    }
    
    

    int acao;
    bool continuar = true;

    while (continuar) {
        acao = exibirMenuPrincipal();
        continuar = processarAcao(acao, lista, fila);
    }
    

    return 0;
}