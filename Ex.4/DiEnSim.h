typedef struct no *Lista;

Lista cria_lista();
int lista_vazia(Lista lst);
int insere_elem(Lista *lst, float elem);
int remove_elem(Lista *lst, float elem);
int esvazia_lista(Lista *lst);
void imprime_lista(Lista lst);
int tamanho_lista(Lista *lst, int *tam);
int intercala_listas(Lista lst1, Lista lst2, Lista *lst3);
int remove_maior(Lista *lst, float *maior);


