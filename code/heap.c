#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

typedef int bool;

typedef struct
{
	int * A;
	int tAtual;
	int tMaximo;
}HEAP;

void inicializaHeap(HEAP *h, int tMax)
{
	h->A = (int*) malloc(sizeof(int)*(tMax+1));
	h->tAtual = 0;
	h->tMaximo = tMax;
}

void destruirHeap(HEAP * h)
{
	int tamanho = h->tMaximo;
	free(h->A);
	h->tMaximo=0;
	h->tAtual=0;
}
int pai(int i)
{
	return i/2;
}

int filhoEsquerda(int i)
{
	return 2*i;
}

int filhoDireita(int i)
{
	return 2*1 + 1;
}
bool inserirHeap(HEAP * h, int valor)
{
	int i;
	if (h->tAtual == h->tMaximo)
		return false;
	(h->tAtual)++;
	i=h->tAtual;
	h->A[i]=valor;

	return true;
}
void maxHeapify(HEAP * h, int i)
{
	int esq = filhoEsquerda(i);
	int dir= filhoDireita(i);
	int temp;
	int maior = i;
	if ((esq <= h->tAtual) && (h->A[esq]>h->A[i]))
		maior=esq;
	if ((dir <= h->tAtual) && (h->A[dir]>h->A[i]))
		maior=dir;
	if (maior!=i)
	{
		temp=h->A[i];
		h->A[i]=h->A[maior];
		h->A[maior]= temp;
		maxHeapify(h,maior);
	}
}
void buildMaxHeap(HEAP * h)
{
	int i;
	int tMetade = h->tAtual/2;
	for (i=tMetade;i>0;i--)
		maxHeapify(h,i);
}
void heapSort(HEAP * h)
{
	int t=h->tAtual;
	int i, temp;
	buildMaxHeap(h);
	for (i=t;i>1;i--)
	{
		temp = h->A[1];
     		h->A[1] = h->A[i];
     		h->A[i] = temp;
		(h->tAtual--);
		maxHeapify(h,1);
	}
}

void imprimir(HEAP h)
{
	int t= h.tAtual;
	int i;
	for (i=1;i<=t;i++)
	{
		printf("%d ",h.A[i]);
  		printf("\n");
	}
}

