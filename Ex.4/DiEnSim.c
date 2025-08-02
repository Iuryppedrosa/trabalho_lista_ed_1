#include <stdio.h>
#include <stdlib.h>
#include "DiEnSim.h"

struct no{
    float info;
    struct no *prox;
};

/*Função: Lista cria_lista()
    Entrada: Nenhuma.
    Pré-condição: Nenhuma.
    Processo: Cria uma nova lista vazia.
    Saída: Ponteiro nulo (NULL).
    Pós-condição: Uma nova lista vazia foi criada.
*/
Lista cria_lista(){ return NULL; }

/*Função: int lista_vazia(Lista lst)
    Entrada: Ponteiro para a lista.
    Pré-condição: Lista deve estar inicializada (pode estar vazia).
    Processo: Verifica se a lista está vazia (igual a NULL).
    Saída: 1 se vazia, 0 caso contrário.
    Pós-condição: Nenhuma alteração na lista.
*/
int lista_vazia(Lista lst){
    if(lst == NULL){
        return 1;
    }else{
        return 0;
    }
}

/*Função: int insere_elem(Lista *lst, float elem)
    Entrada: Ponteiro para a lista e o elemento a ser inserido.
    Pré-condição: Lista deve estar inicializada.
    Processo: Aloca um novo nó e insere no início da lista.
    Saída: 1 se sucesso, 0 se falha na alocação.
    Pós-condição: O novo elemento é inserido na primeira posição da lista
*/
int insere_elem(Lista *lst, float elem){
    Lista N = (Lista)malloc(sizeof(struct no));
    if(N == NULL) return 0;

    N->info = elem;
    N->prox = *lst;
    *lst = N;
    return 1;
}

/*Função: int remove_elem(Lista *lst, float elem)
    Entrada: Ponteiro para a lista e o elemento a ser removido.
    Pré-condição: Lista deve estar inicializada e não vazia.
    Processo: Procura o elemento e, se encontrado, remove-o.
    Saída: 1 se removido, 0 se não encontrado.
    Pós-condição: A lista é modificada caso o elemento seja removido.
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

/*Função: int esvazia_lista(Lista *lst)
    Entrada: Ponteiro para a lista.
    Pré-condição: Lista inicializada.
    Processo: Percorre a lista e libera a memória de todos os nós.
    Saída: 1 se sucesso, 0 se já estava vazia.
    Pós-condição: Lista fica vazia (NULL).
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

/*Função: void imprime_lista(Lista lst)
    Entrada: Lista.
    Pré-condição: Lista inicializada.
    Processo: Percorre e imprime os elementos da lista.
    Saída: Impressão no terminal.
    Pós-condição: Lista permanece inalterada.
*/
void imprime_lista(Lista lst){
    printf("Lista: ");
    while(lst != NULL){
        printf("%.2f ", lst->info);
        lst = lst->prox;
    }
    printf("\n");
}

/*Função: int get_elem_pos(Lista lst, int pos, float *elem)
    Entrada: Lista, posição (1-based), ponteiro para armazenar o valor.
    Pré-condição: Lista deve ter pelo menos pos elementos.
    Processo: Percorre até a posição e retorna o valor.
    Saída: 1 se encontrado, 0 se posição inválida.
    Pós-condição: Valor armazenado em *elem, lista inalterada.
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

/*Função: int tamanho_lista(Lista *lst, int *tam)
    Entrada: Ponteiro para lista e para variável de tamanho.
    Pré-condição: Lista inicializada.
    Processo: Conta a quantidade de nós na lista.
    Saída: 1 se sucesso, 0 se lista vazia.
    Pós-condição: Valor do tamanho armazenado em *tam.
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

/*Função: int intercala_listas(Lista lst1, Lista lst2, Lista *lst3)
    Entrada: Duas listas de entrada, uma de saída.
    Pré-condição: Pelo menos uma das listas não deve estar vazia.
    Processo: Esvazia lst3 e intercala elementos de lst1 e lst2 alternadamente.
    Saída: 1 se sucesso, 0 se ambas vazias.
    Pós-condição: lst3 conterá os elementos intercalados de lst1 e lst2.
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

/*Função: int remove_maior(Lista *lst, float *maior)
    Entrada: Ponteiro para a lista, ponteiro para armazenar o maior valor.
    Pré-condição: Lista não pode estar vazia.
    Processo: Percorre a lista para encontrar o maior valor e remove-o.
    Saída: 1 se sucesso, 0 se lista vazia.
    Pós-condição: O maior valor é removido da lista e armazenado em *maior.
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
















