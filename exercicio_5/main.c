#include <stdio.h>
#include <stdlib.h>
#include "tad_circ.h"

void imprime_menu() {
    printf("\n--- TAD LISTA CIRCULAR DE CARACTERES ---\n");
    printf("1. Inserir no inicio\n");
    printf("2. Inserir no final\n");
    printf("3. Remover do final\n");
    printf("4. Remover elemento especifico\n");
    printf("5. Imprimir lista\n");
    printf("6. Verificar se identica a outra lista\n");
    printf("7. Esvaziar lista\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void imprime_lista(Lista lst) {
    printf("\nEstado da lista (Tamanho: %d): ", tamanho_lista(lst));
    if(lista_vazia(lst)) {
        printf("[VAZIA]\n");
        return;
    }

    printf("[ ");
    char c;
    for(int i = 1; get_elem_pos(lst, i, &c); i++) { //usando o proprio retorno da funcao como condicao de parada
        printf("%c ", c);
    }
    printf("]\n");
}


int main() {
    Lista lista_principal = cria_lista();
    int opcao;
    char char_temp;

    do {
        imprime_menu();
        scanf("%d", &opcao);
        while(getchar() != '\n'); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                printf("Digite o caractere para inserir no INICIO: ");
                scanf("%c", &char_temp);
                if(insere_inicio(&lista_principal, char_temp)) printf("Inserido com sucesso!\n");
                else printf("Falha na insercao.\n");
                break;

            case 2:
                printf("Digite o caractere para inserir no FINAL: ");
                scanf("%c", &char_temp);
                if(insere_elem(&lista_principal, char_temp)) printf("Inserido com sucesso!\n");
                else printf("Falha na insercao.\n");
                break;

            case 3:
                if(remove_fim(&lista_principal, &char_temp)) printf("Elemento '%c' removido do final.\n", char_temp);
                else printf("Falha ao remover. A lista esta vazia.\n");
                break;

            case 4:
                printf("Digite o caractere a ser removido: ");
                scanf("%c", &char_temp);
                if(remove_elem(&lista_principal, char_temp)) printf("Elemento '%c' removido.\n", char_temp);
                else printf("Falha ao remover. Elemento nao encontrado ou lista vazia.\n");
                break;

            case 5:
                imprime_lista(lista_principal);
                break;

            case 6:
                { // Criando variáveis locais
                    Lista lista_b = cria_lista();
                    printf("\n-- Teste de Igualdade --\n");
                    printf("Vamos criar uma segunda lista para comparar.\n");
                    char resp;
                    do {
                        printf("Digite um char para a Lista B (ou '0' para parar): ");
                        //o espaco no inicio do " %c" eh pra desprezar o "\n", ajuda na limpeza do buffer
                        scanf(" %c", &resp);
                        if (resp != '0') insere_elem(&lista_b, resp);
                    } while (resp != '0');

                    printf("\nLista Principal Atual:");
                    imprime_lista(lista_principal);
                    printf("Lista B criada para teste:");
                    imprime_lista(lista_b);

                    if(iguais(lista_principal, lista_b)) printf("\nResultado: As listas SAO identicas.\n");
                    else printf("\nResultado: As listas NAO SAO identicas.\n");

                    //apaga lista usa o esvaziar lista, isto eh, libera memoria de cada no, depois do endereco da lista
                    apaga_lista(&lista_b);
                }
                break;

            case 7:
                if(esvazia_lista(&lista_principal)) printf("Lista esvaziada.\n");
                else printf("A lista ja estava vazia.\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }

    } while (opcao != 0);

    apaga_lista(&lista_principal);
    return 0;
}
