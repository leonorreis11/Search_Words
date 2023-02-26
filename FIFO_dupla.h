//Funções necessárias para a estrutura de dados --> LISTA DUPLAMENTE LIGADA
#include <stdbool.h>

struct no_fila {
    int pos;
    int prioridade;
    struct no_fila * pseg;
    struct no_fila * pant;
};

struct lista {
    struct no_fila * raiz;
    struct no_fila * pfim;
};

bool colocar_lista(struct lista * pf, int numero, int prioridade);

bool retirar_lista(struct lista * pf, int *pnumero);

void inicializar_lista(struct lista *pf);

