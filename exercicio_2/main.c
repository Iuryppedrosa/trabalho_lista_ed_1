#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_estatic.h"
#define MAX_ALUNOS 15

void imprime_menu() {
    printf("\n--- MENU DE GERENCIAMENTO DE ALUNOS ---\n");
    printf("1. Inserir Aluno (no final)\n");
    printf("2. Inserir Aluno (em posicao especifica)\n");
    printf("3. Imprimir Lista Principal\n");
    printf("4. Remover Aluno (por matricula)\n");
    printf("5. Remover Aluno com Menor Matricula\n");
    printf("6. Remover Alunos por Excesso de Faltas\n");
    printf("7. Concatenar Duas Listas (Interativo)\n");
    printf("8. Esvaziar Lista Principal\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void ler_aluno(Aluno *aluno) {
    printf("Digite a matricula: ");
    scanf("%9s", aluno->matricula);
    printf("Digite a nota final: ");
    scanf("%f", &aluno->nota_final);
    printf("Digite o numero de faltas: ");
    scanf("%d", &aluno->faltas);
    printf("Digite o status (1-Aprovado, 0-Reprovado): ");
    scanf("%d", &aluno->status);
}

void imprime_aluno(Aluno aluno) {
    printf("  Matricula: %-10s | Nota: %5.2f | Faltas: %2d | Status: %s\n",
           aluno.matricula, aluno.nota_final, aluno.faltas,
           (aluno.status == 1) ? "Aprovado" : "Reprovado");
}

void imprime_lista(Lista lst, const char* nome_lista){
    printf("\n-- Conteudo da %s (Tamanho: %d) --\n", nome_lista, tamanho_lista(lst));
    if (lista_vazia(lst)) {
        printf("A lista esta vazia.\n");
    } else {
        Aluno aluno_temp;
        for (int i = 1; i <= tamanho_lista(lst); i++) {
            get_elem_pos(lst, i, &aluno_temp);
            imprime_aluno(aluno_temp);
        }
    }
}


int main() {
    Lista lista_principal = cria_lista();
    Aluno aluno_temp;
    char matricula_temp[10];
    int opcao, qtd, pos;

    if (lista_principal == NULL) {
        printf("Erro critico: Nao foi possivel alocar memoria para a lista.\n");
        return 1;
    }

    do {
        imprime_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // Inserir no final
                printf("\n-- Inserir Aluno (Final) --\n");
                if (lista_cheia(lista_principal)) {
                    printf("Erro: A lista esta cheia!\n");
                } else {
                    ler_aluno(&aluno_temp);
                    if (insere_elem(lista_principal, aluno_temp)) printf("Aluno inserido com sucesso!\n");
                    else printf("Falha ao inserir aluno.\n");
                }
                break;

            case 2: // Inserir em posição
                printf("\n-- Inserir Aluno (Posicao) --\n");
                if (lista_cheia(lista_principal)) {
                    printf("Erro: A lista esta cheia!\n");
                } else {
                    printf("Digite a posicao para inserir (de 1 a %d): ", tamanho_lista(lista_principal) + 1);
                    scanf("%d", &pos);
                    ler_aluno(&aluno_temp);
                    if (insere_elem_pos(lista_principal, aluno_temp, pos)) printf("Aluno inserido com sucesso na posicao %d!\n", pos);
                    else printf("Falha ao inserir: posicao invalida ou lista cheia.\n");
                }
                break;

            case 3: // Imprimir
                imprime_lista(lista_principal, "Lista Principal");
                break;

            case 4: // Remover por matrícula
                printf("\n-- Remover Aluno por Matricula --\n");
                if(lista_vazia(lista_principal)) {
                    printf("A lista ja esta vazia.\n");
                } else {
                    printf("Digite a matricula a ser removida: ");
                    scanf("%9s", matricula_temp);
                    if (remove_elem(lista_principal, matricula_temp)) printf("Aluno removido com sucesso!\n");
                    else printf("Erro: Aluno com a matricula '%s' nao encontrado.\n", matricula_temp);
                }
                break;

            case 5: // Remover menor
                printf("\n-- Remover Aluno com Menor Matricula --\n");
                if (remove_menor(lista_principal, &aluno_temp)) {
                    printf("Aluno removido com sucesso:\n");
                    imprime_aluno(aluno_temp);
                } else {
                    printf("Erro: Nao foi possivel remover. A lista pode estar vazia.\n");
                }
                break;

            case 6: // Remover faltosos
                printf("\n-- Remover Alunos Faltosos --\n");
                printf("Remover alunos com mais de quantas faltas? ");
                scanf("%d", &qtd);
                int removidos = remove_faltosos(lista_principal, qtd);
                printf("%d aluno(s) removido(s).\n", removidos);
                break;

            case 7: // Concatenar
                printf("\n-- Concatenar Duas Listas (Interativo) --\n");
                Lista lista_a = cria_lista();
                Lista lista_b = cria_lista();

                if(!lista_a || !lista_b){
                    printf("Erro de alocacao para as listas auxiliares.\n");
                    if(lista_a) apagar_lista(&lista_a);
                    if(lista_b) apagar_lista(&lista_b);
                    break;
                }

                // Preencher Lista A
                printf("Quantos alunos deseja inserir na Lista A? ");
                scanf("%d", &qtd);
                for(int i=0; i<qtd; i++){
                    printf("\nDados do Aluno %d da Lista A:\n", i+1);
                    ler_aluno(&aluno_temp);
                    insere_elem(lista_a, aluno_temp);
                }

                // Preencher Lista B
                printf("\nQuantos alunos deseja inserir na Lista B? ");
                scanf("%d", &qtd);
                if(tamanho_lista(lista_a) + qtd > MAX_ALUNOS){
                    printf("Erro: A soma das listas excede a capacidade maxima de %d alunos.\n", MAX_ALUNOS);
                } else {
                    for(int i=0; i<qtd; i++){
                        printf("\nDados do Aluno %d da Lista B:\n", i+1);
                        ler_aluno(&aluno_temp);
                        insere_elem(lista_b, aluno_temp);
                    }
                }

                imprime_lista(lista_a, "Lista A");
                imprime_lista(lista_b, "Lista B");

                Lista lista_c = concatena(lista_a, lista_b);

                if(lista_c) {
                    imprime_lista(lista_c, "Lista C (Concatenada)");
                    apagar_lista(&lista_c); // Libera a memória da lista nova
                } else {
                    printf("Erro: Nao foi possivel concatenar as listas.\n");
                }
                apagar_lista(&lista_a);
                apagar_lista(&lista_b);
                break;

            case 8: // Esvaziar
                 printf("\n-- Esvaziando a Lista Principal --\n");
                 if(esvaziar_lista(lista_principal)) printf("Lista esvaziada com sucesso.\n");
                 else printf("Nao foi possivel esvaziar a lista (ja estava vazia?).\n");
                 break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    apagar_lista(&lista_principal);
    return 0;
}
