#include <stdio.h>
#include "funcao.h"
#define MAX 1000
//./main arquivoEntrada

int main(int argc, char** argv){
        FILE *p;
        int n,i,tamanho,op;
        int v[MAX];

        p = fopen(argv[1],"r");
	if (!p) perror("Erro ao tentar abrir o arquivo.\n");
        for(i=0; !feof(p) && i<MAX; i++)
	{
                fscanf(p,"%d",&n);
                v[i] = n;
        }
        fclose(p);
	tamanho=--i;
	printf("Escolha:\n1- Insertion\n2- Selection\n");
	scanf("%d",&op);
	switch(op)
	{
		case 1:
		insertionSort(v, tamanho);
		break;
		case 2:
		selectionSort(v, tamanho);
		break;
	}
	imprimeVetor(v, tamanho);
        return 0;
}
