//Funções necessárias para a estrutura de dados --> ÁRVORE BINÁRIA
#include <stdlib.h>
#include <string.h>
#include "arvbin9.h"

void inicializar_arvore(struct arvore_binaria * pa) {
    pa->raiz = NULL;
}

static struct no *addtree(struct no *, struct no *);

bool colocar(struct arvore_binaria * pa, struct pessoa alguem) {
    struct no *p;
    p = (struct no *) malloc(sizeof(struct no)); // make a new node
    if (p == NULL)
        return false;
    p->gente = alguem;
    p->left = p->right = NULL;
    pa->raiz = addtree(pa->raiz, p);
    return true;
}

struct no *addtree(struct no *pr, struct no *p) {
    int cond;
    char nome1[MAXPAL + 1],nome2[MAXPAL + 1];
    //1ªvez que a palavra aparece, logo a lista associada é inicializada
    if (pr == NULL) {
        pr = p;
        inicializar_lista(&pr->gente.fifo);
        colocar_lista(&pr->gente.fifo, p->gente.pos, 1);
    } else {
        strtobase_u8(nome1,p->gente.str);
        strtobase_u8(nome2,pr->gente.str);
        if ((cond = strcmp(nome1,nome2)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}

struct no *find(struct no *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    char nome1[MAXPAL + 1],nome2[MAXPAL + 1];
    strtobase_u8(nome1,pr->gente.str);
    strtobase_u8(nome2,pn);
    if ((cond = strcmp(nome1, nome2)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}

struct no *find_next(struct no *pr, const char *anterior, struct no *candidato);

bool seguinte(struct arvore_binaria * pa, struct pessoa * ppessoa) {
//struct pessoa seguinte(int *pvazio, const char str[MAXNOME + 1]) {
    struct no *p;

    p = find_next(pa->raiz, ppessoa->str, NULL);
    if (p == NULL) {
        return false;
    }
    *ppessoa = p->gente;
    return true;
}

// devolve NULL se não há seguinte
struct no *find_next(struct no *pr, const char *anterior, struct no *candidato) {
    if (pr == NULL) return candidato;
    char nome1[MAXPAL + 1],nome2[MAXPAL + 1];
    strtobase_u8(nome1,anterior);
    strtobase_u8(nome2,pr->gente.str);
    if (strcmp(nome1,nome2) >= 0)
        return find_next(pr->right, anterior, candidato);
    else
        return find_next(pr->left, anterior, pr);
}

