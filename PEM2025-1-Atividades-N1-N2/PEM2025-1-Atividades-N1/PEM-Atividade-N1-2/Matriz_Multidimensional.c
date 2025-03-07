/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Sistema de controle de estoque   *
* para empresa atacadista utilizando matriz 3D para      *
* gerenciar produtos em 3 ruas e 10 gondolas, permitindo *
* estocagem, retirada e visualizacao dos produtos.       *
* Data - 07/03/2024                                      *
* Autor: Alexandre Magno Prezotto Junior                 *
*--------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RUAS 3
#define MAX_GONDOLAS 10
#define MAX_CODIGO 10

int main() {
    // matriz pra guardar os codigos dos produtos
    char estoque_codigo[MAX_RUAS][MAX_GONDOLAS][MAX_CODIGO];
    // matriz pra guardar as quantidades dos produtos
    int estoque_quantidade[MAX_RUAS][MAX_GONDOLAS];

    // inicializando as matrizes com valores vazios
    int i, j;
    for (i = 0; i < MAX_RUAS; i++) {
        for (j = 0; j < MAX_GONDOLAS; j++) {
            estoque_codigo[i][j][0] = '\0';  // string vazia
            estoque_quantidade[i][j] = 0;    // quantidade zerada
        }
    }

    int opcao;
    char codigo[MAX_CODIGO];
    int quantidade, rua_idx, gondola_idx;
    int encontrado, posicao_vazia;
    char rua_letra;
    int c;

    do {
        // menu principal do sistema
        printf("\n===== SISTEMA DE CONTROLE DE ESTOQUE =====\n");
        printf("1. Estocar produto\n");
        printf("2. Retirar produto\n");
        printf("3. Visualizar estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // limpa o buffer pra nao dar problema depois
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1: // Estocar produto
                printf("\n=== ESTOCAGEM DE PRODUTO ===\n");
                printf("Digite o código do produto: ");
                scanf("%s", codigo);
                while ((c = getchar()) != '\n' && c != EOF);

                printf("Digite a quantidade a ser estocada: ");
                scanf("%d", &quantidade);
                while ((c = getchar()) != '\n' && c != EOF);

                if (quantidade <= 0) {
                    printf("Quantidade inválida!\n");
                    break;
                }

                // ve se o produto ja ta no estoque
                encontrado = 0;
                for (i = 0; i < MAX_RUAS && !encontrado; i++) {
                    for (j = 0; j < MAX_GONDOLAS && !encontrado; j++) {
                        if (strcmp(estoque_codigo[i][j], codigo) == 0) {
                            rua_idx = i;
                            gondola_idx = j;
                            encontrado = 1;
                        }
                    }
                }

                if (encontrado) {
                    // produto ja existe, so aumenta a quantidade
                    estoque_quantidade[rua_idx][gondola_idx] += quantidade;

                    // pega a letra da rua A, B ou C
                    if (rua_idx == 0) rua_letra = 'A';
                    else if (rua_idx == 1) rua_letra = 'B';
                    else rua_letra = 'C';

                    printf("\nProduto %s adicionado com sucesso!\n", codigo);
                    printf("Local: Rua %c, Gôndola %d\n", rua_letra, gondola_idx + 1);
                    printf("Quantidade atual: %d\n", estoque_quantidade[rua_idx][gondola_idx]);
                } else {
                    // produto novo, precisa achar um lugar vazio
                    posicao_vazia = 0;
                    for (i = 0; i < MAX_RUAS && !posicao_vazia; i++) {
                        for (j = 0; j < MAX_GONDOLAS && !posicao_vazia; j++) {
                            if (strlen(estoque_codigo[i][j]) == 0) {
                                rua_idx = i;
                                gondola_idx = j;
                                posicao_vazia = 1;
                            }
                        }
                    }

                    if (posicao_vazia) {
                        // coloca o produto e quantidade no lugar vazio
                        strcpy(estoque_codigo[rua_idx][gondola_idx], codigo);
                        estoque_quantidade[rua_idx][gondola_idx] = quantidade;

                        // pega a letra da rua
                        if (rua_idx == 0) rua_letra = 'A';
                        else if (rua_idx == 1) rua_letra = 'B';
                        else rua_letra = 'C';

                        printf("\nProduto %s adicionado com sucesso!\n", codigo);
                        printf("Local: Rua %c, Gôndola %d\n", rua_letra, gondola_idx + 1);
                        printf("Quantidade atual: %d\n", estoque_quantidade[rua_idx][gondola_idx]);
                    } else {
                        printf("\nERRO: Armazém cheio! Não é possível adicionar um novo produto.\n");
                    }
                }
                break;

            case 2: // Retirar produto
                printf("\n=== RETIRADA DE PRODUTO ===\n");
                printf("Digite o código do produto: ");
                scanf("%s", codigo);
                while ((c = getchar()) != '\n' && c != EOF);

                // procura o produto no estoque
                encontrado = 0;
                for (i = 0; i < MAX_RUAS && !encontrado; i++) {
                    for (j = 0; j < MAX_GONDOLAS && !encontrado; j++) {
                        if (strcmp(estoque_codigo[i][j], codigo) == 0) {
                            rua_idx = i;
                            gondola_idx = j;
                            encontrado = 1;
                        }
                    }
                }

                if (encontrado) {
                    // produto encontrado, ve se tem quantidade suficiente
                    if (estoque_quantidade[rua_idx][gondola_idx] > 0) {
                        printf("Quantidade disponível: %d\n", estoque_quantidade[rua_idx][gondola_idx]);
                        printf("Digite a quantidade a ser retirada: ");
                        scanf("%d", &quantidade);
                        while ((c = getchar()) != '\n' && c != EOF);

                        if (quantidade <= 0) {
                            printf("Quantidade inválida!\n");
                        } else if (quantidade > estoque_quantidade[rua_idx][gondola_idx]) {
                            printf("Quantidade insuficiente em estoque!\n");
                        } else {
                            estoque_quantidade[rua_idx][gondola_idx] -= quantidade;

                            // pega a letra da rua
                            if (rua_idx == 0) rua_letra = 'A';
                            else if (rua_idx == 1) rua_letra = 'B';
                            else rua_letra = 'C';

                            printf("\nProduto %s retirado com sucesso!\n", codigo);
                            printf("Local: Rua %c, Gôndola %d\n", rua_letra, gondola_idx + 1);
                            printf("Quantidade restante: %d\n", estoque_quantidade[rua_idx][gondola_idx]);
                        }
                    } else {
                        printf("Estoque esgotado para o produto %s!\n", codigo);
                    }
                } else {
                    printf("Produto %s não encontrado no estoque!\n", codigo);
                }
                break;

            case 3: // Visualizar estoque
                printf("\n=== VISUALIZAÇÃO DO ESTOQUE ===\n");
                printf("%-10s %-10s %-10s %-10s\n", "Rua", "Gôndola", "Código", "Quantidade");
                printf("------------------------------------------\n");

                for (i = 0; i < MAX_RUAS; i++) {
                    if (i == 0) rua_letra = 'A';
                    else if (i == 1) rua_letra = 'B';
                    else rua_letra = 'C';

                    for (j = 0; j < MAX_GONDOLAS; j++) {
                        if (strlen(estoque_codigo[i][j]) > 0) {
                            printf("%-10c %-10d %-10s %-10d\n",
                                rua_letra, j + 1, estoque_codigo[i][j], estoque_quantidade[i][j]);
                        }
                    }
                }
                break;

            case 0: // Sair
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
