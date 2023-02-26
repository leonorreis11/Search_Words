//ficheiro fonte - funções auxiliares ao programa principal
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
//tamanho da maior palavra
#define MAX_PAL 100
#include "lib-utf8.h"


static char acentuadas[][8] =
        {"á", "Á", "à", "À", "ã", "Ã", "â", "Â", "ä", "Ä", "ç", "Ç",
         "é", "É", "è", "È", "ê", "Ê", "í", "Í", "ì", "Ì", "î", "Î",
         "ó", "Ó", "ò", "Ò", "õ", "Õ", "ô", "Ô", "ö", "Ö", "ú", "Ú",
         "ù", "Ù", "û", "Û", "\0"};

bool isacentuada(char *s) {
    for (int j = 0; acentuadas[j][0] != 0; j++) {
        if (strncmp(&acentuadas[j][0], s, 2) == 0)
            return 1;
    }
    return 0;
}

/*procura letras, números e hífen. Se não for um destes, é um separador.
 * Se o carater não for uma letra de um byte ou um número, é guardado juntamente com o carater seguinte numa cadeia aux de 2 bytes e testamos se é
 * uma letra acentuada. Se for uma letra acentuada adicionamos à palavra que está a ser construída, caso contrário é um separador.*/
void ordem_no_ficheiro(FILE *pfich_e, FILE *pfich_s) {
    int c, c1, pos = 0, dist=0;
    char str_aux[3];
    str_aux[2] = 0;
    char word[MAX_PAL];
    word[0]=0;
    int w = 0, control = 0, k=0;

    while ( (c = fgetc(pfich_e)) != EOF) {
        pos++;
        if ( (!isalnum(c) && c!='-') || k==1){
            str_aux[k] = (char) c;
            if (k == 1) {
                // é uma letra acentuada
                if (isacentuada(str_aux)) {
                    strcat(word, str_aux);
                    //primeira letra
                    if(w==0) dist=pos;
                    w = w + 2;
                    word[w] = 0;
                    control = 1;
                    k=0;
                }else {
                    //imprimir palavra
                    if (control == 1) {
                        if(strlen_u8(word)>2)
                            c1 = fprintf(pfich_s, "%s;%d\n", word, dist-1);
                        w = 0;
                        word[0] = 0;
                    }
                    control = 0;
                    str_aux[0]=str_aux[1];
                    k=1;
                }
            }
            else k++;
        }
        //é um número ou uma letra não acentuada
        if (isalnum(c) || c=='-') {
            //primeira letra
            if(w==0) dist=pos;
            word[w] = (char) c;
            w++;
            word[w] = 0;
            control = 1;
            k=0;
            str_aux[0]=0;
        }
        if(c1==EOF)
            fprintf(stderr,"Não foi possível escrever no ficheiro de saída.");
    }

    //imprimir a última palavra se não existir + de um separador
    if(control==1){
        if(strlen_u8(word)>2)
            c1 = fprintf(pfich_s, "%s;%d\n", word, dist-1);
    }
    if(c1==EOF)
        fprintf(stderr,"Não foi possível escrever no ficheiro de saída.");
}