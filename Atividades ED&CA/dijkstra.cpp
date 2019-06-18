#include <iostream>
#include <list>
#include <queue>
#define INFINITO 1000

using namespace std;

class Grafo
{
private:
	int V; // nº  de vértices

	// listas de adjacências 
	list<pair<int, int> > * adj;

public:

	Grafo(int V)
	{
		this->V = V;

		//cria lista de adjacencia destino/custo
		adj = new list<pair<int, int> >[V];
	}

	// adiciona uma aresta ao grafo
	void addAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de distancia
		int dist[V];
		// Vetor para cada vertice visitado
		int visitados[V];
		// fila de prioridades distancia/vertice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}
		dist[orig] = 0;
		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai a distancia
			int u = p.second; // extrai o vertice
			pq.pop(); // remove da fila

			if(visitados[u] == false)
			{
				visitados[u] = true;

				list<pair<int, int> >::iterator it;

				// percorre os adjacentes
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// extrai o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// processo de relaxamento
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		// retorna a distancia minima
		return dist[dest];
	}
};

