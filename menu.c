// menu.c

#include "menu.h"
#include "paciente.c" // n sei pq da erro se coloco o .h  WTF!!!!!
#include "historico.h"
#include "IO.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int exibirMenuPrincipal() {
    int opcao;
    system(CLEAR_SCREEN);
    
    printf("========================================\n");
    printf("   Pronto Socorro SUS - Menu Principal  \n");
    printf("========================================\n");
    printf("1. Registrar paciente\n");
    printf("2. Registrar obito de paciente\n");
    printf("3. Adicionar procedimento ao historico medico\n");
    printf("4. Desfazer procedimento do historico medico\n");
    printf("5. Chamar paciente para atendimento (Triagem)\n");
    printf("6. Mostrar fila de espera\n"); 
    printf("7. Mostrar historico do paciente\n");
    printf("8. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");

    if (scanf("%d", &opcao) != 1) {
        limpar_buffer();
        return -1;
    }
    limpar_buffer();
    return opcao;
}

// acoes do usuario
bool processarAcao(int acao, ListaPacientes *lista, FilaTriagem *fila) {
    
    
    bool deve_pausar = true; // permite que o usuário tenha tempo de ler as msg na tela antes de dar clear

    switch(acao){
        case 1: { // Registrar paciente (busca, cadastra, insere na fila)
            printf("\n--- Opcao 1: Registrar Paciente ---\n");
            printf("Digite o ID do paciente (0 para buscar/cadastrar): ");
            int id_input;
            if (scanf("%d", &id_input) != 1) {
                limpar_buffer();
                printf("ID invalido. Tente novamente.\n");
                break;
            }
            limpar_buffer();
            
            Paciente *p = buscar_paciente_por_id(lista, id_input);

            if (p != NULL) {
                printf("Paciente %s (ID %d) encontrado na base de dados.\n", get_nome_paciente(p), get_id_paciente(p));
            } else {
                printf("Paciente ID %d nao encontrado. Cadastrando novo paciente.\n", id_input);
                char nome_paciente[100];
                printf("Digite o nome completo do paciente: ");
                if (fgets(nome_paciente, sizeof(nome_paciente), stdin) != NULL) {
                    nome_paciente[strcspn(nome_paciente, "\n")] = '\0';
                } else {
                    break;
                }
                
            
                p = criar_paciente(id_input, nome_paciente); // o histórico é ligado a ele nessa função
                if (p == NULL) {
                    printf("Erro ao criar paciente.\n");
                    break;
                }
                
                inserir_paciente_lista(lista, p); 
                printf("Paciente %s registrado na base de dados.\n", get_nome_paciente(p));
            }

            if (fila_cheia(fila)) { 
                printf("ERRO: A fila de triagem esta cheia! Nao foi possivel adicionar.\n");
            } else {
                inserir_paciente_fila(fila, *p); 
                printf("Paciente enviado para a fila de triagem com sucesso.\n");
            }

            break;
        }
        case 5: { // Chamar paciente para atendimento
            printf("\n--- Opcao 5: Chamar Paciente ---\n");
            if (fila_vazia(fila)) { 
                printf("Nao ha pacientes na fila de triagem para atendimento.\n");
            } else {
                Paciente paciente_atendido = remover_paciente_fila(fila); 
                printf("Paciente CHAMADO: %s (ID %d). Agora esta em atendimento medico.\n", 
                       paciente_atendido.nome, paciente_atendido.id);
            }
            break;
        }
        case 6: // Mostrar fila de espera
            printf("\n--- Opcao 6: Mostrar Fila de Espera ---\n");
            mostrar_fila(fila); 
            break;

        // --- essa parte é mais fácil a gi implementar, é a parte que mexe com o histórico e os procedimentos ---
        case 2: 
        case 3:
        case 4:
        case 7: 
        // ---------------------------------------------
            
        case 8: // Sair
            printf("\n--- Opcao 8: Sair ---\n");
            SAVE(lista, fila, NULL); 
            printf("Salvando dados e encerrando o sistema...\n");
            deve_pausar = false; 
            return false; 
        default:
            printf("\nOpcao invalida (%d). Por favor, digite uma opcao valida.\n", acao);
            break;
    }

    // Pausa para o usuário ver a saída
    if (deve_pausar) {
        printf("\nPressione ENTER para voltar ao menu...");
        limpar_buffer();
    }
    return true; //true continua o loop da main
}