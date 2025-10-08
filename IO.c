// IO.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "IO.h"
#include "fila_triagem.h"
#include "paciente.h"
#include "lista_pacientes.h"
#include "historico.h"
#include "procedimentos.h"   // <- precisa para procedimento_save / procedimento_load

bool SAVE(ListaPacientes *lista, FilaTriagem *fila, HISTORICO *historico) {
    (void)historico; // suprime warning se não usar o parâmetro

    if (!lista || !fila) {
        printf("[ERRO] Lista ou fila inexistente.\n");
        return false;
    }

    // --- Salvar Lista de Pacientes com contagem ---
    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if (!fp_lista) return false;

    // conta nós
    int n = 0;
    for (NoLista *aux = lista->inicio; aux; aux = aux->proximo) n++;

    // grava contagem
    fwrite(&n, sizeof(int), 1, fp_lista);

    // grava (id + nome com 100 bytes fixos)
    for (NoLista *no = lista->inicio; no; no = no->proximo) {
        int id = get_id_paciente(no->paciente);
        const char *nome = get_nome_paciente(no->paciente);
        char nome_fix[100] = {0};
        if (nome) strncpy(nome_fix, nome, sizeof(nome_fix) - 1);

        fwrite(&id, sizeof(int), 1, fp_lista);
        fwrite(nome_fix, sizeof(nome_fix), 1, fp_lista);
    }
    fclose(fp_lista);
    printf("Lista: %d pacientes salvos.\n", n);

    // --- Salvar Fila de Triagem (IDs em ordem de atendimento) ---
    FILE *fp_fila = fopen("fila_pacientes.bin", "wb");
    if (!fp_fila) return false;

    int i = get_inicio_fila(fila);
    int qtd = get_tamanho_fila(fila);
    int count = 0;

    printf("[Salvando %d pacientes na fila.\n", qtd);
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

    // --- Salvar o Histórico de Todos os Pacientes ---
    FILE *fp_historico = fopen("historicos.bin", "wb");
    if (!fp_historico) return false;

    for (NoLista *no = lista->inicio; no; no = no->proximo) {
        HISTORICO *h = paciente_get_historico(no->paciente);
        if (!h) continue;

        int tam = historico_get_tamanho(h);
        if (tam > 0) { // só salva se tiver procedimentos
            int id = historico_get_paciente_id(h);
            const char *nome = historico_get_paciente_nome(h);

            fwrite(&id, sizeof(int), 1, fp_historico);
            fwrite(nome, sizeof(char), 100, fp_historico);
            fwrite(&tam, sizeof(int), 1, fp_historico);

            for (int k = 0; k < tam; k++) {
                PROCEDIMENTO *p = historico_get_procedimento_at(h, k);
                if (!procedimento_save(fp_historico, p)) {
                    fclose(fp_historico);
                    return false;
                }
            }
        }
    }
    fclose(fp_historico);

    return true;
}

bool LOAD(ListaPacientes **lista_ptr, FilaTriagem **fila_ptr, HISTORICO **historico) {
    (void)historico; // não usamos diretamente aqui

    ListaPacientes *lista = *lista_ptr;
    FilaTriagem *fila = *fila_ptr;
    if (!lista || !fila) return false;

    // --- Carregar Lista com contagem ---
    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if (!fp_lista) return false;

    int n = 0;
    if (fread(&n, sizeof(int), 1, fp_lista) != 1) { fclose(fp_lista); return false; }

    int lidos = 0;
    for (int i = 0; i < n; i++) {
        int id;
        char nome[100];

        if (fread(&id, sizeof(int), 1, fp_lista) != 1 ||
            fread(nome, sizeof(nome), 1, fp_lista) != 1) {
            fclose(fp_lista);
            return false;
        }

        Paciente *paciente = criar_paciente(id, nome);
        if (!paciente) { fclose(fp_lista); return false; }

        inserir_paciente(lista, paciente);
        lidos++;
    }
    fclose(fp_lista);
    printf("Lista: %d/%d pacientes carregados.\n", lidos, n);

    // --- Carregar e Restaurar Históricos ---
    FILE *fp_historico = fopen("historicos.bin", "rb");
    if (fp_historico) {
        int paciente_id, tamanho;
        char paciente_nome[100];

        while (fread(&paciente_id, sizeof(int), 1, fp_historico) == 1 &&
               fread(paciente_nome, sizeof(char), 100, fp_historico) == 1 &&
               fread(&tamanho, sizeof(int), 1, fp_historico) == 1) {

            HISTORICO *h = historico_criar(paciente_id, paciente_nome);
            if (!h) { fclose(fp_historico); return false; }

            Paciente *paciente_na_lista = buscar_paciente_por_id(lista, paciente_id);
            if (paciente_na_lista) {
                paciente_set_historico(paciente_na_lista, h);
            }

            for (int k = 0; k < tamanho; k++) {
                PROCEDIMENTO *p = procedimento_load(fp_historico);
                if (!p) { fclose(fp_historico); return false; }
                historico_addprocedimento(h, p);
            }
        }
        fclose(fp_historico);
    }

    // --- Carregar Fila de Triagem ---
    FILE *fp_fila = fopen("fila_pacientes.bin", "rb");
    if (fp_fila) {
        int chave;
        int pacientes_carregados = 0;

        while (fread(&chave, sizeof(int), 1, fp_fila) == 1) {
            Paciente *paciente_completo = buscar_paciente_por_id(lista, chave);
            if (paciente_completo) {
                inserir_paciente_fila(fila, paciente_completo);
                pacientes_carregados++;
            } else {
                printf("AVISO: ID %d da fila nao encontrado na Lista de Pacientes.\n", chave);
            }
        }
        fclose(fp_fila);
        printf("Fila carregada: %d pacientes encontrados no arquivo.\n", pacientes_carregados);
    } else {
        printf("Arquivo fila_pacientes.bin nao encontrado. Fila vazia.\n");
    }

    return true;
}
