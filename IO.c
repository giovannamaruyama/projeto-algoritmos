// IO.C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "fila_triagem.h" 
#include "paciente.h"
#include "lista_pacientes.h"
#include "historico.h"



bool SAVE(ListaPacientes *lista, FilaTriagem *fila, HISTORICO *historico) {
    if(!lista || !fila)
        return false;

    //Salvando a Lista de Pacientes 
    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if(!fp_lista) return false;
    
    NoLista *no = lista->inicio;
    while (no != NULL) {
        // Salva apenas o ID do paciente 
        int paciente_id = get_id_paciente(no->paciente);
        fwrite(&paciente_id, sizeof(int), 1, fp_lista); 
        no = no->proximo;
    }
    fclose(fp_lista);

    //Salvando a Fila de Triagem
    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if(!fp_fila) return false;

    
    int i = get_inicio_fila(fila);
    int qtd = get_tamanho_fila(fila);
    int count = 0;
    while (count < qtd) {
    Paciente *p_na_fila = get_paciente_at_fila(fila, i); 
    if (p_na_fila) {
        int paciente_id = get_id_paciente(p_na_fila); 
        fwrite(&paciente_id, sizeof(int), 1, fp_fila);
    }
    i = (i + 1) % TAMANHO_FILA; 
    count++;
}
    fclose(fp_fila);

    // Salvando o Histórico de Todos os Pacientes 
    FILE *fp_historico = fopen("historicos.bin", "wb");
    if(!fp_historico) return false;

    
    no = lista->inicio;
    while (no != NULL) {
        HISTORICO *h = paciente_get_historico((no->paciente)); 

        int tam = historico_get_tamanho(h);
        
        if (h != NULL && tam > 0) { // Só salva se tiver procedimentos
            
            int id = historico_get_paciente_id(h);
            const char *nome = historico_get_paciente_nome(h);

            fwrite(&id, sizeof(int), 1, fp_historico);
            fwrite(nome, sizeof(char), 100, fp_historico);
            fwrite(&tam, sizeof(int), 1, fp_historico);

            // Salva cada procedimento na ordem do array
            for (int k = 0; k < tam; k++) {
                PROCEDIMENTO *p = historico_get_procedimento_at(h, k); 
                if (!procedimento_save(fp_historico,p)) { 
                    fclose(fp_historico);
                    return false; 
                }
            }
        }
        no = no->proximo;
    }
    fclose(fp_historico);
    
    return true;
}


bool LOAD(ListaPacientes **lista_ptr, FilaTriagem **fila_ptr, HISTORICO **historico) {
    
    ListaPacientes *lista = *lista_ptr;
    FilaTriagem *fila = *fila_ptr;

    if(!lista || !fila) return false;

    int chave; 

    //Carregando a Lista de Pacientes 
    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if(!fp_lista) return false;

    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        Paciente *paciente = criar_paciente(chave, "Carregado");
        if (paciente == NULL) { fclose(fp_lista); return false; }
        inserir_paciente(lista, paciente); 
        free(paciente);
    }
    fclose(fp_lista); 

    // Carregando e Restaurando o Histórico
    FILE *fp_historico = fopen("historicos.bin", "rb");
    if(fp_historico) { 
        int paciente_id, tamanho;
        char paciente_nome[100];

        while(fread(&paciente_id, sizeof(int), 1, fp_historico) == 1 &&
              fread(paciente_nome, sizeof(char), 100, fp_historico) == 1 &&
              fread(&tamanho, sizeof(int), 1, fp_historico) == 1) {

            // Cria a estrutura HISTORICO
            HISTORICO *h = historico_criar(paciente_id, paciente_nome);
            if (h == NULL) { fclose(fp_historico); return false; }

            // Busca o paciente na lista e liga o historico
            Paciente *paciente_na_lista = buscar_paciente_por_id(lista, paciente_id); 

            if (paciente_na_lista != NULL) {
                 // Liga o histórico ao paciente 
                  paciente_set_historico(paciente_na_lista,h);
            }

            //Carrega e adiciona os procedimentos (restaura a pilha)
            for (int k = 0; k < tamanho; k++) {
                PROCEDIMENTO *p = procedimento_load(fp_historico); 
                if (p == NULL) { 
                    fclose(fp_historico);
                    return false; 
                }
                // historico_addprocedimento restaura a ordem correta da pilha
                historico_addprocedimento(h, p); 
            }
        }
        fclose(fp_historico);
    }


    // Carregando a Fila de Triagem 
    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if(fp_fila) { 
        while(fread(&chave, sizeof(int), 1, fp_fila) == 1) {
            // Buscamos o paciente já com o histórico ligado na lista.
            Paciente *paciente_completo = buscar_paciente_por_id(lista, chave); 

            if (paciente_completo != NULL) {
                inserir_paciente_fila(fila, paciente_completo); 
            } 
        }
        fclose(fp_fila); 
    }

    return true;
}