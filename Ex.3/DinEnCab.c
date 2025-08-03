#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DinEnCab.h"

struct no{
    int info;
    struct {
        int x, k;
    }termo;
    struct no *prox;
};

/*Função: Lista cria_lista()
    Entrada: Nenhuma
    Pré-condição: Nenhuma
    Processo: Aloca dinamicamente uma lista encadeada com nó cabeça, inicializa ponteiro para NULL e contador info com 0.
    Saída: Ponteiro para a lista criada
    Pós-condição: Lista vazia com nó cabeça criada com sucesso.
*/
Lista cria_lista(){
    Lista cab;
    cab = (Lista)malloc(sizeof(struct no));

    if(cab != NULL){
        cab->prox = NULL;
        cab->info = 0;
    }return cab;
}

/*Função: int lista_vazia(Lista lst)
    Entrada: Lista lst
    Pré-condição: Lista deve ter sido criada anteriormente
    Processo: Verifica se o campo prox do nó cabeça é NULL
    Saída: 1 se estiver vazia, 0 caso contrário
    Pós-condição: Lista não é alterada
*/
int lista_vazia(Lista lst){
    if(lst->prox == NULL){return 1;}
    else{return 0;}
}

/*Função: int insere_ord(Lista *lst, int x, int k)
    Entrada: Ponteiro para lista lst, coeficiente x e expoente k
    Pré-condição: Lista deve estar alocada e válida
    Processo: Insere o termo de forma decrescente por k; se já existir termo com o mesmo k, soma os coeficientes. Se a soma der zero, remove o termo.
    Saída: 1 se inserido com sucesso, 0 em caso de falha (ex: falta de memória)
    Pós-condição: Lista contém o novo termo inserido de forma ordenada (ou atualizado)
*/
int insere_ord(Lista *lst, int x, int k){
    Lista aux = *lst;

    while(aux->prox != NULL && aux->prox->termo.k > k){
        aux = aux->prox;
    }

    if(aux->prox != NULL && aux->prox->termo.k == k){
        aux->prox->termo.x += x;

        if(aux->prox->termo.x == 0){ // Opcional: se a soma der zero, remove o termo
            Lista temp = aux->prox;
            aux->prox = temp->prox;
            free(temp);
            (*lst)->info--;
        }
        return 1;
    }

    Lista N = (Lista)malloc(sizeof(struct no));
    if(N == NULL) return 0;

    N->termo.x = x;
    N->termo.k = k;

    N->prox = aux->prox;
    aux->prox = N;

    (*lst)->info++;
    return 1;
}

/*Função: int remove_ord(Lista *lst, int k)
    Entrada: Ponteiro para lista lst, expoente k
    Pré-condição: Lista válida e não vazia
    Processo: Procura e remove o nó cujo expoente seja igual a k
    Saída: 1 se removido com sucesso, 0 se o termo não existir
    Pós-condição: Lista sem o termo com expoente k, se ele existia
*/
int remove_ord(Lista *lst, int k){
    if(lista_vazia(*lst)==1){return 0;}

    Lista aux = *lst;

    while(aux->prox != NULL && aux->prox->termo.k > k){aux = aux->prox;}

    if(aux->prox == NULL || aux->prox->termo.k < k){return 0;}

    Lista aux2 = aux->prox;
    aux->prox = aux2->prox;
    free(aux2);
    (*lst)->info--;
    return 1;
}

/*Função: int tamanho(Lista lst, int *tam)
    Entrada: Lista lst, ponteiro para inteiro tam
    Pré-condição: Lista válida e não vazia
    Processo: Atribui a *tam o valor de info (quantidade de termos)
    Saída: 1 em caso de sucesso, 0 se a lista estiver vazia
    Pós-condição: Valor de tam atualizado com o tamanho da lista
*/
int tamanho(Lista lst, int *tam){
    if(lista_vazia(lst) == 1){return 0;}

    *tam = lst->info;
    return 1;
}

/*Função: int esvaziar_lista(Lista *lst)
    Entrada: Ponteiro para lista lst
    Pré-condição: Lista válida e não vazia
    Processo: Libera todos os nós a partir do primeiro termo, mantendo o nó cabeça
    Saída: 1 se a operação foi realizada, 0 se a lista já estava vazia
    Pós-condição: Lista esvaziada, mas ainda válida e reutilizável
*/
int esvaziar_lista(Lista *lst){
    if(lista_vazia(*lst) == 1){return 0;}

    Lista atual = (*lst)->prox;
    Lista temp;

    while(atual != NULL){
        temp = atual;
        atual = atual->prox;
        free(temp);
    }

    (*lst)->prox = NULL;
    (*lst)->info = 0;
    return 1;
}

/*Função: void imprime_lista(Lista lst)
    Entrada: Lista lst
    Pré-condição: Lista válida
    Processo: Percorre e imprime os termos do polinômio formatado (como 3x^2 + 2x - 1)
    Saída: Impressão na tela
    Pós-condição: Lista não é alterada
*/
void imprime_lista(Lista lst){
    if(lista_vazia(lst) == 1){printf("Polinomio vazio.\n");return;}

    Lista aux = lst->prox;
    int primeiro = 1;
    printf("P(x) = ");

    while (aux != NULL){
        int x = aux->termo.x;
        int k = aux->termo.k;

        if (x != 0){
            int abs_x = abs(x);

            if(!primeiro){printf(x > 0 ? " + " : " - ");}
            else{
                if (x < 0) printf("-");
                primeiro = 0;
            }

            if (k == 0){printf("%d", abs_x);}
            else if (k == 1){printf(abs_x != 1 ? "%dx" : "x", abs_x);}
            else{printf(abs_x != 1 ? "%dx^%d" : "x^%d", abs_x, k);}
        }
        aux = aux->prox;
    } printf("\n");
}

/*Função: void calcula(Lista lst, int valor)
    Entrada: Lista lst, valor para x
    Pré-condição: Lista válida
    Processo: Substitui o valor de x no polinômio e calcula o resultado, imprimindo cada termo e a soma final
    Saída: Impressão da expressão substituída e resultado
    Pós-condição: Lista não é alterada
*/
void calcula(Lista lst, int valor){
    if(lista_vazia(lst) == 1){printf("Polinomio vazio.\n");return;}

    Lista aux = lst->prox;
    int resultado = 0;
    int primeiro = 1;

    printf("P(%d) = ", valor);

    while (aux != NULL){
        int coef = aux->termo.x;
        int exp = aux->termo.k;

        if (coef != 0){
            if (!primeiro){printf(coef > 0 ? " + " : " - ");}
            else{
                if (coef < 0) printf("-");
                primeiro = 0;
            }

            int abs_coef = abs(coef);

            if (exp == 0){printf("%d", abs_coef);}
            else if (exp == 1){printf("%d*%d", abs_coef, valor);}
            else{printf("%d*%d^%d", abs_coef, valor, exp);}

            resultado += coef * pow(valor, exp);
        }aux = aux->prox;
    }printf(" = %d\n", resultado);
}






































