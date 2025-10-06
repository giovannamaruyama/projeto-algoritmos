#include "fila_triagem.h"
#include "historico.h"
#include "lista_pacientes.h"
#include <stdio.h>
#include <stdlib.h>


int exibirMenuPrincipal() {
    int opcao;

    system("cls || clear");

    printf("========================================\n");
    printf("   Pronto Socorro SUS - Menu Principal  \n");
    printf("========================================\n");
    printf("1. Registrar paciente\n"); //se for 1 vez criar historico medico e mandar para fila de espera
    printf("2. Registrar obito de paciente\n"); // paciente n pode morrer na fila
    printf("3. Adicionar procedimento ao historico medico\n"); // paciente n pode estar morto
    printf("4. Desfazer procedimento do historico medico\n");
    printf("5. Chamar paciente para atendimento\n"); // tem q ter passado pela triagem
    printf("6. Mostrar fila de espera\n"); 
    printf("7. Mostrar historico do paciente\n");
    printf("8. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
    
    // Leitura da opcao
    scanf("%d", &opcao);

    return opcao;
}

<<<<<<< HEAD
=======
int acao;
bool ativo = true;

char nome_paciente[100];
printf("Digite o nome do paciente: ");
fgets(nome_paciente, sizeof(nome_paciente), stdin);
printf("Paciente registrado: %s\n", nome_paciente);
ListaPacientes *lista = criar_lista(); //Não sei se é para criar a lista aqui!!REVISAR
FilaTriagem *fila = cria_fila();
while(ativo){
    acao = exibirMenuPrincipal();
    switch(acao){
        case 1: 
        printf("Registrar paciente\n");
        if()
            
        
    }
}
>>>>>>> dff17177f46ac564fd364d6261685ed5e2bff87d

