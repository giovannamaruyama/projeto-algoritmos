
#define MAX_HISTORICO 10


typedef struct {
    int id; // ou string?
    char nome[100];
    // seria bom colocar a pilha de historico aqui
    // PilhaHistorico *historico;
} Paciente;


#define TAMANHO_FILA 50 

typedef struct {
    Paciente pacientes[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
} FilaTriagem;