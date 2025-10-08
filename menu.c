// menu.c

#include "menu.h"
#include "paciente.h"
#include "historico.h"
#include "lista_pacientes.h"
#include "fila_triagem.h" 
#include "IO.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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

// Funcao auxiliar para obter o ID do paciente
Paciente* obter_paciente(ListaPacientes *lista) {
    int id_input;
    printf("Digite o ID do paciente: ");
    if (scanf("%d", &id_input) != 1) {
        limpar_buffer();
        printf("ID invalido.\n");
        return NULL;
    }
    limpar_buffer();

    Paciente *p = buscar_paciente_por_id(lista, id_input);
    if (p == NULL) {
        printf("Erro: Paciente com ID %d nao encontrado.\n", id_input);
    }
    return p;
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
                
                inserir_paciente(lista, p); 
                printf("Paciente %s registrado na base de dados.\n", get_nome_paciente(p));
            }

            if (fila_cheia(fila)) { 
                printf("ERRO: A fila de triagem esta cheia! Nao foi possivel adicionar.\n");
            } else {
                inserir_paciente_fila(fila, p); 
                printf("Paciente enviado para a fila de triagem com sucesso.\n");
            }

            break;
        }
        
        case 2: { // Registrar óbito de paciente
            printf("\n--- Opcao 2: Registrar Obito ---\n");
            Paciente *p = obter_paciente(lista);
            if (p == NULL) break;
            
            int id = get_id_paciente(p);
            
            // paciente na fila não pode ser apagado
            if (fila_contem_paciente(fila, id)) {
                printf("ERRO: O paciente %s (ID %d) esta atualmente na fila de triagem e nao pode ser apagado.\n", get_nome_paciente(p), id);
                break; // Sai do case
            }
            
            
            if (apagar_paciente(lista, id)) {
                printf("Paciente %s (ID %d) removido da lista de pacientes.\n", get_nome_paciente(p), id);
                
                liberar_paciente(p); 
                
                printf("Registro de obito concluido.\n");
            } else {
                printf("Erro: Nao foi possivel apagar o paciente da lista (nao deveria acontecer).\n");
            }
            break;
        }
        
        case 3: { // Adicionar procedimento ao historico medico
            printf("\n--- Opcao 3: Adicionar Procedimento ---\n");
            Paciente *p = obter_paciente(lista);
            if (p == NULL) break;
            
            printf("Paciente: %s (ID %d)\n", get_nome_paciente(p), get_id_paciente(p));
            
            char descricao[256];
            int medico_id;
            char data_str[20];
            
            printf("Digite a descrição do procedimento: ");
            if (fgets(descricao, sizeof(descricao), stdin) != NULL) {
                descricao[strcspn(descricao, "\n")] = '\0';
            } else {
                break;
            }
            
            printf("Digite o ID do Médico responsável: ");
            if (scanf("%d", &medico_id) != 1) {
                limpar_buffer();
                printf("ID de medico invalido.\n");
                break;
            }
            limpar_buffer();
            
        
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            strftime(data_str, sizeof(data_str), "%Y-%m-%d %H:%M:%S", t);
            
            
            PROCEDIMENTO *proc = procedimento_criar(descricao, data_str); 
            
            if (proc == NULL) {
                printf("Erro ao criar procedimento.\n");
                break;
            }
            
            HISTORICO *h = paciente_get_historico(p);
            historico_addprocedimento(h, proc); 
            
            printf("Procedimento '%s' adicionado ao histórico de %s.\n", descricao, get_nome_paciente(p));

            break;
        }
        
        case 4: { // Desfazer procedimento do historico medico
            printf("\n--- Opcao 4: Desfazer Procedimento ---\n");
            Paciente *p = obter_paciente(lista);
            if (p == NULL) break;
            
            HISTORICO *h = paciente_get_historico(p);
            if (historico_get_tamanho(h) == 0) {
                printf("O paciente %s nao possui procedimentos no historico para desfazer.\n", get_nome_paciente(p));
                break;
            }
            
            // Assume historico_removeprocedimento e procedimento_apagar existem
            PROCEDIMENTO *proc_removido = historico_removeprocedimento(h);
            
            if (proc_removido != NULL) {
                printf("Procedimento desfeito com sucesso: %s\n", procedimento_get_data(proc_removido)); // Assume get_descricao existe
                procedimento_apagar(&proc_removido); // Libera a memória do procedimento
            } else {
                printf("Erro ao desfazer procedimento.\n");
            }
            break;
        }
        
        case 5: { // Chamar paciente para atendimento
            printf("\n--- Opcao 5: Chamar Paciente ---\n");
            if (fila_vazia(fila)) { 
                printf("Nao ha pacientes na fila de triagem para atendimento.\n");
            } else {
                // remove_paciente_fila retorna o ponteiro que deve ser liberado pelo chamador se nao for mais usado.
                Paciente *paciente_atendido = remover_paciente_fila(fila); 
                printf("Paciente CHAMADO: %s (ID %d). Agora esta em atendimento medico.\n", 
                       get_nome_paciente(paciente_atendido), get_id_paciente(paciente_atendido));
            }
            break;
        }
        
        case 6: // Mostrar fila de espera
            printf("\n--- Opcao 6: Mostrar Fila de Espera ---\n");
            mostrar_fila(fila); 
            break;

        case 7: { // Mostrar historico do paciente
            printf("\n--- Opcao 7: Mostrar Histórico ---\n");
            Paciente *p = obter_paciente(lista);
            if (p == NULL) break;
            
            HISTORICO *h = paciente_get_historico(p);
            printf("Histórico de Atendimento: %s (ID %d)\n", get_nome_paciente(p), get_id_paciente(p));

            // Assume historico_imprimir(h) existe e lida com a pilha de procedimentos
            historico_imprimir(h); 
            break;
        }
            
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