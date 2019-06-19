#include <stdio.h>


int knapsack(int W, int *peso, int *b, int n)
{
	// tabela que será preenchida
	int V[n + 1][W + 1];

	// preenchendo a primeira linha e primeira coluna com 0
	for(int w = 0; w <= W; w++)
		V[0][w] = 0;
	for(int i = 1; i <= n; i++)
		V[i][0] = 0;

	for(int i = 1; i <= n; i++)
	{
		for(int w = 1; w <= W; w++)
		{	
			// elemento pode fazer parte da solução
			if(peso[i - 1] <= w)
			{
				//faz o max			
				if((b[i - 1] + V[i - 1][w - peso[i - 1]]) > V[i - 1][w])
					V[i][w] = b[i - 1] + V[i - 1][w - peso[i - 1]];
				else
					V[i][w] = V[i - 1][w];
			}
			else
				// se peso maior que capacidade
				V[i][w] = V[i - 1][w]; 
		}
	}

	// retorna o valor máximo colocado na mochila
	return V[n][W];
}

int main()
{
	int W=20, n=5;
	int b[] = {3, 5, 8, 4, 10};
	int peso[] = {2, 4, 5, 3, 9};

	int x = knapsack(W, peso, b, n);

	printf("Valor maximo: %d\n",x);

	return 0;
}
