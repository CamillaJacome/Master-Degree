#include <stdio.h>

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


