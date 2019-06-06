#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main()
{
    lista l1;
    int posicao = 1;
    int valor = -111;


    printf("%p\n", l1);

    inicializa(&l1);

    printf("%p", l1);


    inserir(&l1,1,10); // 1a posicao de uma lista vazia
    inserir(&l1,2,20);
    inserir(&l1,1,30); // 1a posicao de uma lista nao-vazia
    inserir(&l1,4,40);
    inserir(&l1,7,50); // Nao vai inserir


    putchar('\n');
    if( vazia(l1))
      printf("A lista esta vazia neste momento.\n");
    else
     printf("A lista NAO esta vazia.\n");

    putchar('\n');

    exibeLista(l1);
/*
    if( cheia(l1))
      printf("A lista esta cheia.\n");
    else
     printf("A lista NAO esta cheia.\n");
*/
    putchar('\n');

    printf("Tamanho da Lista: %d", tamanho(l1));

    putchar('\n');
/*
    if( elemento(l1, posicao, &valor) )
        printf("conteudo armazenado na posicao %d eh: %d\n", posicao, valor);
    else
        printf("A posicao digitada eh invalida no momento.\n");

    valor = 10;
    posicao = busca(l1,valor);

    putchar('\n');
    printf("O valor pesquisado %d esta na posicao %d.\n", valor, posicao );

*/
    return 0;



}
