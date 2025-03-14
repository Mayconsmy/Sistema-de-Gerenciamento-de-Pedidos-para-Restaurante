#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedidos.h"

float calcularValorPedido(Pedido *pedido) {
    float valorTotal = 0.0;
    for (int i = 0; i < pedido->quantidadeItens; i++) {
        valorTotal += pedido->itens[i].preco;
    }
    return valorTotal;
}

void gerenciarPedidos(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio) {
    int opcao;
    do {
        printf("\n=== Gerenciamento de Pedidos ===\n");
        printf("1. Exibir pedidos\n");
        printf("2. Criar novo pedido\n");
        printf("3. Alterar status de pedido\n");
        printf("4. Finalizar pedido\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparBuffer(); 
            continue;
        }

        switch (opcao) {
            case 1:
                // Exibir pedidos
                for (int i = 0; i < *quantidadePedidos; i++) {
                    printf("ID: %d\n", (*pedidos)[i].id);
                    printf("Cliente: %s\n", (*pedidos)[i].cliente);
                    printf("Quantidade de Itens: %d\n", (*pedidos)[i].quantidadeItens);
                    printf("Status: %s\n", obterNomeStatus((*pedidos)[i].status));
                    printf("Valor Total: %.2f\n", calcularValorPedido(&(*pedidos)[i]));
                    printf("\n");
                }
                break;
            case 2:
                criarPedido(pedidos, quantidadePedidos, cardapio, quantidadeCardapio);
                break;
            case 3:
                {
                    int idPedido;
                    int novoStatus;
                    printf("ID do pedido: ");
                    scanf("%d", &idPedido);
                    printf("Novo status (0: Pendente, 1: Em Preparo, 2: Pronto, 3: Entregue): ");
                    scanf("%d", &novoStatus);
                    alterarStatusPedido(*pedidos, *quantidadePedidos, idPedido, (StatusPedido)novoStatus);
                }
                break;
            case 4:
                {
                    int idPedido;
                    printf("ID do pedido: ");
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


void criarPedido(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio) {
    *pedidos = realloc(*pedidos, (*quantidadePedidos + 1) * sizeof(Pedido));
    if (*pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    Pedido *novoPedido = &(*pedidos)[*quantidadePedidos];
    novoPedido->id = *quantidadePedidos + 1;
    printf("Nome do cliente: ");
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

    for (int i = 0; i < novoPedido->quantidadeItens; i++) {
        int idItem;
        printf("ID do item %d: ", i + 1);
        scanf("%d", &idItem);
        for (int j = 0; j < quantidadeCardapio; j++) {
            if (cardapio[j].id == idItem) {
                novoPedido->itens[i] = cardapio[j];
                break;
            }
        }
    }

    novoPedido->status = PENDENTE;
    (*quantidadePedidos)++;
}

void alterarStatusPedido(Pedido *pedidos, int quantidadePedidos, int idPedido, StatusPedido novoStatus) {
    for (int i = 0; i < quantidadePedidos; i++) {
        if (pedidos[i].id == idPedido) {
            pedidos[i].status = novoStatus;
            printf("Status do pedido %d atualizado para %s\n", idPedido, obterNomeStatus(novoStatus));
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}

void finalizarPedido(Pedido *pedidos, int quantidadePedidos, int idPedido) {
    for (int i = 0; i < quantidadePedidos; i++) {
        if (pedidos[i].id == idPedido) {
            pedidos[i].status = ENTREGUE;
            printf("Pedido %d finalizado!\n", idPedido);
            return;
        }
    }
    printf("Pedido não encontrado!\n");
}