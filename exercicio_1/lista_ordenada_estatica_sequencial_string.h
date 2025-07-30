#ifndef LISTA_ORDENADA_ESTATICA_SEQUENCIAL_STRING_H_
#define LISTA_ORDENADA_ESTATICA_SEQUENCIAL_STRING_H_

typedef struct lista * Lista;

Lista cria_lista();

int lista_cheia(Lista);

int lista_vazia(Lista);

int insere_elem_ord(Lista, char *);

int remove_elem_ord(Lista, char *);

int esvazia_lista(Lista);

int apaga_lista(Lista *);

int get_elem_pos(Lista, int, char *);

int remove_todas(Lista, char *);

int remove_posicao(Lista, int, char *);

int tamanho_lista(Lista);

Lista intercala(Lista, Lista);
#endif // LISTA_ORDENADA_ESTATICA_SEQUENCIAL_STRING
