#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "lista.h"

#define INF 100000000


//Recupera a dimensão das entradas
int tamanhoEntrada(char files[]){
	FILE *arq;
	arq = fopen(files, "rt");
	int count=0;
	int tam=0;
	char linha[100];
	char *palavra = NULL;
	if (arq == NULL)
	{
    	printf("Problemas na CRIACAO do arquivo\n");
    	return -1;
	}

	while (!feof(arq)){
		fgets(linha, sizeof linha, arq);
		count++;
		if(count==1){	//Ignora a primeira linha
			continue;
		}

		palavra = strtok(linha, " ");

		while(palavra != NULL){
			if(!strcmp(palavra, "DIMENSION:")){
				while(palavra != NULL){
					tam = atoi(palavra);	//Recupera o valor da dimensão
					palavra = strtok(NULL, " ");
				}
				return tam;		//Retorna a dimensão da entrada
			}

			palavra = strtok(NULL, " ");
		}
	}

	return tam;
}

//Função para ler instâncias de teste
void lerInstanciaP(char files[], int tam, int** v){
	FILE *arq;
	arq = fopen(files, "rt");
	int count=0;
	int i=0, j=0;
	char linha[1000];
	char *palavra = NULL;
	if (arq == NULL)
	{
    	printf("Problemas na CRIACAO do arquivo\n");
    	return;
	}

	while (!feof(arq)){
		fgets(linha, sizeof linha, arq);

		//Ignora as 3 primeiras linhas
		if(count == 0 || count == 1 || count == 2){
			count++;
			continue;
		}
		palavra = strtok(linha, " ");
		if(!strcmp(palavra, "\n")){
			palavra = strtok(NULL, " ");
			continue;
		}
		v[i][j] = atoi(palavra);

		while(palavra != NULL){
			//Ignora o \n e pula para a próxima linha
			if(!strcmp(palavra, "\n")){
				palavra = strtok(NULL, " ");
				break;
			}

			j++;
			palavra = strtok(NULL, " ");
			v[i][j] = atoi(palavra);
			//printf("v[%d][%d]: %d ", i, j, v[i][j]);
		}
		//printf("\n\n");
		j=0;
		i++;
	}
}

//Função para ler instâncias a serem utilizadas no projeto final
void lerInstanciaG(char files[], int tam, int** v){
	FILE *arq;
	arq = fopen(files, "rt");
	int count=0;
	int i=0, j=0;
	char linha[1000];
	int coord[tam][2];
	char *palavra = NULL;
	if (arq == NULL)
	{
    	printf("Problemas na CRIACAO do arquivo\n");
    	return;
	}

	while (!feof(arq)){
		fgets(linha, sizeof linha, arq);

		//Ignora as 3 primeiras linhas
		if(count == 0 || count == 1 || count == 2){
			count++;
			continue;
		}

		palavra = strtok(linha, " ");
		if(!strcmp(palavra, "EOF")){		//Ignora última linha
			break;
		}

		while(palavra != NULL){

			//Ignora o \n e pula para a próxima linha
			if(!strcmp(palavra, "\n")){
				palavra = strtok(NULL, " ");
				break;
			}

			palavra = strtok(NULL, " ");
			coord[i][j] = atoi(palavra);
			j++;
		}
		j=0;
		i++;
	}

	int aux;
	for(i=0; i<tam; i++){
		for (j=i; j<tam; j++){
			if(i!=j){
				aux = (int)(sqrt(pow((coord[j][0]-coord[i][0]), 2) + pow((coord[j][1]-coord[i][1]), 2)));
				v[i][j] = aux;
				v[j][i] = aux;	
			}
			else
				v[i][j] = 0;
		}

	}
	fclose(arq);

}

int funcAvaliacao(int** v, lista lst){
	int profit=0;
	tNo *aux = lst;

	for(int i=0; i<(tamanho(lst)-1); i++){
		profit = profit + v[aux->indice][aux->prox->indice];
		aux = aux->prox;
	}

	profit = profit + v[aux->indice][lst->indice];			//Acrescenta a aresta do último até o primeiro
	//printf("Profit: %d", profit);
	return profit;
}

int funcAvaliacaoV(int** v, int tam, int* solucao){
	int profit=0, i;

	for(i=0; i<(tam-1); i++){
		profit = profit + v[solucao[i]][solucao[i+1]];
	}

	profit = profit + v[solucao[i]][solucao[0]];			//Acrescenta a aresta do último até o primeiro
	//printf("Profit: %d\n", profit);
	return profit;
}

