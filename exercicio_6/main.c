#include <stdio.h>
#include <stdlib.h>
#include "lista_dinamica_duplamente_encad.h"

void exibir_lista(Lista l) {
    int *vetor = veja_lista(l);
    int tam = tamanho_lista(l);
    printf("Lista: ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    free(vetor);
}

int main() {
    Lista l = cria_lista();
    int opcao, elem, pos, resultado;
    int *vetor;

    do {
        printf("\n=== Menu de Operacoes ===\n");
        printf("1. Criar nova lista\n");
        printf("2. Verificar se lista esta vazia\n");
        printf("3. Inserir elemento\n");
        printf("4. Remover elemento\n");
        printf("5. Esvaziar lista\n");
        printf("6. Obter tamanho da lista\n");
        printf("7. Visualizar lista\n");
        printf("8. Obter elemento por posicao\n");
        printf("9. Remover todos os elementos pares\n");
        printf("10. Remover maior elemento\n");
        printf("11. Inserir elemento em posicao\n");
        printf("12. Criar lista invertida\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                l = cria_lista();
                printf("Nova lista criada!\n");
                break;

            case 2:
                if (lista_vazia(l) == 1) {
                    printf("A lista esta vazia!\n");
                } else {
                    printf("A lista nao esta vazia!\n");
                }
                break;

            case 3:
                printf("Digite o elemento a inserir: ");
                scanf("%d", &elem);
                if (insere_elemento(&l, elem) == 1) {
                    printf("Elemento %d inserido com sucesso!\n", elem);
                } else {
                    printf("Falha ao inserir elemento!\n");
                }
                exibir_lista(l);
                break;

            case 4:
                printf("Digite o elemento a remover: ");
                scanf("%d", &elem);
                if (remove_elemento(&l, elem) == 1) {
                    printf("Elemento %d removido com sucesso!\n", elem);
                } else {
                    printf("Elemento nao encontrado ou lista vazia!\n");
                }
                exibir_lista(l);
                break;

            case 5:
                if (esvazia_lista(&l) == 1) {
                    printf("Lista esvaziada com sucesso!\n");
                } else {
                    printf("Lista ja esta vazia!\n");
                }
                exibir_lista(l);
                break;

            case 6:
                printf("Tamanho da lista: %d\n", tamanho_lista(l));
                break;

            case 7:
                exibir_lista(l);
                break;

            case 8:
                printf("Digite a posicao (comecando em 1): ");
                scanf("%d", &pos);
                if (get_elem_posicao(l, pos, &elem) == 1) {
                    printf("Elemento na posicao %d: %d\n", pos, elem);
                } else {
                    printf("Posicao invalida ou lista vazia!\n");
                }
                break;

            case 9:
                if (remove_pares(&l) == 1) {
                    printf("Elementos pares removidos com sucesso!\n");
                } else {
                    printf("Lista vazia ou sem elementos pares!\n");
                }
                exibir_lista(l);
                break;

            case 10:
                if (remove_maior(&l, &elem) == 1) {
                    printf("Maior elemento removido: %d\n", elem);
                } else {
                    printf("Lista vazia!\n");
                }
                exibir_lista(l);
                break;

            case 11:
                printf("Digite o elemento a inserir: ");
                scanf("%d", &elem);
                printf("Digite a posicao (comecando em 1): ");
                scanf("%d", &pos);
                if (insere_posicao(&l, elem, pos) == 1) {
                    printf("Elemento %d inserido na posicao %d!\n", elem, pos);
                } else {
                    printf("Posicao invalida ou falha na insercao!\n");
                }
                exibir_lista(l);
                break;

            case 12:
                {
                    Lista l2 = inverte_lista(l);
                    printf("Lista original: ");
                    exibir_lista(l);
                    printf("Lista invertida: ");
                    exibir_lista(l2);
                    esvazia_lista(&l2);
                }
                break;

            case 0:
                printf("Saindo...\n");
                esvazia_lista(&l);
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
