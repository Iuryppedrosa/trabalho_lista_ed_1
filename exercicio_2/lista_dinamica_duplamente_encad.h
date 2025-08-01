#ifndef LISTA_DINAMICA_DUPLAMENTE_ENCAD_H_
#define LISTA_DINAMICA_DUPLAMENTE_ENCAD_H_

typedef struct no * Lista;
Lista cria_lista();
int lista_vazia(Lista);

// nao ordenada
int insere_elemento(Lista *, int);
int remove_elemento(Lista *, int);
int esvazia_lista(Lista *);
int get_elem_posicao(Lista, int, int *);

int remove_pares(Lista *);
int remove_maior(Lista *, int *);
int insere_posicao(Lista *, int, int);
Lista inverte_lista(Lista);


int tamanho_lista(Lista);
int * veja_lista(Lista);
#endif // LISTA_DINAMICA_DUPLAMENTE_ENCAD_H_
