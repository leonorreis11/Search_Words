//Funções necessárias para a estrutura de dados --> LISTA DUPLAMENTE LIGADA
#include <stdlib.h>
#include "FIFO_dupla.h"

void inicializar_lista(struct lista *pf) {
    pf->raiz = NULL;
    pf->pfim = NULL;
}

bool colocar_lista(struct lista *pf, const int numero, int prioridade) {
    struct no_fila *paux, *prox, *panterior;

    //Obter espaço para um novo nó
    paux = (struct no_fila *) malloc(sizeof(struct no_fila));
    if (paux == NULL)
        //não há espaço
        return false;


    paux->pos= numero;
    paux->prioridade = prioridade;
    paux->pseg = NULL;
    paux->pant = NULL;

    //Procurar a posição onde a mensagem deve ficar
    if (pf->raiz == NULL) {
        // fila vazia, é o primeiro nó
        pf->raiz = paux;
        pf->pfim = paux;
    } else {
        // fila contém dados
        if (pf->raiz->prioridade >= prioridade) {
            // inserir à entrada da lista
            paux->pseg = pf->raiz;
            pf->raiz->pant = paux;
            pf->raiz = paux;
        } else {
            // procurar posição de inserção
            panterior = pf->raiz;
            prox = pf->raiz->pseg;
            while (prox != NULL && prox->prioridade < prioridade) {
                panterior = prox;
                prox = prox->pseg;
            }
            if (prox == NULL) {
                // inserir à saída da lista
                panterior->pseg = paux;
                paux->pant = panterior;
                pf->pfim = paux;
            } else {
                // inserir a meio da lista
                panterior->pseg = paux;
                paux->pseg = prox;
                paux->pant=panterior;
                prox->pant=paux;
            }
        }
    }
    return true;
}

bool retirar_lista(struct lista *pf, int *pnumero) {
    struct no_fila *paux;

    if (pf->raiz == NULL) {
        // lista vazia
        return false;
    }

    if (pf->pfim->pant == NULL) {
        //só havia um dado na fila - vai ficar vazia
        *pnumero = pf->raiz->pos;
        free(pf->raiz);
        pf->raiz = NULL;
        pf->pfim = NULL;
    } else {
        // havia mais do que um dado na lista
        pf->pfim->pant->pseg = NULL;
        *pnumero = pf->pfim->pos;
        paux = pf->pfim;
        pf->pfim = pf->pfim->pant;
        free(paux);
    }
    return true;
}
