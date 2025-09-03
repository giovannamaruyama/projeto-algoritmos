
#include <stdbool.h>
    typedef struct historico_ HISTORICO;

    HISTORICO* historico_criar(void);
    bool historico_cheio(HISTORICO *historico);
    bool historico_vazio(HISTORICO *historico);
    bool historico_addprocedimento(HISTORICO *historico, ITEM *procedimento);
    ITEM* historico_removeprocedimento(HISTORICO *historico);
    ITEM* historico_seeprocedimento(HISTORICO *historico);


    