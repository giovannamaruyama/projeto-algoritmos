#include <stdio.h>
#include <stdlib.h>


int exibirMenuPrincipal() {
    int opcao;

    system("cls || clear");

    printf("========================================\n");
    printf("   Pronto Socorro SUS - Menu Principal  \n");
    printf("========================================\n");
    printf("1. Registrar paciente\n");
    printf("2. Registrar obito de paciente\n");
    printf("3. Adicionar procedimento ao historico medico\n");
    printf("4. Desfazer procedimento do historico medico\n");
    printf("5. Chamar paciente para atendimento\n");
    printf("6. Mostrar fila de espera\n");
    printf("7. Mostrar historico do paciente\n");
    printf("8. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
    
    // Leitura da opcao
    scanf("%d", &opcao);

    return opcao;
}

