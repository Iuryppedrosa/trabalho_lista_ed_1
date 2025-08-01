#include <stdio.h>
#include <stdlib.h>
#include "lista_dinamica_duplamente_encad.h"

struct no {
    int info;
    struct no * ante;
    struct no * prox;
};

/*
Entrada: Nenhuma.
Pré-condição: Nenhuma.
Processo: Cria uma lista vazia.
Saída: Ponteiro para a lista criada (NULL).
Pós-condição: A lista está vazia.
*/
Lista cria_lista(){
    return NULL;
}

/*
Entrada: Ponteiro para a lista.
Pré-condição: A lista deve ser válida.
Processo: Verifica se a lista está vazia.
Saída: 1 se a lista está vazia, 0 caso contrário.
Pós-condição: A lista permanece inalterada.
*/
int lista_vazia(Lista l){
    if(l == NULL){
        return 1;
    }
    return 0;
}

/*
Entrada: Endereço do ponteiro para a lista e o elemento a ser inserido.
Pré-condição: A lista deve ser válida.
Processo: Insere o elemento no início da lista.
Saída: 1 se a inserção for bem-sucedida, 0 caso contrário.
Pós-condição: O elemento é inserido no início da lista, e os ponteiros são ajustados.
*/
int insere_elemento(Lista *l, int elem){
    Lista no = (Lista) malloc(sizeof(struct no));
    if(no == NULL){
        return 0;
    }
    no->info = elem;
    no->ante = NULL;
    no->prox = *l; // ou vai ser NULL ou vai ser o antigo primeiro
    if(lista_vazia(*l) == 0){
        (*l)->ante = no;
    }
    *l = no;
    return 1;
}

/*
Entrada: Endereço do ponteiro para a lista e o elemento a ser removido.
Pré-condição: A lista deve ser válida.
Processo: Remove a primeira ocorrência do elemento na lista.
Saída: 1 se a remoção for bem-sucedida, 0 caso contrário.
Pós-condição: O elemento é removido da lista, e os ponteiros são ajustados.
*/
int remove_elemento(Lista *l, int elem){
    if(lista_vazia(*l) == 1){
        return 0;
    }
    Lista aux = *l;
    while(aux->prox != NULL && aux->info != elem){
        aux = aux->prox;
    }
    if(aux->info != elem){
        return 0;
    }
    if(aux->prox != NULL){ // uma coisa
        aux->prox->ante = aux->ante;
    }
    if(aux->ante != NULL){ // complementa a outra
        aux->ante->prox = aux->prox;
    }
    if(aux == *l){//primeiro elemento
        *l = aux->prox; //l aponta para NULL
    }
    free(aux);
    return 1;
}

/*
Entrada: Endereço do ponteiro para a lista.
Pré-condição: A lista deve ser válida.
Processo: Remove todos os elementos da lista.
Saída: 1 se a lista for esvaziada, 0 se já estava vazia.
Pós-condição: A lista está vazia, e toda a memória alocada é liberada.
 */
int esvazia_lista(Lista *l){
    if(lista_vazia(*l) == 1)
        return 0;
    Lista aux = *l;
    while(aux->prox != NULL){
        *l = aux->prox;
        aux = aux->prox;
        free(aux->ante);
    }
    *l = aux->prox;
    free(aux);
    return 1;
}

/*
Entrada: Ponteiro para a lista.
Pré-condição: A lista deve ser válida.
Processo: Conta o número de elementos na lista.
Saída: Número de elementos na lista.
Pós-condição: A lista permanece inalterada.
*/
int tamanho_lista(Lista l){
    int tamanho = 1;
    Lista aux = l;
    while(aux->prox != NULL){
        aux = aux->prox;
        tamanho++;
    }
    return tamanho;
}

/*
Entrada: Ponteiro para a lista, posição desejada e endereço para armazenar o elemento.
Pré-condição: A lista deve ser válida, e a posição deve ser maior que 0.
Processo: Obtém o elemento na posição especificada.
Saída: 1 se o elemento for encontrado, 0 caso contrário.
Pós-condição: O elemento é armazenado no endereço fornecido, e a lista permanece inalterada.
*/
int get_elem_posicao(Lista l, int posicao, int *elemento){
    int avanco = 1;
    Lista aux = l;
    while(aux->prox != NULL && avanco != posicao){
        aux = aux->prox;
        avanco++;
    }
    *elemento = aux->info;
    return elemento;
}