void ConstrucaoMaisProximo(int** v, int tam, int* solucao){

	bool vMark[tam];
	int count = 0;
	int pos=0;
	int menor = INF;
	int i;
	int aux;

	for (i=0;i<tam;i++){
		vMark[i]=false;
	}

	vMark[0]=true;
	solucao[0]=0;
	count++;

	while(count<tam){
		for(i=1; i<tam; i++){
			if(vMark[i] == false){
				if(v[pos][i]<menor){
					menor = v[pos][i];
					aux = i;
				}
			}
		}
		pos = aux;
		solucao[count] = aux;
		vMark[aux] = true;
		count++;
		menor = INF;
	}

	for (int i=0; i<tam; i++){
		printf("%d ", solucao[i]);
	}

}

void melhorInsercao(int** v, int tam, int* solucao){

	bool vMark[tam];
	int count = 0;
	int pos=0;
	int maior = 0, menor = INF;
	int i;
	int aux;
	lista noAux;
	lista noAlt;
	lista lst;
	int profit=0;
	int pAux=0;

	for(int k=0; k<tam; k++){
		vMark[k] = false;
	}

	inicializa(&lst);

	//Começa sempre com o índice 0
	inserir(&lst, count, 0);
	vMark[0]=true;
	count++;

	//exibeLista(lst);
	//printf("\n");

	//Pega o índice mais distante do índice 0
	for(i=1; i<tam; i++){
		if(vMark[i] == false){
			if(v[pos][i]>maior){
				maior = v[pos][i];
				aux = i;
			}
		}
	}

	//Insere índice mais distante
	inserir(&lst, count, aux);
	count++;
	vMark[aux] = true;
	//exibeLista(lst);
	//printf("\n");


	profit = funcAvaliacao(v, lst);
	pAux = profit;

	int j;

	for(j=0; j<tam; j++){
		if(vMark[j]==true){
			continue;
		}

		pAux = profit + v[lst->indice][j] + v[j][lst->prox->indice] - v[lst->indice][lst->prox->indice];
		
		//menor recebe o menor profit entre os "candidatos" e aux recebe o índice do melhor profit
		if(pAux < menor){
			menor = pAux;
			aux = j;
		}
	}

	//Insere o menor profit entre os dois primeiros nós
	inserir(&lst, (busca(lst, lst->prox->indice)), aux);
	vMark[aux] = true;
	profit = funcAvaliacao(v, lst);		//Atualiza profit
	count++;
	//exibeLista(lst);
	//printf("\n");

	while(tamanho(lst)<tam){
		noAlt = lst;
		noAux = lst;
		menor = INF;
		while(noAux != NULL){
			for(j=0; j<tam; j++){
				if(vMark[j]==true){
					continue;
				}
				if(noAux->prox != NULL){
					pAux = profit + v[noAux->indice][j] + v[j][noAux->prox->indice] - v[noAux->indice][noAux->prox->indice];
				}
				else{
					pAux = profit + v[noAux->indice][j] + v[j][0] - v[noAux->indice][0];
				}
				
				//menor recebe o melhor profit entre os "candidatos" e aux recebe o índice do melhor profit
				if(pAux < menor){
					menor = pAux;
					aux = j;
					noAlt = noAux;
				}
			}

			
			noAux = noAux->prox;
		}
		inserir(&lst, (busca(lst, noAlt->indice)+1), aux);
		vMark[aux] = true;
		profit = funcAvaliacao(v, lst);		//Atualiza profit
		count++;
		//exibeLista(lst);
		//printf("\n");
	}
	//printf("\nProfit inicial: %d\n", profit);

	//printf("\nLista Final:\n");
	//exibeLista(lst);
	//printf("\n");

	profit = funcAvaliacao(v, lst);

	for(int k=0; k<tam; k++){
		solucao[k] = lst->indice;
		lst = lst->prox;
	}
	
}

