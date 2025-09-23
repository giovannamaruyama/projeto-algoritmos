
#include <stdbool.h>
    typedef struct historico_ HISTORICO;

    HISTORICO* historico_criar(void);
    bool historico_cheio(HISTORICO *historico);
    bool historico_vazio(HISTORICO *historico);
    bool historico_addprocedimento(HISTORICO *historico, ITEM *procedimento);
    ITEM* historico_removeprocedimento(HISTORICO *historico);
    ITEM* historico_consultar_ultimo(HISTORICO *historico);
    void historico_imprimir(HISTORICO *historico);
    void historico_apagar(HISTORICO **historico);


    
