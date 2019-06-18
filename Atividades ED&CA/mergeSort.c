#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void merge(int *v, int inicio, int meio, int fim);

void mergeSort(int *v, int inicio, int fim)
{
	int meio;

	if (inicio < fim)
	{
		meio = floor((inicio+meio)/2);
		//merge para a primeira metade
		mergeSort(v,inicio,meio);
		//merge para a segunda metade
		mergeSort(v,meio+1,fim);
		//combinar duas metades de forma ordenada
		merge(v,inicio,meio,fim);
	}
}
void merge(int *v, int inicio, int meio, int fim)
{
	int *temp,v1, v2,tamanho,j,k;
	int fim1=0, fim2=0;
	tamanho=fim-inicio+1;
	//vetores para combinar
 c	v1=inicio;
	v2=meio+1;
	temp=(int *) malloc(tamanho*sizeof(int));

	if (temp!=NULL)
	{
		for (int i=0;i<tamanho;i++)
		{
			if(!fim1 && !fim2)
			{
				//para cada posição verifica o menor elemento	
				if(v[v1]<v[v2])
					temp[i]=v[v1++];
				else
					temp[i]=v[v2++];

				//se chegar ao final do vetor
				if(v1>meio)
					fim1=1;
				if(v2>fim)
					fim2=1;
			//copia o que sobrou
			}else{
				if(!fim1)
					temp[i]=v[v1++];
				else
					temp[i]=v[v2++];
			}	
		}
	}
	//copia o vetor auxiliar para o original
	for(j=0,k=inicio;j<tamanho;j++,k++)
	{
		v[k]=temp[j];
		printf("%d\n",temp[j]);
	}
	free(temp);
}
int main ()
{
	int vetor[]={1,10,35,2,6,7,9,15};

	mergeSort(vetor,0,7);

	return 0;
}