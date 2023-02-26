#include <stdio.h>
#include <string.h>

void ordem_no_ficheiro(FILE *pfich_e,FILE *pfich_s);

int main(void){
    char nome[50];
    char nome_saida[60]="pal_";
    char *ps;
    FILE * pfich_e, * pfich_s;

    printf("Nome do ficheiro: ");
    ps=fgets(nome,50,stdin);
    if(ps==NULL) {
        fprintf(stderr, "Erro na leitura do nome do ficheiro.\n");
        return 1;
    }

    int i=(int) strlen(nome);
    if(nome[i-1]=='\n') nome[i-1]=0;

    pfich_e=fopen(nome, "r");
    if(pfich_e == NULL){
        fprintf(stderr, "Ficheiro não encontrado!\n");
        return 1;
    }

    strcat(nome_saida, nome);
    pfich_s=fopen(nome_saida, "w");
    if(pfich_s == NULL){
        fprintf(stderr, "Não foi possível criar o ficheiro de saída\n");
        return 1;
    }

    ordem_no_ficheiro(pfich_e,pfich_s);

    if(fclose(pfich_e)!=0) fprintf(stderr, "Erro ao fechar o ficheiro de entrada!");
    if(fclose(pfich_s)!=0) fprintf(stderr, "Erro ao fechar o ficheiro de saída");
}


