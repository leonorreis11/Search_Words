//Funções auxiliares ao programa principal
#include "TP3_FASE2_aux.h"

char *ler_nome(char *linha, int lim, FILE *fp) {
    if (fgets_u8(linha, lim, fp) == NULL)
        return NULL;
    bool inicio = true;
    int i = 0, j = 0;
    while (linha[i] != 0) {
        if (inicio && isspace((int) linha[i]))
            i++;
        else {
            inicio = false;
            if (iscntrl((int) linha[i])) {
                i++;
            } else {
                linha[j++] = linha[i++];
            }
        }
    }
    if (i > 0) {
        if (linha[i - 1] != '\n') {
            //limpar o resto da linha
            int c = fgetc(fp);
            while ((c != EOF) && (c != '\n'))
                c = fgetc(fp);
        }
        linha[j] = 0;
    }
    return linha;
}


void mostrar_tudo(struct arvore_binaria *pa) {
    struct pessoa alguem;
    alguem.str[0] = 0;
    while (seguinte(pa, &alguem)) {
        printf("%6s ", alguem.str);
        struct no_fila *aux = alguem.fifo.raiz;
        while (aux!= NULL) {
            printf(" %3d ", aux->pos);
            aux = aux->pseg;
        }
        printf("\n");
    }
}

bool procura_letras_iniciais(struct arvore_binaria *pa) {
    struct pessoa alguem;
    char nome1[MAXPAL + 1], nome2[MAXPAL + 1];
    alguem.str[0] = 0;
    int control=0;

    //pedir a letra ao utilizador
    printf("Letra(s) iniciais da palavra? ");
    char str[MAXPAL];
    ler_nome(str, MAXPAL, stdin);
    strtobase_u8(nome2, str);
    //nºletras dadas pelo utilizador
    int tam=(int)strlen(nome2);
    int i=0;

    while (seguinte(pa, &alguem)) {
        strtobase_u8(nome1, alguem.str);
        while(nome1[i]==nome2[i] && i<tam) i++;

        if (i==tam) {
            control=1;
            struct no_fila *aux = alguem.fifo.raiz;
            struct no_fila *ant;
            //descobrir o último nó da lista
            while (aux != NULL) {
                ant=aux;
                aux = aux->pseg;
            }
            aux=ant;
            while (aux != NULL) {
                printf("%s;%d\n", alguem.str, aux->pos);
                aux = aux->pant;
            }
        }
        i=0;
    }
    if(!control) printf("Não existe nenhuma palavra no texto que comece com a(s) letra(s) %s!\n", str);
    return 1;
}

void contexto(struct arvore_binaria *pa, struct pessoa alguem, char nome_fich[]) {
    printf("Nome da palavra a procurar? ");
    ler_nome(alguem.str, MAXPAL + 1, stdin);
    if (!consultar(pa, alguem.str,nome_fich))
        printf("Não existe\n");
}

bool consultar(struct arvore_binaria * pa, char *nome, char *nome_fich) {
    FILE *fich = NULL;
    struct no *p;
    int pos, c,i=0,dist=0,control=1,j=0;

    //encontrar o indice na arvore
    p = find(pa->raiz, nome);
    if (p == NULL)
        return false;

    struct no_fila *aux = p->gente.fifo.raiz;
    char linha[MAXLINHA+1], linha_ant[MAXLINHA+1];
    while(aux!= NULL){
        //abrir o texto
        fich = fopen(nome_fich, "r");
        if (fich == NULL) fprintf(stderr, "Ficheiro não existe\n");

        pos=aux->pos;
        while ( (c = fgetc(fich)) != EOF && control){
            dist++;
            if(c!='.'){
                linha[i]=(char) c;
                i++;
                //se o tamanho máximo da linha (MAXLINHA) for atingido
                if(i>MAXLINHA){
                    printf("Linha demasiado comprida.");
                    return false;
                }
            }
            else{
                //encontramos a linha que contém a palavra
                if(dist>=pos)
                    control = 0;
                else {
                    //guardar a linha anterior
                    linha[i]=0;
                    for(j=0; linha[j]!=0;j++)
                        linha_ant[j]=linha[j];
                    linha_ant[j]=0;
                    //limpar a linha, esta linha não contém a palavra
                    i = 0;
                }
            }
        }
        linha[i]=0;

        //se a palavra que procuramos estiver na 1ªlinha, ou seja, não existem linhas antes
        if(j==0) printf("Posição da palavra: %d Contexto: %s.\n", pos,linha);
        else printf("Posição da palavra: %d Contexto: %s. %s.\n", pos, linha_ant,linha);

        //recomeçar outra linha
        i=0;
        j=0;
        dist=0;
        control=1;
        aux = aux->pseg;
        //fechar o texto
        if(fclose(fich)!=0) fprintf(stderr, "Erro ao fechar o ficheiro de entrada!");
    }
    return true;
}


char *ler_pares(char *nome, char *ano, int lim, FILE *fp) {
    char linha[lim];
    if (fgets_u8(linha, lim, fp) == NULL)
        return NULL;
    bool inicio = false;
    int i = 0, k = 0;
    while (linha[i] != 0) {
        if (isspace((int) linha[i]) || iscntrl((int) linha[i]))
            i++;
        else if (linha[i] == ';') {
            inicio = true;
            i++;
            nome[k] = 0;
            k = 0;
        } else if (inicio == false) {
            nome[k++] = linha[i++];
        } else {
            ano[k++] = linha[i++];
        }
    }
    if (i > 0) {
        if (linha[i - 1] != '\n') {
            //limpar o resto da linha
            int c = fgetc(fp);
            while ((c != EOF) && (c != '\n'))
                c = fgetc(fp);
        }
        ano[k] = 0;
    }
    return nome;
}
