#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

class Aresta
{
	int vertice1, vertice2, peso;

public:

	Aresta(int v1, int v2, int peso)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	int getVertice1()
	{
		return vertice1;
	}

	int getVertice2()
	{
		return vertice2;
	}

	int getPeso()
	{
		return peso;
	}

	bool operator < (const Aresta& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

class Grafo
{
	int V; //nº de vertices
	vector<Aresta> arestas; //vetor de arestas 

public:

	Grafo(int V)
	{
		this->V = V;
	}

	void addAresta(int v1, int v2, int peso)
	{
		Aresta aresta(v1, v2, peso);
		arestas.push_back(aresta);
	}
	//determina se dois elementos estão no mesmo subconjunto
	int find(int subset[], int i)
	{
		if(subset[i] == -1)
			return i;
		return find(subset, subset[i]);
	}
	//une dois subconjuntos em um unico subconjunto
	void unir(int subset[], int v1, int v2)
	{
		int v1_set = find(subset, v1);
		int v2_set = find(subset, v2);
		subset[v1_set] = v2_set;
	}

	///  implementação do algoritmo de kruskal
	void kruskal()
	{
		vector<Aresta> agm;
		int size_arestas = arestas.size();

		// ordenar por peso
		sort(arestas.begin(), arestas.end());

		// criar subconjuntos
		int * subset = new int[V];


		memset(subset, -1, sizeof(int) * V);

		for(int i = 0; i < size_arestas; i++)
		{
			int v1 = find(subset, arestas[i].obterVertice1());
			int v2 = find(subset, arestas[i].obterVertice2());
			
			//se for diferente, não forma ciclos
			if(v1 != v2)
			{
				arvore.push_back(arestas[i]);
				unir(subset, v1, v2); 
			}
		}

		int size_agm = agm.size();

		for(int i = 0; i < size_agm; i++)
		{
			char v1 = agm[i].getVertice1();
			char v2 = agm[i].getVertice2();
			cout << "(" << v1 << ", " << v2 << ") = " << agm[i].getPeso() << endl;
		}
	}
};

