#include "IO.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>

// Callback executado para CADA paciente na árvore
void salvar_paciente_completo(Paciente *p, void *arg) {
    FILE *fp = (FILE*)arg;
    
    // 1. Dados Básicos
    int id = get_id_paciente(p);
    char *nome = get_nome_paciente(p);
    int prio = get_prioridade_paciente(p);
    unsigned long ordem = get_ordem_chegada(p);
    char buffer[100] = {0};
    if(nome) strncpy(buffer, nome, 99);
    
    fwrite(&id, sizeof(int), 1, fp);
    fwrite(buffer, sizeof(char), 100, fp);
    fwrite(&prio, sizeof(int), 1, fp);
    fwrite(&ordem, sizeof(unsigned long), 1, fp);
    
    // 2. Histórico (Salva JUNTO com o paciente)
    HISTORICO *h = paciente_get_historico(p);
    int qtd_hist = historico_get_tamanho(h);
    fwrite(&qtd_hist, sizeof(int), 1, fp);
    
    // Percorre pilha (usando get_at que implementamos no historico.c)
    // Salva do mais antigo para o mais novo para facilitar reload, ou ordem pilha.
    // Vamos salvar na ordem natural (base->topo)
    for(int i=0; i<qtd_hist; i++) {
        PROCEDIMENTO *proc = historico_get_procedimento_at(h, i);
        procedimento_save(fp, proc);
    }
}

bool SAVE(ListaPacientes *lista, FilaTriagem *fila, void *u) {
    (void)u;
    
    // ARQUIVO 1: BASE DE DADOS (Pacientes + Históricos)
    FILE *fp = fopen("dados_hospital.bin", "wb");
    if(!fp) return false;
    
    unsigned long time = get_seqchegada();
    fwrite(&time, sizeof(unsigned long), 1, fp);
    
    int qtd_p = lista_get_tamanho(lista);
    fwrite(&qtd_p, sizeof(int), 1, fp);
    
    percorrer_arvore_para_save(lista, salvar_paciente_completo, fp);
    fclose(fp);
    
    // ARQUIVO 2: ESTADO DA FILA (Apenas IDs)
    fp = fopen("dados_fila.bin", "wb");
    if(fp) {
        int qtd_f = get_tamanho_fila(fila);
        fwrite(&qtd_f, sizeof(int), 1, fp);
        for(int i=0; i<qtd_f; i++) {
            Paciente *p = acessar_posicao_heap(fila, i);
            int id = get_id_paciente(p);
            fwrite(&id, sizeof(int), 1, fp);
        }
        fclose(fp);
    }
    printf("Sistema Salvo!\n");
    return true;
}

bool LOAD(ListaPacientes **lista, FilaTriagem **fila, void *u) {
    (void)u;
    FILE *fp = fopen("dados_hospital.bin", "rb");
    if(!fp) return false;
    
    unsigned long time;
    fread(&time, sizeof(unsigned long), 1, fp);
    set_seqchegada(time);
    
    int qtd_p;
    fread(&qtd_p, sizeof(int), 1, fp);
    
    for(int i=0; i<qtd_p; i++) {
        int id, prio, qtd_hist;
        char nome[100];
        unsigned long ordem;
        
        fread(&id, sizeof(int), 1, fp);
        fread(nome, sizeof(char), 100, fp);
        fread(&prio, sizeof(int), 1, fp);
        fread(&ordem, sizeof(unsigned long), 1, fp);
        
        Paciente *p = criar_paciente(id, nome, prio, ordem);
        
        // Ler Histórico
        fread(&qtd_hist, sizeof(int), 1, fp);
        HISTORICO *h = paciente_get_historico(p);
        for(int k=0; k<qtd_hist; k++) {
            PROCEDIMENTO *proc = procedimento_load(fp);
            historico_addprocedimento(h, proc);
        }
        inserir_paciente(*lista, p);
    }
    fclose(fp);
    
    // Carregar Fila
    fp = fopen("dados_fila.bin", "rb");
    if(fp) {
        int qtd_f;
        fread(&qtd_f, sizeof(int), 1, fp);
        for(int i=0; i<qtd_f; i++) {
            int id;
            fread(&id, sizeof(int), 1, fp);
            Paciente *p = buscar_paciente(*lista, id);
            if(p) inserir_paciente_fila(*fila, p);
        }
        fclose(fp);
    }
    
    return true;
}