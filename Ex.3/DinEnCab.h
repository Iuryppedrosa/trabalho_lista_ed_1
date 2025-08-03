typedef struct no *Lista;

Lista cria_lista();
int lista_vazia(Lista lst);
int insere_ord(Lista *lst, int x, int k);
int remove_ord(Lista *lst, int k);
int tamanho(Lista lst, int *tam);
int esvaziar_lista(Lista *lst);
void imprime_lista(Lista lst);
void calcula(Lista lst, int valor);
