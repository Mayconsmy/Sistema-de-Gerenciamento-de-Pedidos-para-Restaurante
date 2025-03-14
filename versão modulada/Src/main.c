#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cardapio.h"
#include "pedidos.h"

// Função principal do programa
int main() {
    setlocale(LC_ALL, "Portuguese");

    Item *cardapio = NULL;
    int quantidadeCardapio = 0;
    Pedido *pedidos = NULL;
    int quantidadePedidos = 0;
    int opcao;

    printf("\nSeja bem-vindo ao Sistema de Gerenciamento de Pedidos do Restaurante Comidas do Sertão!\n");
    printf("Fique à vontade para proporcionar a melhor experiência para os nossos clientes <3.\n");

    do {
        printf("\nMenu:\n");
        printf("======== Restaurante =========\n");
        printf("1 - Gerenciar Cardápio\n");
        printf("2 - Gerenciar Pedidos\n");
        printf("0 - Sair\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciarCardapio(&cardapio, &quantidadeCardapio);
                break;
            case 2:
                gerenciarPedidos(&pedidos, &quantidadePedidos, cardapio, quantidadeCardapio);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
                limparBuffer();
                break;
        }
    } while (opcao != 0);

    free(cardapio);
    for (int i = 0; i < quantidadePedidos; i++) {
        free(pedidos[i].itens);
    }
    free(pedidos);

    return 0;
}