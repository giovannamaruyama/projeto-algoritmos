#include "menu.h"
#include "paciente.h"
#include "historico.h"
#include "procedimentos.h"
#include "lista_pacientes.h"
#include "fila_triagem.h"
#include "IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Variável responsável por registrar a sequência de chegada e garante que cada paciente receba um número único e crescente ao ser registrado
static unsigned long contador = 0;

// Define o valor atual do contador de ordem de chegada
void set_seqchegada(unsigned long valor){
    contador = valor;
}

// Retorna o valor atual do contador de ordem de chegada
unsigned long get_seqchegada(){
    return contador;
}

// Função que limpa caracteres sobrando no stdin.
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // descarta caracteres restantes
    }
}

// Solicita ao usuário um ID e retorna o ponteiro do paciente
static Paciente* pedir_paciente_por_id(ListaPacientes *lista) {
    if (!lista) return NULL;
    int id;
    printf("Digite o ID do paciente: ");
    if (scanf("%d", &id) != 1) {
        limpar_buffer();
        printf("ID invalido.\n");
        return NULL;
    }
    limpar_buffer();

    Paciente *p = buscar_paciente(lista, id);
    if (!p) {
        printf("Paciente com ID %d nao encontrado.\n", id);
    }
    return p;
}

// Exibe o menu principal e retorna a opção escolhida pelo usuário.
// Caso a leitura falhe, retorna -1.
int exibirMenuPrincipal() {
    int op;
    printf("\n-----------------------------------------\n");
    printf("     PRONTO SOCORRO - PROJETO 2\n");
    printf("-----------------------------------------\n");
    printf("1. Registrar paciente (triagem)\n");
    printf("2. Remover paciente do hospital\n");
    printf("3. Listar todos os pacientes\n");
    printf("4. Buscar paciente por ID\n");
    printf("5. Mostrar fila de espera\n");
    printf("6. Dar alta (chamar pro atendimento)\n");
    printf("7. Mostrar historico do paciente  \n");
    printf("8. Adicionar procedimento        \n");
    printf("9. Desfazer procedimento          \n");
    printf("10. Sair\n");
    printf("-----------------------------------------\n");
    printf("Escolha uma opcao: ");

    if (scanf("%d", &op) != 1) {
        limpar_buffer();
        return -1;
    }
    limpar_buffer();
    return op;
}

//Função principal de controle do menu, que executa a operação selecionada pelo usuário.
//Retorna false quando o programa deve encerrar.