//Não está pronta ainda
void swap2(int** v, int tam, int* solucao){
	int rand1, rand2;
	int profit = 0;
	int vAux, vAux2, pAux;
	int count=0;

	profit = funcAvaliacaoV(v, tam, solucao);
	pAux = profit;

	printf("Profit incial: %d ", profit);
	srand(time(NULL));

	while(pAux >= profit){
		rand1 = rand() % tam;
		rand2 = rand() % tam;
		//printf("%d, %d ", rand1, rand2);
		//printf("%d, %d ", rand1, rand2);
		if (!(rand1 == rand2 || rand1 == (rand2+1) || rand2 == (rand1+1))){
			if(rand1 == (tam-1) || rand1 == 0){
				continue;
				pAux = profit - v[solucao[rand1]][solucao[0]] - v[solucao[rand2]][solucao[rand2+1]] 
				+ v[solucao[rand1]][solucao[rand2]] + v[solucao[0]][solucao[rand2+1]];
			}
			else if(rand2 == (tam-1) || rand2 == 0){
				continue;
				pAux = profit - v[solucao[rand1]][solucao[rand1+1]] - v[solucao[rand2]][solucao[0]] 
				+ v[solucao[rand1]][solucao[rand2]] + v[solucao[rand1+1]][solucao[0]];
			}
			else{
				pAux = profit - v[solucao[rand1-1]][solucao[rand1]] - v[solucao[rand1]][solucao[rand1+1]] - v[solucao[rand2-1]][solucao[rand2]] - v[solucao[rand2]][solucao[rand2+1]]
				+ v[solucao[rand1-1]][solucao[rand2]] + v[solucao[rand2]][solucao[rand1+1]] + v[solucao[rand2-1]][solucao[rand1]] + v[solucao[rand1]][solucao[rand2+1]];
			}
			//printf("Profit atualizado: %d ", pAux);
		}
		count++;
	}
	printf("%d, %d \n", rand1, rand2);
	printf("%d, %d \n", pAux, profit);
	/*for(int i=0; i<tam; i++){
		if(solucao[i]==rand1){
			vAux = i;
		}
		else if (solucao[i] == rand2){
			vAux2 = i;
		}
	}
	solucao[vAux] = rand2;
	solucao[vAux2] = rand1;*/
	vAux = rand1;
	solucao[rand1] = solucao[rand2];
	solucao[rand2] = solucao[vAux];

	for (int i=0; i<tam; i++){
		printf("%d ", solucao[i]);
	}
	profit = funcAvaliacaoV(v, tam, solucao);
	//printf("Profit atualizado: %d ", profit);
	//count++;
	printf("Profit final: %d ", profit);
}

int swap(int** v, int tam, int* solucao){
	int rand1, rand2;
	int profit = 0;
	int vAux, vAux2, vAux3, pAux;
	int count=0;
	int solAux[tam];

	for (int i=0; i<tam; i++){
		solAux[i] = solucao[i];
	}

	profit = funcAvaliacaoV(v, tam, solucao);
	pAux = profit;

	//printf("\nProfit incial: %d \n", profit);

	for(int i=1; i<(tam-1); i++){
		for(int j=i+1; j<tam; j++){
			if(j==tam-1){
				pAux = profit - v[solucao[i-1]][solucao[i]] - v[solucao[i]][solucao[i+1]] - v[solucao[j-1]][solucao[j]] - v[solucao[j]][solucao[0]]
					+ v[solucao[i-1]][solucao[j]] + v[solucao[j]][solucao[i+1]] + v[solucao[j-1]][solucao[i]] + v[solucao[i]][solucao[0]];
			}
			else{
				pAux = profit - v[solucao[i-1]][solucao[i]] - v[solucao[i]][solucao[i+1]] - v[solucao[j-1]][solucao[j]] - v[solucao[j]][solucao[j+1]]
					+ v[solucao[i-1]][solucao[j]] + v[solucao[j]][solucao[i+1]] + v[solucao[j-1]][solucao[i]] + v[solucao[i]][solucao[j+1]];
			}
			//pAux = profit - v[solucao[i-1]][solucao[i]] - v[solucao[i]][solucao[i+1]] - v[solucao[j-1]][solucao[j]] - v[solucao[j]][solucao[j+1]]
			if(pAux<profit){
				vAux = i;
				vAux2 = j;
				profit = pAux;
			}
		}
	}

	vAux3 = solucao[vAux];
	solucao[vAux] = solucao[vAux2];
	solucao[vAux2] = vAux3;

	profit = funcAvaliacaoV(v, tam, solucao);
	//printf("Profit atualizado: %d ", profit);
	//count++;
	//printf("Profit final: %d ", profit);
	return profit;
}

