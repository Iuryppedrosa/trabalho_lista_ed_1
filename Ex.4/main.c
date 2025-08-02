#include <stdio.h>
#include <stdlib.h>
#include "DiEnSim.h"

int main(){
    Lista lista1, lista2, lista3;
    int opcao, criada1 = 0, criada2 = 0, criada3 = 0, tam1 = 0, tam2 = 0;
    float elem, maior1 = 0, maior2 = 0;

    do{
        printf("::: LISTA 1 - MENU :::\n");
        printf("(1) Cria Lista\n");
        printf("(2) Insere Elemento\n");
        printf("(3) Remove Elemento\n");
        printf("(4) Esvazia Lista\n");
        printf("(5) Imprime Lista\n");
        printf("(6) Tamanho Lista\n");
        printf("(7) Remove e Informa Maior Elemento\n");
        printf("(8) Lista 2 - Menu\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(!criada1){
                    lista1 = cria_lista();
                    criada1 = 1;
                    printf("Lista criada com sucesso.\n");
                } else {
                    printf("A lista ja foi criada.\n");
                }
                break;
            case 2:
                if(!criada1){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                printf("Informe o elemento: ");
                scanf("%f", &elem);
                if(insere_elem(&lista1, elem)){
                    printf("Elemento inserido.\n");
                } else {
                    printf("Erro ao inserir.\n");
                }
                break;
            case 3:
                if(!criada1){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                printf("Informe o elemento: ");
                scanf("%f", &elem);
                if(remove_elem(&lista1, elem)){
                    printf("Elemento removido.\n");
                } else {
                    printf("Erro ao remover.\n");
                }
                break;
            case 4:
                if(!criada1){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(esvazia_lista(&lista1)){
                    printf("Lista esvaziada.\n");
                }else{
                    printf("Erro ao esvaziar lista.\n");
                }
                break;
            case 5:
                if(!criada1){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(lista_vazia(lista1)){
                    printf("Insira os elementos primeiro.\n");
                }
                else{
                    imprime_lista(lista1);
                }
                break;
            case 6:
                if(!criada1){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(tamanho_lista(&lista1, &tam1)){
                    printf("O tamanho da lista eh: %d\n", tam1);
                }else{
                    printf("Erro ao calcular tamanho da lista.\n");
                }
                break;
            case 7:
                if(!criada1){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(remove_maior(&lista1, &maior1)){
                    printf("O maior elemento eh: %.2f\n", maior1);
                }else{
                    printf("Erro ao remover o maior elemento.\n");
                }
                break;
            case 8: break;
            default:
                printf("Opção invalida.\n");
        }
        printf("\n");
    } while(opcao != 8);

    do{
        printf("::: LISTA 2 - MENU :::\n");
        printf("(1) Cria Lista\n");
        printf("(2) Insere Elemento\n");
        printf("(3) Remove Elemento\n");
        printf("(4) Esvazia Lista\n");
        printf("(5) Imprime Lista\n");
        printf("(6) Tamanho Lista\n");
        printf("(7) Remove e Informa Maior Elemento\n");
        printf("(8) Lista 3 (Lista 1 e 2 Intercalada) - Menu\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(!criada2){
                    lista2 = cria_lista();
                    criada2 = 1;
                    printf("Lista criada com sucesso.\n");
                } else {
                    printf("A lista ja foi criada.\n");
                }
                break;
            case 2:
                if(!criada2){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                printf("Informe o elemento: ");
                scanf("%f", &elem);
                if(insere_elem(&lista2, elem)){
                    printf("Elemento inserido.\n");
                } else {
                    printf("Erro ao inserir.\n");
                }
                break;
            case 3:
                if(!criada2){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                printf("Informe o elemento: ");
                scanf("%f", &elem);
                if(remove_elem(&lista2, elem)){
                    printf("Elemento removido.\n");
                } else {
                    printf("Erro ao remover.\n");
                }
                break;
            case 4:
                if(!criada2){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(esvazia_lista(&lista2)){
                    printf("Lista esvaziada.\n");
                }else{
                    printf("Erro ao esvaziar lista.\n");
                }
                break;
            case 5:
                if(!criada2){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(lista_vazia(lista2)){
                    printf("Insira os elementos primeiro.\n");
                }
                else{
                    imprime_lista(lista2);
                };
            case 6:
                if(!criada2){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(tamanho_lista(&lista2, &tam2)){
                    printf("O tamanho da lista eh: %d\n", tam2);
                }else{
                    printf("Erro ao calcular tamanho da lista.\n");
                }
                break;
            case 7:
                 if(!criada2){
                    printf("Crie a lista primeiro.\n");
                    break;
                }
                if(remove_maior(&lista2, &maior2)){
                    printf("O maior elemento eh: %.2f\n", maior2);
                }else{
                    printf("Erro ao remover o maior elemento.\n");
                }
                break;;
            case 8: break;
            default:
                printf("Opção invalida.\n");
        }
        printf("\n");
    } while(opcao != 8);

    printf(".:: VERIFICANDO SE LISTA 1 E LISTA 2 EXISTEM ::.\n");
    if(criada1 == 0 && criada2 == 0){
        printf("Nao eh possivel intercalar, lista 1 e 2 nao existem!\n");
        return 0;
    }else{
         printf("Eh possivel intercalar!\n");
         printf("\n");
        do{
            printf(">>> LISTA 3 (LISTA 1 E 2 INTERCALADA) <<<\n");
            printf("(1) Cria Lista\n");
            printf("(2) Intercala Listas\n");
            printf("(3) Imprime Lista\n");
            printf("(4) Sair do Programa\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch(opcao){
                case 1:
                    if(!criada3){
                        lista3 = cria_lista();
                        criada3 = 1;
                        printf("Lista criada com sucesso.\n");
                    } else {
                        printf("A lista ja foi criada.\n");
                    }
                    break;
                case 2:
                    if(!criada3){
                        printf("Crie a lista primeiro.\n");
                        break;
                    }
                    if(intercala_listas(lista1, lista2, &lista3)){
                        printf("Listas intercaladas.\n");
                    }else{
                        printf("Erro ao intercalar as listas, lista 1 e lista 2 sao vazias.\n");
                        return 0;
                    }
                    break;
                case 3:
                    if(!criada3){
                        printf("Crie a lista primeiro.\n");
                        break;
                    }
                    if(lista_vazia(lista3)){
                        printf("Intercale as listas primeiro.\n");
                    }
                    else{
                        imprime_lista(lista3);
                        return 0;
                    }
                    break;
                case 4: break;
                default:
                    printf("Opção invalida.\n");
            }
            printf("\n");
        }while(opcao != 4);
    }

    system("pause");
    return 0;
}

