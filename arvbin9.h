//Funções necessárias para a estrutura de dados --> ÁRVORE BINÁRIA

#define MAXPAL 100
#define MAXLINHA 5000
#include "lib-utf8.h"
#include "FIFO_dupla.h"

struct pessoa {
    char str[MAXPAL + 1];
    int pos;
    struct lista fifo;
};

struct no {
    struct pessoa gente;
    struct no *left;
    struct no *right;
};

struct arvore_binaria {
    struct no * raiz;
};

// deve ser sempre chamada antes da árvore ser usada
void inicializar_arvore(struct arvore_binaria * pa);

// coloca uma pessoa na árvore. Devolve true se tudo correu bem, devolve false se não havia espaço disponível
bool colocar(struct arvore_binaria * pa, struct pessoa alguem);

// obter o ano de nascimento de alguém. Ignora diferença entre maiúsculas e minúsculas.
// Devolve false se a pessoa não foi encontrada
bool consultar(struct arvore_binaria * pa, char nome[], char nome_fich[]);

// Obter os dados da próxima pessoa (por ordem alfabética) presente na árvore, a seguir ao str indicado
// Se ppessoa.str == "\0", devolve a primeira pessoa (por ordem alfabética) presente na árvore
// Se não há ninguém na árvore com um str a seguir ao fornecido, devolve false
// Se há uma pessoa na árvore que satisfaz o pedido, devolve true, e coloca os dados em *ppessoa
bool seguinte(struct arvore_binaria * pa, struct pessoa * ppessoa);

//devolve NULL caso a palavra procurada não exista; caso contrário
//devolve um ponteiro para o nó da árvore onde a palavra se encontra
struct no *find(struct no *pr, char *pn);



