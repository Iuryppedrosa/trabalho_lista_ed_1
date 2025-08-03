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

/*Fun��o: Lista cria_lista()
    Entrada: Nenhuma
    Pr�-condi��o: Nenhuma
    Processo: Aloca dinamicamente uma lista encadeada com n� cabe�a, inicializa ponteiro para NULL e contador info com 0.
    Sa�da: Ponteiro para a lista criada
    P�s-condi��o: Lista vazia com n� cabe�a criada com sucesso.
*/
Lista cria_lista(){
    Lista cab;
    cab = (Lista)malloc(sizeof(struct no));

    if(cab != NULL){
        cab->prox = NULL;
        cab->info = 0;
    }return cab;
}

/*Fun��o: int lista_vazia(Lista lst)
    Entrada: Lista lst
    Pr�-condi��o: Lista deve ter sido criada anteriormente
    Processo: Verifica se o campo prox do n� cabe�a � NULL
    Sa�da: 1 se estiver vazia, 0 caso contr�rio
    P�s-condi��o: Lista n�o � alterada
*/
int lista_vazia(Lista lst){
    if(lst->prox == NULL){return 1;}
    else{return 0;}
}

/*Fun��o: int insere_ord(Lista *lst, int x, int k)
    Entrada: Ponteiro para lista lst, coeficiente x e expoente k
    Pr�-condi��o: Lista deve estar alocada e v�lida
    Processo: Insere o termo de forma decrescente por k; se j� existir termo com o mesmo k, soma os coeficientes. Se a soma der zero, remove o termo.
    Sa�da: 1 se inserido com sucesso, 0 em caso de falha (ex: falta de mem�ria)
    P�s-condi��o: Lista cont�m o novo termo inserido de forma ordenada (ou atualizado)
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

/*Fun��o: int remove_ord(Lista *lst, int k)
    Entrada: Ponteiro para lista lst, expoente k
    Pr�-condi��o: Lista v�lida e n�o vazia
    Processo: Procura e remove o n� cujo expoente seja igual a k
    Sa�da: 1 se removido com sucesso, 0 se o termo n�o existir
    P�s-condi��o: Lista sem o termo com expoente k, se ele existia
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

/*Fun��o: int tamanho(Lista lst, int *tam)
    Entrada: Lista lst, ponteiro para inteiro tam
    Pr�-condi��o: Lista v�lida e n�o vazia
    Processo: Atribui a *tam o valor de info (quantidade de termos)
    Sa�da: 1 em caso de sucesso, 0 se a lista estiver vazia
    P�s-condi��o: Valor de tam atualizado com o tamanho da lista
*/
int tamanho(Lista lst, int *tam){
    if(lista_vazia(lst) == 1){return 0;}

    *tam = lst->info;
    return 1;
}

/*Fun��o: int esvaziar_lista(Lista *lst)
    Entrada: Ponteiro para lista lst
    Pr�-condi��o: Lista v�lida e n�o vazia
    Processo: Libera todos os n�s a partir do primeiro termo, mantendo o n� cabe�a
    Sa�da: 1 se a opera��o foi realizada, 0 se a lista j� estava vazia
    P�s-condi��o: Lista esvaziada, mas ainda v�lida e reutiliz�vel
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

/*Fun��o: void imprime_lista(Lista lst)
    Entrada: Lista lst
    Pr�-condi��o: Lista v�lida
    Processo: Percorre e imprime os termos do polin�mio formatado (como 3x^2 + 2x - 1)
    Sa�da: Impress�o na tela
    P�s-condi��o: Lista n�o � alterada
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

/*Fun��o: void calcula(Lista lst, int valor)
    Entrada: Lista lst, valor para x
    Pr�-condi��o: Lista v�lida
    Processo: Substitui o valor de x no polin�mio e calcula o resultado, imprimindo cada termo e a soma final
    Sa�da: Impress�o da express�o substitu�da e resultado
    P�s-condi��o: Lista n�o � alterada
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






