bool processarAcao(int acao, ListaPacientes *lista, FilaTriagem *fila) {
    switch (acao) {
        case 1: { //Registra novo paciente
            int id;
            printf("\n--- Registrar paciente ---\n");
            printf("ID: ");

            if (scanf("%d", &id) != 1) {
                limpar_buffer();
                printf("ID invalido.\n");
                break;
            }
            limpar_buffer();
            // Impede cadastro duplicado
            if (buscar_paciente(lista, id) != NULL) {
                printf("Erro: ja existe um paciente com ID %d.\n", id);
                break;
            }

            char nome[100];
            printf("Nome completo: ");
            if (!fgets(nome, sizeof(nome), stdin)) {
                printf("Erro ao ler nome.\n");
                break;
            }
            nome[strcspn(nome, "\n")] = '\0';  // remove quebra de linha
            
            int prio;
            printf("Prioridade ( 1)Emergência, 2) Muito urgente, 3) Urgente, 4) Pouco Urgente, 5) Não Urgência): ");
            if (scanf("%d", &prio) != 1) {
                limpar_buffer();
                printf("Prioridade invalida.\n");
                break;
            }
            limpar_buffer();
            if (prio < 1 || prio > 5) {
                printf("Prioridade fora do intervalo.\n");
                break;
            }
            // Incrementa sequência de chegada (ordem cronológica)
            contador++;
            // Cria uma nova estrutura Paciente
            Paciente *novo = criar_paciente(id, nome, prio, contador);
            if (!novo) {
                printf("Erro ao criar paciente.\n");
                break;
            }
            // Insere o paciente na árvore AVL (base do hospital)
            if (!inserir_paciente(lista, novo)) {
                printf("Erro ao inserir na base.\n");
                liberar_paciente(novo);
                break;
            }
            // Insere o paciente na fila de urgência (heap)
            if (!inserir_paciente_fila(fila, novo)) {
                printf("Erro ao inserir na fila.\n");
            } else {
                printf("Paciente cadastrado e inserido na fila.\n");
            }

            break;
        }

        case 2: { //2- Remover paciente do hospital
            printf("\n--- Remover paciente do hospital ---\n");
            Paciente *p = pedir_paciente_por_id(lista);
            if (!p) break;

            int id = get_id_paciente(p);

            // Verifica se o paciente ainda está na fila
            if (fila_contem_paciente(fila, id)) {
                printf("Erro: paciente esta na fila.\n");
                break;
            }

            if (apagar_paciente(lista, id)) {
                printf("Paciente removido.\n");
            } else {
                printf("Erro ao remover paciente.\n");
            }
            break;
        }

        case 3: {   // 3- Listar todos os pacientes cadastrados
            printf("\n--- Lista de pacientes ---\n");
            listar_todos_pacientes(lista);
            break;
        }

        case 4: { // 4- Buscar paciente por ID e exibir seus dados
            printf("\n--- Buscar paciente ---\n");
            Paciente *p = pedir_paciente_por_id(lista);
            if (p) {
                printf("ID: %d | Nome: %s | Prioridade: %d\n",
                       get_id_paciente(p),
                       get_nome_paciente(p),
                       get_prioridade_paciente(p));
            }
            break;
        }

        case 5: {    // 5. Mostrar fila de espera (em ordem de prioridade)
            printf("\n--- Fila de triagem ---\n");
            mostrar_fila(fila);
            break;
        }

        // 6- Dar alta (chamar paciente para atendimento)
        // Remove da fila, mas mantém na base de dados
        case 6: {
            printf("\n--- Dar alta ---\n");
            Paciente *p = remover_paciente_fila(fila);

            if (p) {
                printf("Chamando: %s (Prioridade %d)\n",
                       get_nome_paciente(p),
                       get_prioridade_paciente(p));
            } else {
                printf("Fila vazia.\n");
            }
            break;
        }

        case 7: {    // 7. Mostrar histórico do paciente (funcionalidade do projeto antigo)
            printf("\n--- Historico do paciente ---\n");
            Paciente *p = pedir_paciente_por_id(lista);
            if (!p) break;

            HISTORICO *h = paciente_get_historico(p);

            if (!h) {
                printf("Paciente sem historico.\n");
                break;
            }

            historico_imprimir(h);
            break;
        }

        case 8: {     // 8- Adicionar procedimento ao histórico (funcionalidade do projeto antigo)
            printf("\n--- Adicionar procedimento ---\n");

            Paciente *p = pedir_paciente_por_id(lista);
            if (!p) break;

            HISTORICO *h = paciente_get_historico(p);

            char descricao[100];
            printf("Descricao do procedimento: ");
            if (!fgets(descricao, sizeof(descricao), stdin)) {
                printf("Erro ao ler descricao.\n");
                break;
            }
            descricao[strcspn(descricao, "\n")] = '\0';

            // Gera timestamp simples
            char data_str[20];
            time_t agora = time(NULL);
            struct tm *t = localtime(&agora);

            if (t) {
                strftime(data_str, sizeof(data_str), "%Y-%m-%d %H:%M", t);
            } else {
                strcpy(data_str, "data_indef");
            }

            PROCEDIMENTO *proc = procedimento_criar(descricao, data_str);

            if (historico_addprocedimento(h, proc)) {
                printf("Procedimento registrado.\n");
            } else {
                printf("Erro ao adicionar procedimento.\n");
                procedimento_apagar(&proc);
            }
            break;
        }

 
        case 9: {         // 9- Desfazer último procedimento funcionalidade do projeto antigo)
            printf("\n--- Desfazer procedimento ---\n");

            Paciente *p = pedir_paciente_por_id(lista);
            if (!p) break;

            HISTORICO *h = paciente_get_historico(p);

            if (historico_get_tamanho(h) == 0) {
                printf("Historico vazio.\n");
                break;
            }

            PROCEDIMENTO *proc = historico_removeprocedimento(h);

            if (proc) {
                printf("Desfeito: %s (%s)\n",
                       procedimento_get_nome(proc),
                       procedimento_get_data(proc));
                procedimento_apagar(&proc);
            }
            break;
        }

        // 10- Sair do programa
        // Salva os dados no disco e encerra o loop
        case 10: {
            printf("\nSalvando dados...\n");
            SAVE(lista, fila, NULL);
            return false;
        }

        default:
            printf("\nOpcao invalida.\n");
            break;
    }

    // Retorna true para continuar o loop principal
    return true;
}

