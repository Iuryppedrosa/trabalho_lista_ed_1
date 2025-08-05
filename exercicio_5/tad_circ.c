#include <stdio.h>
#include <stdlib.h>
#include "tad_circ.h"

// O n� da lista armazena a informa��o e um ponteiro para o pr�ximo n�
struct no {
    char info;
    struct no *prox;
};

/*
CRIA_LISTA()
entrada: Nenhuma.
pre-condicao: Nenhuma.
processo: Retorna um ponteiro nulo, representando uma lista vazia.
saida: Retorna NULL.
pos-condicao: Nenhuma.
*/
Lista cria_lista() {
    return NULL;
}

/*
LISTA_VAZIA()
entrada: A lista a ser verificada.
pre-condicao: Nenhuma.
processo: Verifica se o ponteiro da lista � nulo.
saida: Retorna 1 se a lista for vazia, 0 caso contr�rio.
pos-condicao: Nenhuma.
*/
int lista_vazia(Lista lst) {
    return (lst == NULL);
}

/*
APAGA_LISTA()
entrada: O endere�o de uma lista.
pre-condicao: Nenhuma.
processo: Libera todos os n�s da lista e atribui NULL ao ponteiro original.
saida: Retorna 1 em caso de sucesso, 0 caso contr�rio.
pos-condicao: Toda a mem�ria alocada para a lista � liberada.
*/
int apaga_lista(Lista *lst) {
    if (lst == NULL) return 0;
    return esvazia_lista(lst);
}

