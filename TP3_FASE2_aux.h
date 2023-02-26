#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "arvbin9.h"
#define MAXPAL 100
#define MAXLINHA 5000

//responsável por extrair a palavra e a respetiva posição do ficheiro obtido na 1ªfase
char *ler_pares(char *nome, char *ano, int lim, FILE *fp);

/* Retira carateres ascii de controlo, bem como os espaços no início e fim
   "lim" inclui o espaço para o zero de terminação
   Devolve NULL se EOF, devolve o endereço recebido em caso contrário */
char *ler_nome(char *linha, int lim, FILE *fp);

/*imprime no ecrã todos os pares palavra;posição conforme guardados na árvore*/
void mostrar_tudo(struct arvore_binaria *pa);

/*função responsável por imprimir o contexto da palavra; devolve false se a palavra não existir no texto
 * Caso a palavra esteja contida na primeira frase do contexto, não é impressa a frase anterior porque não existe
 * Se o texto não terminar com um ponto final e a palavra estiver na última frase, o programa imprime a frase até encontrar EOF
 * Funcionamento: guarda numa string todos os carateres encontrados até ser encontrado um ponto final. Se a posição do ponto final for inferior
 à posição da palavra, significa que a palavra não está contida naquela frase e, portanto, a string é limpa e passa para a próxima frase.*/
void contexto(struct arvore_binaria *pa, struct pessoa alguem, char nome_fich[]);

/*descobre as palavras no texto que começam por uma letra ou uma gama de letras (exemplo: "p"--> pêra, passeio; "pa"--> passeio)
 *acentos, cedilhas, maiúsculas/minúsculas não são considerados, ou seja,se procurarmos todas as palavras que começam com letra a,
 são exibidas também todas as palavras que começam com a letra A,Á,à,á,ã...*/
bool procura_letras_iniciais(struct arvore_binaria *pa);
