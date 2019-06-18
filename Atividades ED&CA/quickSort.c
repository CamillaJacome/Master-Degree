#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int particiona(int *v, int inicio, int fim)
{
	int esq,dir,pivo,aux;
	esq=inicio;
	dir=final;
	pivo=v[inicio];
	while(esq<dir)
	{
		//avança posição da esquerda
		while(v[esq]<=pivo)
			esq++;
		//recua posição da direita
		while(v[dir]>pivo)
			dir--;
		//troca esq e dir
		if(esq<dir)
		{
			aux=v[esq];
			v[esq]=v[dir];
			v[dir]=aux;
		}

	}
	v[inicio]=v[dir];
	v[dir]=pivo;
	//ponto antes todos antes é menor e depois é maior
	return dir;
}
void quickSort(int *v, int inicio, int fim)
{
	int pivo;
	if (fim>inicio)
	{
		pivo=particiona(v,inicio,fim);
		quickSort(v,inicio,pivo-1);
		quickSort(v,pivo+1,fim);
	}
}

int main()
{
	return 0;
}