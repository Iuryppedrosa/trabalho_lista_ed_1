#include <stdio.h>
#include <string.h>
#include "lista_ordenada_estatica_sequencial_string.h"

void exibir_menu() {
    printf("1. Criar nova lista\n");
    printf("2. Verificar se a lista esta cheia\n");
    printf("3. Verificar se a lista esta vazia\n");
    printf("4. Inserir elemento ordenado\n");
    printf("5. Remover elemento ordenado\n");
    printf("6. Remover todas as ocorrencias\n");
    printf("7. Obter elemento por posicao\n");
    printf("8. Remover elemento por posicao\n");
    printf("9. Obter tamanho da lista\n");
    printf("10. Intercalar com outra lista\n");
    printf("11. Esvaziar lista\n");
    printf("12. Apagar lista\n");
    printf("13. Sair\n");
    printf("Escolha uma opcao: ");
}

void exibir_lista(Lista l) {
    char palavra[20];
    if (l == NULL || lista_vazia(l)) {
        printf("Lista vazia ou nao inicializada.\n");
        return;
    }
    printf("Conteudo da lista: ");
    for (int i = 1; i <= tamanho_lista(l); i++) {
        if (get_elem_pos(l, i, palavra)) {
            printf("%s ", palavra);
        }
    }
    printf("\n");
}

int main() {
    Lista l = NULL, l2 = NULL, l3 = NULL;
    char palavra[20];
    int opcao, posicao, resultado;

    while (1) {
        exibir_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                if (l != NULL) {
                    apaga_lista(&l);
                }
                l = cria_lista();
                printf(l != NULL ? "Sucesso: Lista criada.\n" : "Falha: Erro ao criar lista.\n");
                break;

            case 2:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    resultado = lista_cheia(l);
                    printf(resultado ? "Sucesso: Lista esta cheia.\n" : "Sucesso: Lista nao esta cheia.\n");
                }
                break;

            case 3:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    resultado = lista_vazia(l);
                    printf(resultado ? "Sucesso: Lista esta vazia.\n" : "Sucesso: Lista nao esta vazia.\n");
                }
                break;

            case 4:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    printf("Digite a palavra (max. 19 caracteres): ");
                    fgets(palavra, 20, stdin);
                    palavra[strcspn(palavra, "\n")] = '\0';
                    resultado = insere_elem_ord(l, palavra);
                    if (resultado) {
                        printf("Sucesso: Palavra '%s' inserida.\n", palavra);
                    } else {
                        printf("Falha: Nao foi possivel inserir '%s' (lista cheia ou palavra invalida).\n", palavra);
                    }
                    exibir_lista(l);
                }
                break;

            case 5:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    printf("Digite a palavra a remover: ");
                    fgets(palavra, 20, stdin);
                    palavra[strcspn(palavra, "\n")] = '\0';
                    resultado = remove_elem_ord(l, palavra);
                    if (resultado) {
                        printf("Sucesso: Palavra '%s' removida.\n", palavra);
                    } else {
                        printf("Falha: Palavra '%s' nao encontrada ou lista vazia.\n", palavra);
                    }
                    exibir_lista(l);
                }
                break;

            case 6:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    printf("Digite a palavra a remover: ");
                    fgets(palavra, 20, stdin);
                    palavra[strcspn(palavra, "\n")] = '\0';
                    resultado = remove_todas(l, palavra);
                    if (resultado > 0) {
                        printf("Sucesso: %d ocorrencia(s) de '%s' removida(s).\n", resultado, palavra);
                    } else {
                        printf("Falha: Palavra '%s' nao encontrada ou lista vazia.\n", palavra);
                    }
                    exibir_lista(l);
                }
                break;

            case 7:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    printf("Digite a posicao: ");
                    scanf("%d", &posicao);
                    getchar();
                    resultado = get_elem_pos(l, posicao, palavra);
                    if (resultado) {
                        printf("Sucesso: Elemento na posicao %d: %s\n", posicao, palavra);
                    } else {
                        printf("Falha: Posicao %d invalida ou lista vazia.\n", posicao);
                    }
                }
                break;

            case 8:
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    printf("Digite a posicao: ");
                    scanf("%d", &posicao);
                    getchar();
                    resultado = remove_posicao(l, posicao, palavra);
                    if (resultado) {
                        printf("Sucesso: Elemento '%s' removido da posicao %d.\n", palavra, posicao);
                        exibir_lista(l);
                    } else {
                        printf("Falha: Posicao %d invalida ou lista vazia.\n", posicao);
                    }
                }
                break;

            case 9: // Obter tamanho da lista
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    resultado = tamanho_lista(l);
                    printf("Sucesso: Tamanho da lista: %d\n", resultado);
                }
                break;

            case 10: // Intercalar com outra lista
                if (l == NULL) {
                    printf("Falha: Lista principal nao inicializada.\n");
                } else {
                    if (l2 == NULL) {
                        l2 = cria_lista();
                        if (l2 == NULL) {
                            printf("Falha: Erro ao criar segunda lista.\n");
                            break;
                        }
                        printf("Segunda lista criada. Insira palavras (digite 'fim' para terminar):\n");
                        while (1) {
                            fgets(palavra, 20, stdin);
                            palavra[strcspn(palavra, "\n")] = '\0';
                            if (strcmp(palavra, "fim") == 0) break;
                            resultado = insere_elem_ord(l2, palavra);
                            if (!resultado) {
                                printf("Falha: Nao foi possivel inserir '%s' na segunda lista.\n", palavra);
                            }
                        }
                    }
                    printf("Lista principal: ");
                    exibir_lista(l);
                    printf("Segunda lista: ");
                    exibir_lista(l2);
                    l3 = intercala(l, l2);
                    if (l3 != NULL) {
                        printf("Sucesso: Lista intercalada criada.\n");
                        printf("Lista intercalada: ");
                        exibir_lista(l3);
                        apaga_lista(&l3);
                    } else {
                        printf("Falha: Erro ao intercalar listas.\n");
                    }
                }
                break;

            case 11: // Esvaziar lista
                if (l == NULL) {
                    printf("Falha: Lista nao inicializada.\n");
                } else {
                    resultado = esvazia_lista(l);
                    if (resultado) {
                        printf("Sucesso: Lista esvaziada.\n");
                        exibir_lista(l);
                    } else {
                        printf("Falha: Lista ja esta vazia.\n");
                    }
                }
                break;

            case 12: // Apagar lista
                if (l == NULL) {
                    printf("Sucesso: Lista ja nao existe.\n");
                } else {
                    resultado = apaga_lista(&l);
                    if (resultado) {
                        printf("Sucesso: Lista apagada.\n");
                    } else {
                        printf("Falha: Erro ao apagar lista.\n");
                    }
                }
                if (l2 != NULL) {
                    apaga_lista(&l2);
                    printf("Sucesso: Segunda lista apagada.\n");
                }
                break;

            case 13: // Sair
                if (l != NULL) apaga_lista(&l);
                if (l2 != NULL) apaga_lista(&l2);
                printf("Sucesso: Programa encerrado.\n");
                return 0;

            default:
                printf("Falha: Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
