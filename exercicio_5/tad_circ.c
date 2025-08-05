#include <stdio.h>
#include <stdlib.h>
#include "tad_circ.h"

// O nó da lista armazena a informação e um ponteiro para o próximo nó
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
processo: Verifica se o ponteiro da lista é nulo.
saida: Retorna 1 se a lista for vazia, 0 caso contrário.
pos-condicao: Nenhuma.
*/
int lista_vazia(Lista lst) {
    return (lst == NULL);
}

/*
APAGA_LISTA()
entrada: O endereço de uma lista.
pre-condicao: Nenhuma.
processo: Libera todos os nós da lista e atribui NULL ao ponteiro original.
saida: Retorna 1 em caso de sucesso, 0 caso contrário.
pos-condicao: Toda a memória alocada para a lista é liberada.
*/
int apaga_lista(Lista *lst) {
    if (lst == NULL) return 0;
    return esvazia_lista(lst);
}

/*
ESVAZIA_LISTA()
entrada: O endereço de uma lista.
pre-condicao: Nenhuma.
processo: Percorre a lista, liberando a memória de cada nó um por um.
saida: Retorna 1 em caso de sucesso, 0 caso contrário.
pos-condicao: A lista se torna vazia (ponteiro aponta para NULL).
*/
int esvazia_lista(Lista *lst) {
    if (lst == NULL || *lst == NULL) {
        return 0;
    }
    Lista aux = (*lst)->prox; // Aponta para o primeiro elemento
    Lista cabecalho = aux;    // Guarda o início para a condição de parada

    while (aux != *lst) {
        Lista temp = aux;
        aux = aux->prox;
        free(temp);
    }
    free(*lst); // Libera o último nó
    *lst = NULL;
    return 1;
}

/*
INSERE_INICIO()
entrada: O endereço da lista e o caractere a ser inserido.
pre-condicao: Nenhuma.
processo: Aloca um novo nó. Se a lista estiver vazia, o nó aponta para si mesmo.
          Senão, ele é inserido entre o último e o primeiro nó original.
saida: Retorna 1 para sucesso, 0 para falha (memória insuficiente).
pos-condicao: O elemento é o novo primeiro da lista.
*/
int insere_inicio(Lista *lst, char elem) {
    Lista N = (Lista) malloc(sizeof(struct no));
    if (N == NULL) return 0; // Falha de alocação

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
entrada: O endereço da lista e o caractere a ser inserido (no final).
pre-condicao: Nenhuma.
processo: Aloca um novo nó. Insere no início e depois avança o ponteiro
          da lista para que o novo nó se torne o último.
saida: Retorna 1 para sucesso, 0 para falha (memória insuficiente).
pos-condicao: O elemento é o novo último da lista.
*/
int insere_elem(Lista *lst, char elem) {
    if (insere_inicio(lst, elem)) {
        // Se a inserção no início deu certo, o novo elemento é o primeiro.
        // Para que ele seja o último, basta avançar o ponteiro da lista.
        if ((*lst)->prox != *lst) { // Garante que não é o único elemento
             *lst = (*lst)->prox;
        }
        return 1;
    }
    return 0;
}


/*
REMOVE_FIM()
entrada: O endereço da lista e um ponteiro para char para retornar o valor.
pre-condicao: A lista não pode estar vazia.
processo: Encontra o nó anterior ao último. Salva a informação do último,
          faz o nó anterior apontar para o primeiro, libera o último e o
          atualiza como o novo último.
saida: Retorna 1 para sucesso, 0 para falha.
pos-condicao: O último elemento é removido e seu valor retornado.
*/
int remove_fim(Lista *lst, char *elem) {
    if (lista_vazia(*lst)) return 0;

    Lista no_remover = *lst;
    *elem = no_remover->info;

    if (*lst == (*lst)->prox) { // Caso 1: Apenas um elemento
        free(*lst);
        *lst = NULL;
    } else { // Caso 2: Múltiplos elementos
        Lista ant = (*lst)->prox;
        while(ant->prox != *lst) { // Acha o penúltimo
            ant = ant->prox;
        }
        ant->prox = (*lst)->prox; // Penúltimo aponta para o primeiro
        *lst = ant; // Penúltimo se torna o último
        free(no_remover);
    }
    return 1;
}


/*
REMOVE_ELEM()
entrada: O endereço da lista e o caractere a ser removido.
pre-condicao: A lista não pode estar vazia.
processo: Percorre a lista com um ponteiro auxiliar e um anterior. Ao achar
          o elemento, remove-o, tratando os casos de ser o primeiro,
          o último ou um nó do meio.
saida: Retorna 1 se removeu, 0 se não encontrou o elemento ou a lista estava vazia.
pos-condicao: O primeiro nó com o caractere correspondente é removido.
*/
int remove_elem(Lista *lst, char elem) {
    if (lista_vazia(*lst)) return 0;

    Lista aux = (*lst)->prox; // Começa no primeiro
    Lista ant = *lst; // O anterior ao primeiro é o último

    // Procura pelo elemento, parando quando der a volta completa
    int i, tam = tamanho_lista(*lst);
    for (i = 0; i < tam; i++) {
        if (aux->info == elem) {
            // Se o elemento a remover é o único da lista
            if (aux == ant) {
                free(aux);
                *lst = NULL;
                return 1;
            }
            // Se for o último elemento da lista
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
    return 0; // Não encontrou
}

/*
GET_ELEM_POS()
entrada: A lista, a posição desejada e um ponteiro para char para retorno.
pre-condicao: A lista não pode estar vazia e a posição deve ser válida.
processo: Percorre a lista a partir do primeiro nó até a posição desejada.
saida: Retorna 1 para sucesso, 0 para falha.
pos-condicao: O valor do elemento da posição é retornado no ponteiro 'elem'.
*/
int get_elem_pos(Lista lst, int pos, char *elem) {
    if (lista_vazia(lst) || pos <= 0) return 0;

    Lista aux = lst->prox; // Começa no primeiro
    int i = 1;
    while(i < pos) {
        aux = aux->prox;
        // Se deu a volta na lista e não achou a posição
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
processo: Se a lista não for vazia, percorre contando os nós até voltar ao início.
saida: Retorna o número de elementos da lista.
pos-condicao: Nenhuma.
*/
int tamanho_lista(Lista lst) {
    if (lista_vazia(lst)) return 0;

    int cont = 0;
    Lista aux = lst->prox; // Começa no primeiro
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
processo: Compara os tamanhos. Se forem iguais e não vazias, percorre ambas
          simultaneamente, comparando o conteúdo de cada nó.
saida: Retorna 1 se forem idênticas, 0 caso contrário.
pos-condicao: Nenhuma.
*/
int iguais(Lista l1, Lista l2) {
    if (tamanho_lista(l1) != tamanho_lista(l2)) return 0;
    if (lista_vazia(l1)) return 1; // Se tamanhos são iguais e uma é vazia, a outra também é

    Lista aux1 = l1->prox; // Ponteiro para o primeiro de l1
    Lista aux2 = l2->prox; // Ponteiro para o primeiro de l2

    do {
        if (aux1->info != aux2->info) return 0; // Se um elemento for diferente
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    } while (aux1 != l1->prox); // Percorre a lista toda

    return 1; // Se chegou até aqui, são iguais
}
