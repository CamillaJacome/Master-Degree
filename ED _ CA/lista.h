#include <stdbool.h>


typedef struct tNo{
    int indice;
    struct tNo *prox;
}tNo;

typedef tNo* lista;


void inicializa(lista *lst);

int busca(lista lst, int indice);

bool vazia(lista lst);

int tamanho(lista lst);
void exibeLista(lista lst);

bool inserir(lista *lst, int posicao, int indice);

bool deletaLista(lista *lst);

