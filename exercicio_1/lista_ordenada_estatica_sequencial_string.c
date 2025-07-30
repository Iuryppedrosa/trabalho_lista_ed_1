#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lista_ordenada_estatica_sequencial_string.h"

struct lista {
    char palavra[10][20];
    int fim;
};

/*
entrada: Nenhuma.
pre-condicao: Nenhuma.
processo: Aloca mem�ria para uma nova lista est�tica.
saida: Ponteiro para a nova lista ou NULL se a aloca��o falhar.
pos-condicao: Lista criada e inicializada como vazia.
*/
Lista cria_lista() {
    Lista l = (Lista) malloc(sizeof(struct lista));
    if (l == NULL) {
        return NULL;
    }
    l->fim = 0;
    for (int i = 0; i < 10; i++) {
        l->palavra[i][0] = '\0';
    }
    return l;
}

/*
entrada: Ponteiro para a lista.
pre-condicao: Nenhuma.
processo: Verifica se a lista est� cheia.
saida: 1 se a lista est� cheia, 0 caso contr�rio.
pos-condicao: Nenhuma.
*/
int lista_cheia(Lista l) {
    if (l == NULL || l->fim == 10) {
        return 1;
    }
    return 0;
}

/*
entrada: Ponteiro para a lista.
pre-condicao: Nenhuma.
processo: Verifica se a lista est� vazia.
saida: 1 se a lista est� vazia, 0 caso contr�rio.
pos-condicao: Nenhuma.
*/
int lista_vazia(Lista l) {
    if (l == NULL || l->fim == 0) {
        return 1;
    }
    return 0;
}

/*
entrada: Ponteiro para a lista e string a ser inserida.
pre-condicao: Lista inicializada e string com no m�ximo 19 caracteres.
processo: Insere a string na lista em ordem.
saida: 1 se a inser��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: String inserida na posi��o correta, mantendo a ordem.
*/
int insere_elem_ord(Lista l, char *palavra) {
    if (l == NULL || lista_cheia(l) || strlen(palavra) >= 20) {
        return 0;
    }
    int pos = l->fim;
    while (pos > 0 && strcmp(l->palavra[pos - 1], palavra) > 0) {
        strcpy(l->palavra[pos], l->palavra[pos - 1]);
        pos--;
    }
    strcpy(l->palavra[pos], palavra);
    l->fim++;
    return 1;
}

/*
entrada: Ponteiro para a lista e string a ser removida.
pre-condicao: Lista inicializada.
processo: Remove a primeira ocorr�ncia da string na lista.
saida: 1 se a remo��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: Primeira ocorr�ncia da string removida, mantendo a ordem dos elementos restantes.
*/
int remove_elem_ord(Lista l, char *palavra) {
    if (l == NULL || lista_vazia(l)) {
        return 0;
    }
    int aux = 0;
    while (aux < l->fim && strcmp(l->palavra[aux], palavra) < 0) {
        aux++;
    }
    if (aux == l->fim || strcmp(l->palavra[aux], palavra) != 0) {
        return 0;
    }
    for (int i = aux + 1; i < l->fim; i++) {
        strcpy(l->palavra[i - 1], l->palavra[i]);
    }
    l->fim--;
    return 1;
}

/*
entrada: Ponteiro para a lista e string a ser removida.
pre-condicao: Lista inicializada ou nao vazia.
processo: Remove todas as ocorr�ncias da string na lista.
saida: N�mero de ocorr�ncias removidas.
pos-condicao: Todas as ocorr�ncias da string removidas, mantendo a ordem dos elementos restantes.
*/
int remove_todas(Lista l, char *palavra_a_remover) {
    if (l == NULL || lista_vazia(l) != 1) {
        return 0;
    }
    int i = 0;
    int removidos = 0;
    while (i < l->fim) {
        if (strcmp(l->palavra[i], palavra_a_remover) == 0) {
            for (int j = i + 1; j < l->fim; j++) {
                strcpy(l->palavra[j - 1], l->palavra[j]);
            }
            l->fim--;
            removidos++;
        } else {
            i++;
        }
    }
    return removidos;
}

