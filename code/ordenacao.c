#include <stdio.h>
#define MAX 1000
// gcc ordenacao.c arquivoEntrada
void insertionSort(int v[], int tamanho);
void imprimeVetor(int v[], int tamanho);
void selectionSort (int v[],int tamanho);

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
void insertionSort(int v[], int tamanho)
{
   int i,j,pivo;
   for (i = 1; i<tamanho; i++)
   {
       pivo = v[i];
       j = i-1;

       while (j >= 0 && v[j] > pivo)
       {
           v[j+1] = v[j];
           j = j-1;
       }
       v[j+1] = pivo;
   }
}

void selectionSort (int v[],int tamanho)
{
	int i, j, min, temp;

	for (i = 0; i < (tamanho - 1); i++)
 	{
		min = i;
                for (j = i+1; j < tamanho; j++)
		{
			if (v[j] < v[min])
			{
			min = j;
      			}
  	 	 }

		if (i != min)
		{
      		temp = v[i];
     		v[i] = v[min];
      		v[min] = temp;
    		}
  	}
}

void imprimeVetor (int v[], int tamanho)
{
        int i;
	puts("Vetor ordenado:");
        for(i=0;i<tamanho;i++)
        {
                printf("%d ", v[i]);

        }
	puts(" ");
}


