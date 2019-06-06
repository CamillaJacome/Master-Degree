#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void inicializa(lista *lst){
    *lst = NULL;
}



bool vazia(lista lst){
    return lst == NULL;
}


int tamanho(lista lst){
    tNo* aux = lst; // lista aux;
    int contador = 0;

    while (aux != NULL){
        contador++;
        aux = aux->prox;
    }

    return contador;
}

int busca(lista lst, int indice){
    int i;
    for( i=0; ; i++ ){
        if( lst->indice == indice){
            return i;
        }
        lst = lst->prox;
    }
    return 0;
}

bool inserir(lista *lst, int posicao, int indice){
	tNo *novo;
	lista aux;
	int contador;
	// insercao se a lista estiver vazia
	if (vazia(*lst)) {
		if (posicao != 0)
			return(0);
		if ( (novo = (tNo*) malloc(sizeof(tNo))) == NULL )
			return(0);
		novo->indice = indice;
		novo->prox = NULL;
		*lst = novo;
        return(1);
	}
	// insercao na primeira posicao em uma lista nao vazia
	if ( posicao == 0) {
		if ( (novo = (tNo*) malloc(sizeof(tNo))) == NULL )
			return(0);
		novo->indice = indice;
		novo->prox = *lst;
		*lst = novo;
        return(1);
	}
	// insercao apos a primeira posicao em lista nao vazia
	aux = *lst;
	contador = 0;
	while ( (contador < posicao-1)  && (aux != NULL)) {
		aux = aux->prox;
		contador++;
	}
	if ( aux == NULL ){
		return 0;
    }

  if ((novo = (tNo*) malloc(sizeof(tNo))) == NULL)
		return 0;
  novo->indice = indice;
  novo->prox = aux->prox;
  aux->prox  = novo;
  return 1;
}



void exibeLista(lista lst){
    putchar('[');
    lista aux = lst;

    while( aux != NULL ){
        printf("%d ", aux->indice);
        aux = aux->prox;
    }
    putchar(']');
}

bool deletaLista(lista *lst){
    lista aux;

    aux = *lst;

    while(!vazia(*lst)){
        printf("Entra aqui");
        *lst = aux->prox;
        free(aux);
        return 0;
    }

    return 1;
}