/*
Entrada: Ponteiro para a lista.
Pré-condição: A lista deve ser válida.
Processo: Cria um vetor com os elementos da lista.
Saída: Ponteiro para o vetor com os elementos da lista.
Pós-condição: A lista permanece inalterada, e o vetor deve ser liberado pelo chamador.
*/
int *veja_lista(Lista l){
    int tamanho = tamanho_lista(l);
    int * vetor = (int) malloc(tamanho * sizeof(int));
    Lista aux = l;
    for(int i = 0; i < tamanho; i++){
        vetor[i] = aux->info;
        aux = aux->prox;
    }
    return vetor;
}


/*
Entrada: Endereço do ponteiro para a lista.
Pré-condição: A lista deve ser válida.
Processo: Remove todos os elementos pares da lista.
Saída: 1 se algum elemento foi removido, 0 se a lista está vazia ou não há elementos pares.
Pós-condição: Todos os elementos pares são removidos, e os ponteiros são ajustados.
 */
int remove_pares(Lista *l) {
    if (lista_vazia(*l) == 1) {
        return 0;
    }
    int removido = 0;
    Lista aux = *l;
    while (aux != NULL) {
        Lista proximo = aux->prox; // Salva próximo antes de possível remoção
        if (aux->info % 2 == 0) {
            if (aux->ante == NULL) {
                *l = aux->prox;
                if (*l != NULL) {
                    (*l)->ante = NULL;
                }
            } else if (aux->prox == NULL) {
                aux->ante->prox = NULL;
            } else {
                aux->ante->prox = aux->prox;
                aux->prox->ante = aux->ante;
            }
            free(aux);
            removido = 1;
        }
        aux = proximo;
    }
    return removido;
}

/*
Entrada: Endereço do ponteiro para a lista e endereço para armazenar o maior elemento.
Pré-condição: A lista deve ser válida.
Processo: Remove a última ocorrência do maior elemento da lista.
Saída: 1 se a remoção for bem-sucedida, 0 se a lista está vazia.
Pós-condição: O maior elemento é removido, seu valor é armazenado, e os ponteiros são ajustados.
 */
int remove_maior(Lista *l, int *maior) {
    if (lista_vazia(*l) == 1) {
        return 0;
    }
    Lista aux = *l;
    Lista ultimo_maior = NULL;
    int valor_maior = aux->info;
    while (aux != NULL) {
        if (aux->info >= valor_maior) {
            valor_maior = aux->info;
            ultimo_maior = aux;
        }
        aux = aux->prox;
    }
    *maior = valor_maior;
    if (ultimo_maior->ante == NULL) {
        *l = ultimo_maior->prox;
        if (*l != NULL) {
            (*l)->ante = NULL;
        }
    } else if (ultimo_maior->prox == NULL) {
        ultimo_maior->ante->prox = NULL;
    } else {
        ultimo_maior->ante->prox = ultimo_maior->prox;
        ultimo_maior->prox->ante = ultimo_maior->ante;
    }
    free(ultimo_maior);
    return 1;
}

/*
Entrada: Endereço do ponteiro para a lista, elemento a inserir e posição desejada.
Pré-condição: A lista deve ser válida, e a posição deve ser maior que 0.
Processo: Insere o elemento na posição especificada.
Saída: 1 se a inserção for bem-sucedida, 0 caso contrário.
Pós-condição: O elemento é inserido na posição indicada, e os ponteiros são ajustados.
 */
int insere_posicao(Lista *l, int elem, int pos) {
    if (pos < 1) {
        return 0;
    }
    if (pos == 1 || lista_vazia(*l) == 1) {
        return insere_elemento(l, elem);
    }
    Lista no = (Lista) malloc(sizeof(struct no));
    if (no == NULL) {
        return 0;
    }
    no->info = elem;
    Lista aux = *l;
    int avanco = 1;
    while (aux != NULL && avanco < pos) {
        aux = aux->prox;
        avanco++;
    }
    if (aux == NULL && avanco != pos) {
        free(no);
        return 0;
    }
    no->prox = aux;
    no->ante = aux->ante;
    aux->ante->prox = no;
    aux->ante = no;
    return 1;
}

/*
Entrada: Ponteiro para a lista original.
Pré-condição: A lista deve ser válida.
Processo: Cria uma nova lista com os elementos da lista original em ordem inversa.
Saída: Ponteiro para a nova lista invertida.
Pós-condição: A lista original permanece inalterada, e a nova lista contém os elementos na ordem inversa.
*/
Lista inverte_lista(Lista l) {
    Lista l2 = cria_lista();
    Lista aux = l;
    while (aux != NULL) {
        insere_elemento(&l2, aux->info);
        aux = aux->prox;
    }
    return l2;
}
