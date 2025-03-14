#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos.h"

// Função para calcular o valor total de um pedido
float calcularValorPedido(Pedido *pedido) {
    float valorTotal = 0.0;
    int i;
    for (i = 0; i < pedido->quantidadeItens; i++) {
        valorTotal += pedido->itens[i].preco;
    }
    return valorTotal;
}

// Função para obter o nome de um status de pedido
void gerenciarPedidos(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio) {
    int opcao;
    do {
        printf("\n=== Gerenciamento de Pedidos ===\n");
        printf("1. Exibir pedidos\n");
        printf("2. Criar novo pedido\n");
        printf("3. Alterar status de pedido\n");
        printf("4. Finalizar pedido\n");
        printf("0. Voltar ao menu principal\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparBuffer(); 
            continue;
        }

        switch (opcao) {
            case 1:
                // Exibir pedidos
                {
                    int i;
                    for (i = 0; i < *quantidadePedidos; i++) {
                        printf("\nID: %d\n", (*pedidos)[i].id);
                        printf("Cliente: %s\n", (*pedidos)[i].cliente);
                        printf("Quantidade de Itens: %d\n", (*pedidos)[i].quantidadeItens);
                        printf("Status: %s\n", obterNomeStatus((*pedidos)[i].status));
                        printf("Valor Total: %.2f\n", calcularValorPedido(&(*pedidos)[i]));
                        printf("\n");
                    }
                }
                break;
            case 2:
                criarPedido(pedidos, quantidadePedidos, cardapio, quantidadeCardapio);
                break;
            case 3:
                {
                    int idPedido;
                    int novoStatus;
                    printf("\nID do pedido: ");
                    scanf("%d", &idPedido);
                    printf("Novo status (0: Pendente, 1: Em Preparo, 2: Pronto, 3: Entregue): ");
                    scanf("%d", &novoStatus);
                    alterarStatusPedido(*pedidos, *quantidadePedidos, idPedido, (StatusPedido)novoStatus);
                }
                break;
            case 4:
                {
                    int idPedido;
                    printf("\nID do pedido: ");
                    scanf("%d", &idPedido);
                    finalizarPedido(*pedidos, *quantidadePedidos, idPedido);
                }
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
                limparBuffer();
                break;
        }
    } while (opcao != 0);
}

// Função para criar um novo pedido
void criarPedido(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio) {
    *pedidos = realloc(*pedidos, (*quantidadePedidos + 1) * sizeof(Pedido));
    if (*pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    Pedido *novoPedido = &(*pedidos)[*quantidadePedidos];
    novoPedido->id = *quantidadePedidos + 1;
    printf("\nNome do cliente: ");
    limparBuffer();
    fgets(novoPedido->cliente, 50, stdin);
    novoPedido->cliente[strcspn(novoPedido->cliente, "\n")] = '\0';

    printf("Quantidade de itens: ");
    scanf("%d", &novoPedido->quantidadeItens);
    novoPedido->itens = malloc(novoPedido->quantidadeItens * sizeof(Item));
    if (novoPedido->itens == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    int i;
    for (i = 0; i < novoPedido->quantidadeItens; i++) {
        int idItem;
        printf("ID do item %d: ", i + 1);
        scanf("%d", &idItem);
        int j;
        for (j = 0; j < quantidadeCardapio; j++) {
            if (cardapio[j].id == idItem) {
                novoPedido->itens[i] = cardapio[j];
                break;
            }
        }
    }

    novoPedido->status = PENDENTE;
    (*quantidadePedidos)++;
}

// Função para alterar o status de um pedido
void alterarStatusPedido(Pedido *pedidos, int quantidadePedidos, int idPedido, StatusPedido novoStatus) {
    int i;
    for (i = 0; i < quantidadePedidos; i++) {
        if (pedidos[i].id == idPedido) {
            pedidos[i].status = novoStatus;
            printf("Status do pedido %d atualizado para %s\n", idPedido, obterNomeStatus(novoStatus));
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

// Função para finalizar um pedido
void finalizarPedido(Pedido *pedidos, int quantidadePedidos, int idPedido) {
    int i;
    for (i = 0; i < quantidadePedidos; i++) {
        if (pedidos[i].id == idPedido) {
            pedidos[i].status = ENTREGUE;
            printf("Pedido %d finalizado!\n", idPedido);
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}