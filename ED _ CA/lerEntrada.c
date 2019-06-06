#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define INF 100000000


//Recupera a dimensão das entradas
int tamanho(char files[]){
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


void solucao(int** v, int tam, int* solucao){

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

int main(){
	int tam;
	//char *file = "./instancias/instancias_tsp_cup/tsp1.txt";
	char *file = "./instancias/instancias_teste/bayg29.txt";
	tam = tamanho(file);
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
	if(file[25] == 'e'){
		lerInstanciaP(file, tam, v);
		//Imprime os valores da matriz
		for(int i=0; i<tam; i++){
			printf("\n");
			for(int j=0; j<tam; j++){
				printf("%d\t", v[i][j]);
			}
			printf("\n");
		}
	}
	else
		lerInstanciaG(file, tam, v);

	solucao(v,tam,sol);

	for (int i = 0; i < tam; ++i)
	{
		//free(v[i]);
		v[i] = NULL;
	}
	free(v);
	return 0;
}
