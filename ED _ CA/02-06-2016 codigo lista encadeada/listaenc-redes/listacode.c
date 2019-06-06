#include "lista.h"
#include<stdio.h>
#include<stdlib.h>


void inicializa(lista *lst){
    *lst = NULL;
}



boolean vazia(lista lst){
    return lst == NULL;
}


int tamanho(lista lst){
    no* aux = lst; // lista aux;
    int contador = 0;

    while (aux != NULL){
        contador++;
        aux = aux->prox;
    }

    return contador;
}




boolean cheia(lista lst){
    return false;
}

boolean remover(lista *lst, int posicao, int *dado){
    return true;
}
/*

boolean elemento(lista lst, int posicao, int *dado){
    if( posicao < 1 || posicao > tamanho(lst) )
        return false;
    else {
        *dado = lst.elemento[posicao-1];
        return true;
    }
}

int busca(lista lst, int dado){
    int i;
    //for( i=0; i <= lst.posAtual; i++ )
    for( i=lst.posAtual; i >= 0; i-- )
        if( lst.elemento[i] == dado)
            return i+1;
    return 0;
}

*/
boolean inserir(lista *lst, int posicao, int dado){
	no *novo;
	lista aux;
	int contador;
	// insercao se a lista estiver vazia
	if (vazia(*lst)) {
		if (posicao != 1)
			return(0);
		if ( (novo = (no*) malloc(sizeof(no))) == NULL )
			return(0);
		novo->dado = dado;
		novo->prox = NULL;
		*lst = novo;
      return(1);
	}
	// insercao na primeira posicao em uma lista nao vazia
	if ( posicao == 1) {
		if ( (novo = (no*) malloc(sizeof(no))) == NULL )
			return(0);
		novo->dado = dado;
		novo->prox = *lst;
		*lst = novo;
      return(1);
	}
	// insercao apos a primeira posicao em lista nao vazia
	aux = *lst;
	contador = 1;
	while ( (contador < posicao-1)  && (aux != NULL)) {
		aux = aux->prox;
		contador++;
	}
	if ( aux == NULL )
		return 0;

  if ((novo = (no*) malloc(sizeof(no))) == NULL)
		return 0;
  novo->dado = dado;
  novo->prox = aux->prox;
  aux->prox  = novo;
  return 1;
}



void exibeLista(lista lst){
    putchar('[');
    lista aux = lst;

    while( aux != NULL ){
        printf("%d ", aux->dado);
        aux = aux->prox;
    }
    putchar(']');
}

