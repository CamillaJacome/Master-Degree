

typedef enum {false,true} boolean;


typedef struct stnolista{
    int dado;
    struct stnolista *prox;
}no;

typedef no* lista;


void inicializa(lista *lst);


boolean vazia(lista lst);

int tamanho(lista lst);
void exibeLista(lista lst);

boolean inserir(lista *lst, int posicao, int dado);


boolean cheia(lista lst);
/*
boolean elemento(lista lst, int posicao, int *dado);

int busca(lista lst, int dado);
boolean remover(lista *lst, int posicao, int *dado);

*/