int swap_shake(int** v, int tam, int* solucao){
	int rand1, rand2;
	int profit = 0;
	int vAux, vAux2, pAux;
	int count=0;
	int solAux[tam];

	for (int i=0; i<tam; i++){
		solAux[i] = solucao[i];
	}

	profit = funcAvaliacaoV(v, tam, solucao);
	pAux = profit;

	//printf("\nProfit incial: %d \n", profit);
	srand(time(NULL));

		
	rand1 = rand() % tam;
	rand2 = rand() % tam;
	//printf("%d, %d \n", rand1, rand2);
	//printf("%d, %d ", rand1, rand2);
	while (!(rand1 == rand2 || rand1 == (rand2+1) || rand2 == (rand1+1))){
		vAux = solucao[rand1];
		solucao[rand1] = solucao[rand2];
		solucao[rand2] = vAux;
		//profit = funcAvaliacaoV(v, tam, solAux);
		//printf("Profit atualizado: %d ", profit);
	}
	count++;

	vAux = solucao[rand1];
	solucao[rand1] = solucao[rand2];
	solucao[rand2] = vAux;

	profit = funcAvaliacaoV(v, tam, solucao);
	//printf("Profit atualizado: %d ", profit);
	//count++;
	//printf("Profit final: %d ", profit);
	return profit;
}

int twist(int** v, int tam, int* solucao){
	int rand1, rand2;
	int profit = 0;
	int vAux, vAux2, vAux3, pAux;
	int count=0;
	int solAux[tam];

	for (int i=0; i<tam; i++){
		solAux[i] = solucao[i];
	}

	profit = funcAvaliacaoV(v, tam, solucao);
	pAux = profit;

	//printf("\nProfit incial: %d \n", profit);

	for(int i=1; i<(tam-1); i++){
		for(int j=i+1; j<tam; j++){
			if(j==tam-1){
				pAux = profit - v[solucao[i-1]][solucao[i]] - v[solucao[j]][solucao[0]]
					+ v[solucao[i-1]][solucao[j]] + v[solucao[i]][solucao[0]];
			}
			else{
				pAux = profit - v[solucao[i-1]][solucao[i]] - v[solucao[j]][solucao[j+1]]
					+ v[solucao[i-1]][solucao[j]] + v[solucao[i]][solucao[j+1]];
			}
			
			if(pAux<profit){
				vAux = i;
				vAux2 = j;
				profit = pAux;
			}
		}
	}

	while(vAux<vAux2){		
		vAux3 = solucao[vAux];
		solucao[vAux] = solucao[vAux2];
		solucao[vAux2] = vAux3;
		vAux++;
		vAux2--;
	}

	return profit;
}

void VND(int** v, int tam, int* solucao){
	int menor = INF;
	int profit = funcAvaliacaoV(v, tam, solucao);
	int pAux;
	int k = 1;
	int r = 2;
	printf("\nProfit inicial: %d ", profit);
	while(k<=r){
		if(k == 1){
			printf("Executando Swap\n");
			pAux = swap(v, tam, solucao);
			printf("Fim da execucao Swap\n");
		}
		else{
			printf("Executando Twist\n");
			pAux = twist(v, tam, solucao);
			printf("Fim da execucao Twist\n");
		}

		if(pAux<profit){
			profit = pAux;
			k=1;
		}
		else
			k++;
	}

	printf("\nProfit final: %d ", profit);
}

int main(){
	int tam;
	//char *file = "./instancias/instancias_tsp_cup/tsp1.txt";
	char *file = "./instancias/instancias_teste/berlin52.txt";
	tam = tamanhoEntrada(file);
	int **v;
	int *sol;
	v = malloc (tam * sizeof(int *));
	sol = malloc (tam * sizeof(int *));
	if(v==NULL){
		printf("Erro ao alocar memória!");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<tam; ++i){
		v[i] = malloc (tam * sizeof(int));
		if(v[i]==NULL){
			printf("Erro na alocação de memória!");
			exit(EXIT_FAILURE);
		}
	}

	//Usa a função de leitura de acordo com o arquivo selecionado
	if(tam != 1500){
		lerInstanciaP(file, tam, v);

		//Imprime os valores da matriz
		for(int i=tam; i<tam; i++){
			printf("\n");
			for(int j=0; j<tam; j++){
				printf("%d\t", v[i][j]);
			}
			printf("\n");
		}
	}
	else{
		lerInstanciaG(file, tam, v);
		for(int i=tam; i<tam; i++){
			printf("\n");
			for(int j=0; j<tam; j++){
				printf("%d\t", v[i][j]);
			}
			printf("\n");
		}
	}

	printf("Calculando Solucao!\n");
	melhorInsercao(v, tam, sol);

	printf("Iniciando VND.\n");
	VND(v, tam, sol);
	printf("Execução finalizada!\n");

	for (int i = 0; i < tam; ++i)
	{
		//free(v[i]);
		v[i] = NULL;
	}
	free(v);
	return 0;
}