/*
ESVAZIA_LISTA()
entrada: O endere�o de uma lista.
pre-condicao: Nenhuma.
processo: Percorre a lista, liberando a mem�ria de cada n� um por um.
saida: Retorna 1 em caso de sucesso, 0 caso contr�rio.
pos-condicao: A lista se torna vazia (ponteiro aponta para NULL).
*/
int esvazia_lista(Lista *lst) {
    if (lst == NULL || *lst == NULL) {
        return 0;
    }
    Lista aux = (*lst)->prox; // Aponta para o primeiro elemento
    Lista cabecalho = aux;    // Guarda o in�cio para a condi��o de parada

    while (aux != *lst) {
        Lista temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(*lst); // Libera o �ltimo n�
    *lst = NULL;
    return 1;
}

/*
INSERE_INICIO()
entrada: O endere�o da lista e o caractere a ser inserido.
pre-condicao: Nenhuma.
processo: Aloca um novo n�. Se a lista estiver vazia, o n� aponta para si mesmo.
          Sen�o, ele � inserido entre o �ltimo e o primeiro n� original.
saida: Retorna 1 para sucesso, 0 para falha (mem�ria insuficiente).
pos-condicao: O elemento � o novo primeiro da lista.
*/
int insere_inicio(Lista *lst, char elem) {
    Lista N = (Lista) malloc(sizeof(struct no));
    if (N == NULL) return 0; // Falha de aloca��o

    N->info = elem;
    if (lista_vazia(*lst)) {
        *lst = N;
        N->prox = N;
    } else {
        N->prox = (*lst)->prox;
        (*lst)->prox = N;
    }
    return 1;
}

/*
INSERE_ELEM()
entrada: O endere�o da lista e o caractere a ser inserido (no final).
pre-condicao: Nenhuma.
processo: Aloca um novo n�. Insere no in�cio e depois avan�a o ponteiro
          da lista para que o novo n� se torne o �ltimo.
saida: Retorna 1 para sucesso, 0 para falha (mem�ria insuficiente).
pos-condicao: O elemento � o novo �ltimo da lista.
*/
int insere_elem(Lista *lst, char elem) {
    if (insere_inicio(lst, elem)) {
        // Se a inser��o no in�cio deu certo, o novo elemento � o primeiro.
        // Para que ele seja o �ltimo, basta avan�ar o ponteiro da lista.
        if ((*lst)->prox != *lst) { // Garante que n�o � o �nico elemento
             *lst = (*lst)->prox;
        }
        return 1;
    }
    return 0;
}


/*
REMOVE_FIM()
entrada: O endere�o da lista e um ponteiro para char para retornar o valor.
pre-condicao: A lista n�o pode estar vazia.
processo: Encontra o n� anterior ao �ltimo. Salva a informa��o do �ltimo,
          faz o n� anterior apontar para o primeiro, libera o �ltimo e o
          atualiza como o novo �ltimo.
saida: Retorna 1 para sucesso, 0 para falha.
pos-condicao: O �ltimo elemento � removido e seu valor retornado.
*/
int remove_fim(Lista *lst, char *elem) {
    if (lista_vazia(*lst)) return 0;

    Lista no_remover = *lst;
    *elem = no_remover->info;

    if (*lst == (*lst)->prox) { // Caso 1: Apenas um elemento
        free(*lst);
        *lst = NULL;
    } else { // Caso 2: M�ltiplos elementos
        Lista ant = (*lst)->prox;
        while(ant->prox != *lst) { // Acha o pen�ltimo
            ant = ant->prox;
        }
        ant->prox = (*lst)->prox; // Pen�ltimo aponta para o primeiro
        *lst = ant; // Pen�ltimo se torna o �ltimo
        free(no_remover);
    }
    return 1;
}


/*
REMOVE_ELEM()
entrada: O endere�o da lista e o caractere a ser removido.
pre-condicao: A lista n�o pode estar vazia.
processo: Percorre a lista com um ponteiro auxiliar e um anterior. Ao achar
          o elemento, remove-o, tratando os casos de ser o primeiro,
          o �ltimo ou um n� do meio.
saida: Retorna 1 se removeu, 0 se n�o encontrou o elemento ou a lista estava vazia.
pos-condicao: O primeiro n� com o caractere correspondente � removido.
*/
int remove_elem(Lista *lst, char elem) {
    if (lista_vazia(*lst)) return 0;

    Lista aux = (*lst)->prox; // Come�a no primeiro
    Lista ant = *lst; // O anterior ao primeiro � o �ltimo

    // Procura pelo elemento, parando quando der a volta completa
    int i, tam = tamanho_lista(*lst);
    for (i = 0; i < tam; i++) {
        if (aux->info == elem) {
            // Se o elemento a remover � o �nico da lista
            if (aux == ant) {
                free(aux);
                *lst = NULL;
                return 1;
            }
            // Se for o �ltimo elemento da lista
            if (aux == *lst) {
                char temp;
                return remove_fim(lst, &temp);
            }
            // Se for o primeiro ou um do meio
            ant->prox = aux->prox;
            free(aux);
            return 1;
        }
        ant = aux;
        aux = aux->prox;
    }
    return 0; // N�o encontrou
}

/*
GET_ELEM_POS()
entrada: A lista, a posi��o desejada e um ponteiro para char para retorno.
pre-condicao: A lista n�o pode estar vazia e a posi��o deve ser v�lida.
processo: Percorre a lista a partir do primeiro n� at� a posi��o desejada.
saida: Retorna 1 para sucesso, 0 para falha.
pos-condicao: O valor do elemento da posi��o � retornado no ponteiro 'elem'.
*/
int get_elem_pos(Lista lst, int pos, char *elem) {
    if (lista_vazia(lst) || pos <= 0) return 0;

    Lista aux = lst->prox; // Come�a no primeiro
    int i = 1;
    while(i < pos) {
        aux = aux->prox;
        // Se deu a volta na lista e n�o achou a posi��o
        if (aux == lst->prox) return 0;
        i++;
    }
    *elem = aux->info;
    return 1;
}

/*
TAMANHO_LISTA()
entrada: A lista.
pre-condicao: Nenhuma.
processo: Se a lista n�o for vazia, percorre contando os n�s at� voltar ao in�cio.
saida: Retorna o n�mero de elementos da lista.
pos-condicao: Nenhuma.
*/
int tamanho_lista(Lista lst) {
    if (lista_vazia(lst)) return 0;

    int cont = 0;
    Lista aux = lst->prox; // Come�a no primeiro
    do {
        cont++;
        aux = aux->prox;
    } while (aux != lst->prox); // Para quando der uma volta completa

    return cont;
}

/*
IGUAIS()
entrada: Duas listas, l1 e l2.
pre-condicao: Nenhuma.
processo: Compara os tamanhos. Se forem iguais e n�o vazias, percorre ambas
          simultaneamente, comparando o conte�do de cada n�.
saida: Retorna 1 se forem id�nticas, 0 caso contr�rio.
pos-condicao: Nenhuma.
*/
int iguais(Lista l1, Lista l2) {
    if (tamanho_lista(l1) != tamanho_lista(l2)) return 0;
    if (lista_vazia(l1)) return 1; // Se tamanhos s�o iguais e uma � vazia, a outra tamb�m �

    Lista aux1 = l1->prox; // Ponteiro para o primeiro de l1
    Lista aux2 = l2->prox; // Ponteiro para o primeiro de l2

    do {
        if (aux1->info != aux2->info) return 0; // Se um elemento for diferente
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    } while (aux1 != l1->prox); // Percorre a lista toda

    return 1; // Se chegou at� aqui, s�o iguais
}