/*
entrada: Ponteiro para a lista, posi��o (1-based) e ponteiro para armazenar a string.
pre-condicao: Lista inicializada e posi��o v�lida.
processo: Obt�m a string na posi��o especificada.
saida: 1 se a obten��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: String da posi��o especificada copiada para o ponteiro fornecido.
*/
int get_elem_pos(Lista l, int posicao_elemento, char *palavra) {
    if (l == NULL || lista_vazia(l) || posicao_elemento < 1 || posicao_elemento > l->fim) {
        return 0;
    }
    strcpy(palavra, l->palavra[posicao_elemento - 1]);
    return 1;
}

/*
entrada: Ponteiro para a lista.
pre-condicao: Lista inicializada e n�o vazia.
processo: Remove todos os elementos da lista, mantendo-a alocada.
saida: 1 se a opera��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: Lista vazia, mas ainda alocada.
*/
int esvazia_lista(Lista l) {
    if (l == NULL || lista_vazia(l)) {
        return 0;
    }
    l->fim = 0;
    return 1;
}

/*
entrada: Ponteiro para o ponteiro da lista.
pre-condicao: Ponteiro da lista inicializado.
processo: Libera a mem�ria da lista e define o ponteiro como NULL.
saida: 1 se a opera��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: Mem�ria da lista liberada e ponteiro definido como NULL.
*/
int apaga_lista(Lista *l) {
    if (l == NULL || *l == NULL) {
        return 0;
    }
    free(*l);
    *l = NULL;
    return 1;
}

/*
entrada: Ponteiro para a lista, posi��o (1-based) e ponteiro para armazenar a string.
pre-condicao: Lista inicializada e posi��o v�lida.
processo: Remove a string na posi��o especificada e a retorna.
saida: 1 se a remo��o for bem-sucedida, 0 caso contr�rio.
pos-condicao: String removida da posi��o especificada, mantendo a ordem dos elementos restantes.
*/
int remove_posicao(Lista l, int posicao, char *palavra) {
    if (l == NULL || lista_vazia(l) || posicao < 1 || posicao > l->fim) {
        return 0;
    }
    strcpy(palavra, l->palavra[posicao - 1]);
    for (int i = posicao; i < l->fim; i++) {
        strcpy(l->palavra[i - 1], l->palavra[i]);
    }
    l->fim--;
    return 1;
}

/*
entrada: Ponteiro para a lista.
pre-condicao: Lista inicializada.
processo: Calcula a quantidade de elementos na lista.
saida: N�mero de elementos na lista, ou 0 se a lista for NULL ou vazia.
pos-condicao: Nenhuma.
*/
int tamanho_lista(Lista l) {
    if (l == NULL || lista_vazia(l)) {
        return 0;
    }
    return l->fim;
}

/*
entrada: Dois ponteiros para listas (L1 e L2).
pre-condicao: Ambas as listas inicializadas.
processo: Cria uma nova lista com os elementos de L1 e L2 intercalados em ordem lexicogr�fica.
saida: Ponteiro para a nova lista ou NULL em caso de falha.
pos-condicao: Nova lista criada com elementos intercalados, L1 e L2 inalteradas.
*/
Lista intercala(Lista l1, Lista l2) {
    Lista l3 = cria_lista();
    if (l3 == NULL) {
        return NULL;
    }
    int i = 0, j = 0;
    while (i < l1->fim && j < l2->fim && !lista_cheia(l3)) {
        if (strcmp(l1->palavra[i], l2->palavra[j]) <= 0) {
            strcpy(l3->palavra[l3->fim], l1->palavra[i]);
            l3->fim++;
            i++;
        } else {
            strcpy(l3->palavra[l3->fim], l2->palavra[j]);
            l3->fim++;
            j++;
        }
    }
    while (i < l1->fim && !lista_cheia(l3)) {
        strcpy(l3->palavra[l3->fim], l1->palavra[i]);
        l3->fim++;
        i++;
    }
    while (j < l2->fim && !lista_cheia(l3)) {
        strcpy(l3->palavra[l3->fim], l2->palavra[j]);
        l3->fim++;
        j++;
    }
    return l3;
}
