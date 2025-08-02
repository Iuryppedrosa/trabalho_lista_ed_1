#include <stdio.h>
#include <stdlib.h>
#include "DiEnSim.h"

struct no{
    float info;
    struct no *prox;
};

/*Fun��o: Lista cria_lista()
    Entrada: Nenhuma.
    Pr�-condi��o: Nenhuma.
    Processo: Cria uma nova lista vazia.
    Sa�da: Ponteiro nulo (NULL).
    P�s-condi��o: Uma nova lista vazia foi criada.
*/
Lista cria_lista(){ return NULL; }

/*Fun��o: int lista_vazia(Lista lst)
    Entrada: Ponteiro para a lista.
    Pr�-condi��o: Lista deve estar inicializada (pode estar vazia).
    Processo: Verifica se a lista est� vazia (igual a NULL).
    Sa�da: 1 se vazia, 0 caso contr�rio.
    P�s-condi��o: Nenhuma altera��o na lista.
*/
int lista_vazia(Lista lst){
    if(lst == NULL){
        return 1;
    }else{
        return 0;
    }
}

/*Fun��o: int insere_elem(Lista *lst, float elem)
    Entrada: Ponteiro para a lista e o elemento a ser inserido.
    Pr�-condi��o: Lista deve estar inicializada.
    Processo: Aloca um novo n� e insere no in�cio da lista.
    Sa�da: 1 se sucesso, 0 se falha na aloca��o.
    P�s-condi��o: O novo elemento � inserido na primeira posi��o da lista
*/
int insere_elem(Lista *lst, float elem){
    Lista N = (Lista)malloc(sizeof(struct no));
    if(N == NULL) return 0;

    N->info = elem;
    N->prox = *lst;
    *lst = N;
    return 1;
}

/*Fun��o: int remove_elem(Lista *lst, float elem)
    Entrada: Ponteiro para a lista e o elemento a ser removido.
    Pr�-condi��o: Lista deve estar inicializada e n�o vazia.
    Processo: Procura o elemento e, se encontrado, remove-o.
    Sa�da: 1 se removido, 0 se n�o encontrado.
    P�s-condi��o: A lista � modificada caso o elemento seja removido.
*/
int remove_elem(Lista *lst, float elem){
    if(lista_vazia(*lst)) return 0;

    Lista aux = *lst;

    if(aux->info == elem){
        *lst = aux->prox;
        free(aux);
        return 1;
    }

    while(aux->prox != NULL && aux->prox->info != elem){
        aux = aux->prox;
    }

    if(aux->prox == NULL) return 0;

    Lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    return 1;
}

/*Fun��o: int esvazia_lista(Lista *lst)
    Entrada: Ponteiro para a lista.
    Pr�-condi��o: Lista inicializada.
    Processo: Percorre a lista e libera a mem�ria de todos os n�s.
    Sa�da: 1 se sucesso, 0 se j� estava vazia.
    P�s-condi��o: Lista fica vazia (NULL).
*/
int esvazia_lista(Lista *lst){
    if(lista_vazia(*lst)==1){return 0;}

    Lista aux;
    while(*lst != NULL){
        aux = *lst;
        *lst = (*lst)->prox;
        free(aux);
    }return 1;
}

/*Fun��o: void imprime_lista(Lista lst)
    Entrada: Lista.
    Pr�-condi��o: Lista inicializada.
    Processo: Percorre e imprime os elementos da lista.
    Sa�da: Impress�o no terminal.
    P�s-condi��o: Lista permanece inalterada.
*/
void imprime_lista(Lista lst){
    printf("Lista: ");
    while(lst != NULL){
        printf("%.2f ", lst->info);
        lst = lst->prox;
    }
    printf("\n");
}

/*Fun��o: int get_elem_pos(Lista lst, int pos, float *elem)
    Entrada: Lista, posi��o (1-based), ponteiro para armazenar o valor.
    Pr�-condi��o: Lista deve ter pelo menos pos elementos.
    Processo: Percorre at� a posi��o e retorna o valor.
    Sa�da: 1 se encontrado, 0 se posi��o inv�lida.
    P�s-condi��o: Valor armazenado em *elem, lista inalterada.
*/
int get_elem_pos(Lista lst, int pos, float *elem){
    int i = 1;
    while(lst != NULL){
        if(i == pos){
            *elem = lst->info;
            return 1;
        }
        lst = lst->prox;
        i++;
    }
    return 0;
}

/*Fun��o: int tamanho_lista(Lista *lst, int *tam)
    Entrada: Ponteiro para lista e para vari�vel de tamanho.
    Pr�-condi��o: Lista inicializada.
    Processo: Conta a quantidade de n�s na lista.
    Sa�da: 1 se sucesso, 0 se lista vazia.
    P�s-condi��o: Valor do tamanho armazenado em *tam.
*/
int tamanho_lista(Lista *lst, int *tam){
    if(lista_vazia(*lst)==1){return 0;}

    Lista aux = *lst;
    int i = 0;
    while(aux != NULL){
        aux = aux->prox;
        i++;
    }
    *tam = i;
    return 1;;
}

/*Fun��o: int intercala_listas(Lista lst1, Lista lst2, Lista *lst3)
    Entrada: Duas listas de entrada, uma de sa�da.
    Pr�-condi��o: Pelo menos uma das listas n�o deve estar vazia.
    Processo: Esvazia lst3 e intercala elementos de lst1 e lst2 alternadamente.
    Sa�da: 1 se sucesso, 0 se ambas vazias.
    P�s-condi��o: lst3 conter� os elementos intercalados de lst1 e lst2.
*/
int intercala_listas(Lista lst1, Lista lst2, Lista *lst3){
    if(lista_vazia(lst1)==1 && lista_vazia(lst2)==1){return 0;}

    Lista aux1 = lst1;
    Lista aux2 = lst2;
    esvazia_lista(lst3);

    while(aux1 != NULL || aux2 != NULL){
        if(aux1 != NULL){
            insere_elem(lst3, aux1->info);
            aux1 = aux1->prox;
        }
        if(aux2 != NULL){
            insere_elem(lst3, aux2->info);
            aux2 = aux2->prox;
        }
    }return 1;
}

/*Fun��o: int remove_maior(Lista *lst, float *maior)
    Entrada: Ponteiro para a lista, ponteiro para armazenar o maior valor.
    Pr�-condi��o: Lista n�o pode estar vazia.
    Processo: Percorre a lista para encontrar o maior valor e remove-o.
    Sa�da: 1 se sucesso, 0 se lista vazia.
    P�s-condi��o: O maior valor � removido da lista e armazenado em *maior.
*/
int remove_maior(Lista *lst, float *maior){
    if(lista_vazia(*lst)==1){return 0;}

    float maiorlista = (*lst)->info;
    Lista aux = *lst;

    while(aux != NULL){
        if(aux->info > maiorlista){
            maiorlista = aux->info;
        }
        aux = aux->prox;
    }
    *maior = maiorlista;
    remove_elem(lst, maiorlista);
    return 1;
}
















