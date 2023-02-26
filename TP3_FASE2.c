//Ficheiro fonte com programa principal
#include "TP3_FASE2_aux.h"

int main(void) {
    struct pessoa alguem;
    char nome_fich[MAXPAL + 1];
    FILE *fich = NULL;
    char pos_str[10];
    char nome_saida[60]="pal_";

    setlocale(LC_ALL, "pt_PT.utf8");

    struct arvore_binaria arvore;
    inicializar_arvore(&arvore);

    // pedir str do ficheiro que contém os dados
    while (fich == NULL) {
        printf("Nome do ficheiro de texto original: ");
        if (ler_nome(nome_fich, MAXPAL + 1, stdin) == NULL)
            return 0;
        //abrir o ficheiro palavra;posição criado na primeira fase
        strcat(nome_saida, nome_fich);
        fich = fopen(nome_saida, "r");
        if (fich == NULL)
            fprintf(stderr, "Ficheiro não existe\n");
    }


    // inserir pares {str,pos} na árvore
    struct no *pr;
    while (ler_pares(alguem.str, pos_str, MAXPAL + 1, fich) != NULL) {
        alguem.pos = (int) strtol(pos_str, NULL, 0);

        //1ªvez que a palavra aparece - colocada na árvore;
        if( (pr=find(arvore.raiz,alguem.str))==NULL) {
            if (!colocar(&arvore, alguem) != 0) {
                fprintf(stderr, "Não há espaço para inserir o nó na árvore!\n");
                break;
            }
        }else //não é necessário colocar na árvore porque já apareceu; adicionar a pos à lista associada
            colocar_lista(&pr->gente.fifo, alguem.pos, 1);
    }

    int escolha;
    while (1) {
        printf("\n"
               "  0 - Sair\n"
               "  1 - Mostrar todas as palavras\n"
               "  2 - Contexto de uma palavra\n"
               "  3 - Inicial da palavra\n"
               "Escolha: ");
        escolha = ' ';
        while (isspace(escolha))
            escolha = getchar();
        while (getchar() != '\n'); //limpar o resto da linha
        if (escolha == '0') return 0;
        if (escolha == '1') mostrar_tudo(&arvore);
        else if (escolha == '2') contexto(&arvore, alguem, nome_fich);
        else if (escolha == '3') procura_letras_iniciais(&arvore);
        else printf("Escolha inválida\n");
    }
}
