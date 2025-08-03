#include <stdio.h>
#include <stdlib.h>
#include "DinEnCab.h"

int main(){
    Lista lista;
    int aux, x, k, tam = 0, valor;

    printf("Deseja criar um polinomio?\n");
    printf("(1)Sim. (2)Nao, sair do programa.\n");
    printf("Escolha: ");
    scanf("%d", &aux);

    if(aux == 2){
        return 0;
    }else{
        lista = cria_lista();
        do{
            printf("\n");
            printf(">> Polinomio - Menu <<\n");
            printf("(1)Inserir termo\n");
            printf("(2)Remover termo associado a k-essima potencia\n");
            printf("(3)Tamanho do polinomio\n");
            printf("(4)Reiniciar polinomio\n");
            printf("(5)Imprimir polinomio\n");
            printf("(6)Calcular polinomio\n");
            printf("(7)Sair do programa\n");
            printf("Escolha: ");
            scanf("%d", &aux);

            switch(aux){
                case 1:
                    printf("Insira o coeficiente: ");
                    scanf("%d", &x);
                    printf("Insira o expoente: ");
                    scanf("%d", &k);
                    if(insere_ord(&lista, x, k)){
                        printf("Termo inserido.\n");
                    }else{
                        printf("Erro ao inserir");
                    }
                    break;
                case 2:
                    printf("Insira a k-essima potencia: ");
                    scanf("%d", &k);
                    if(remove_ord(&lista, k)){
                        printf("Termo removido.\n");
                    }else{
                        printf("Erro ao remover termo associado a k-essima potencia");
                    }
                    break;
                case 3:
                    if(tamanho(lista, &tam)){
                        printf("O numero de termos do polinomio eh %d.\n", tam);
                    }else{
                        printf("Erro ao calcular o tamanho do polinomio");
                    }
                    break;
                case 4:
                    if(esvaziar_lista(&lista)){
                        printf("Polinomio esvaziado.\n");
                    }else{
                        printf("Polinomio ja esta vazio.\n");
                    }
                    break;
                case 5:
                    imprime_lista(lista);
                    break;
                case 6:
                    printf("Insira um valor de x de P(x): ");
                    scanf("%d", &valor);
                    calcula(lista, valor);
                    break;
                case 7: break;
                default:
                printf("Opçao invalida.\n");
            }printf("\n");
        }while(aux != 7);
    }

    system("pause");
    return 0;
}
