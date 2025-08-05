#ifndef TAD_CIRC_H_INCLUDED
#define TAD_CIRC_H_INCLUDED

// --- ESTRUTURAS ---

// A lista eh um ponteiro para o struct no. O ponteiro apontar� para o �LTIMO n�.
typedef struct no *Lista;


// --- PROT�TIPOS ---
// Opera��es B�sicas
Lista cria_lista();
int lista_vazia(Lista lst);
int apaga_lista(Lista *lst);
int esvazia_lista(Lista *lst);

int insere_inicio(Lista *lst, char elem);
int insere_elem(Lista *lst, char elem); // Por padr�o, insere no fim
int remove_elem(Lista *lst, char elem);
int remove_fim(Lista *lst, char *elem);
int get_elem_pos(Lista lst, int pos, char *elem);
int tamanho_lista(Lista lst);
int iguais(Lista l1, Lista l2);

#endif // TAD_CIRC_H_INCLUDED
