#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definição das enum's
typedef enum {
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} Categoria;

typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

// Definição das structs
typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    float preco;
    Categoria categoria;
} Item;

typedef struct {
    int id;
    char cliente[50];
    Item *itens;
    int quantidadeItens;
    StatusPedido status;
} Pedido;

// Função para obter o nome da categoria como string
const char* obterNomeCategoria(Categoria categoria) {
    switch (categoria) {
        case ENTRADA: return "Entrada";
        case PRINCIPAL: return "Prato Principal";
        case SOBREMESA: return "Sobremesa";
        case BEBIDA: return "Bebida";
        default: return "Desconhecido";
    }
}

// Função para obter o nome do status como string
const char* obterNomeStatus(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "Pendente";
        case EM_PREPARO: return "Em Preparação";
        case PRONTO: return "Pronto";
        case ENTREGUE: return "Entregue";
        default: return "Desconhecido";
    }
}


// Função para adicionar um item ao cardápio
void adicionarItem(Item **cardapio, int *quantidade) {
    *cardapio = realloc(*cardapio, (*quantidade + 1) * sizeof(Item));
    if (*cardapio == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    Item *novoItem = &(*cardapio)[*quantidade];
    novoItem->id = *quantidade + 1;

    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem->nome);

    printf("Descrição: ");
    scanf(" %[^\n]", novoItem->descricao);

    printf("Preço: ");
    scanf("%f", &novoItem->preco);

    printf("Categoria (0-Entrada, 1-Prato Principal, 2-Sobremesa, 3-Bebida): ");
    int cat;
    scanf("%d", &cat);
    novoItem->categoria = (Categoria)cat;

    (*quantidade)++;
    printf("Item adicionado com sucesso!\n");
}

// Função para exibir o cardápio
void exibirCardapio(Item *cardapio, int quantidade) {
    printf("\n=== Cardápio ===\n");
    int i = 0;
    for (i = 0; i < quantidade; i++) {
        printf("ID: %d\n", cardapio[i].id);
        printf("Nome: %s\n", cardapio[i].nome);
        printf("Descrição: %s\n", cardapio[i].descricao);
        printf("Preço: R$ %.2f\n", cardapio[i].preco);
        printf("Categoria: %s\n", obterNomeCategoria(cardapio[i].categoria));
        printf("-----------------------\n");
    }
}

// Função para criar um pedido(com verificação de alocação de memória)
void criarPedido(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio) {
    *pedidos = realloc(*pedidos, (*quantidadePedidos + 1) * sizeof(Pedido));
    if (*pedidos == NULL) {
        printf("Erro ao alocar memória para o pedido.\n");
        return;
    }

    Pedido *novoPedido = &(*pedidos)[*quantidadePedidos];
    novoPedido->id = *quantidadePedidos + 1;

    printf("Nome do cliente: ");
    scanf(" %[^\n]", novoPedido->cliente);

    novoPedido->itens = malloc(sizeof(Item) * 1); // Começamos com um item
    if (novoPedido->itens == NULL) {
        printf("Erro ao alocar memória para os itens do pedido.\n");
        return;
    }
    novoPedido->quantidadeItens = 0;

    // Adiciona itens ao pedido
    int idItem;
    printf("Informe os IDs dos itens para adicionar ao pedido (0 para finalizar):\n");
    while (1) {
        printf("ID do item: ");
        scanf("%d", &idItem);

        if (idItem == 0) break;  // Finaliza a adição de itens

        // Verifica se o item existe no cardápio
        if (idItem > 0 && idItem <= quantidadeCardapio) {
            novoPedido->quantidadeItens++;
            novoPedido->itens = realloc(novoPedido->itens, novoPedido->quantidadeItens * sizeof(Item));
            if (novoPedido->itens == NULL) {
                printf("Erro ao alocar memória para adicionar o item ao pedido.\n");
                return;
            }
            novoPedido->itens[novoPedido->quantidadeItens - 1] = cardapio[idItem - 1];  // Adiciona item
        } else {
            printf("Item inválido.\n");
        }
    }

    novoPedido->status = PENDENTE;  // Status inicial do pedido
    (*quantidadePedidos)++;
    printf("Pedido criado com sucesso!\n");
}

// Função para alterar o status de um pedido
void alterarStatusPedido(Pedido *pedidos, int quantidadePedidos, int idPedido, StatusPedido novoStatus) {
    int i = 0;
    for (i = 0; i < quantidadePedidos; i++) {
        if (pedidos[i].id == idPedido) {
            pedidos[i].status = novoStatus;
            printf("Status do pedido %d alterado para %d.\n", idPedido, novoStatus);
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

// Função para finalizar um pedido
void finalizarPedido(Pedido *pedidos, int quantidadePedidos, int idPedido) {
    alterarStatusPedido(pedidos, quantidadePedidos, idPedido, ENTREGUE);
    printf("Pedido %d finalizado com sucesso!\n", idPedido);
}

// Função para exibir os pedidos com status legível
void exibirPedidos(Pedido *pedidos, int quantidadePedidos) {
    printf("\n=== Pedidos ===\n");
    int i = 0;
    for (i = 0; i < quantidadePedidos; i++) {
        printf("ID do pedido: %d\n", pedidos[i].id);
        printf("Cliente: %s\n", pedidos[i].cliente);
        printf("Status: %s\n", obterNomeStatus(pedidos[i].status));  // Exibe o status como string
        printf("Itens do pedido:\n");
        int j = 0;
        for (j = 0; j < pedidos[i].quantidadeItens; j++) {
            printf("  - %s (R$ %.2f)\n", pedidos[i].itens[j].nome, pedidos[i].itens[j].preco);
        }
        printf("-----------------------\n");
    }
}


// Função principal 
int main() {
setlocale(LC_ALL, "portuguese");

    Item *cardapio = NULL;
    int quantidadeCardapio = 0;
    Pedido *pedidos = NULL;
    int quantidadePedidos = 0;
    int opcao;
    printf("\n");
    printf("Seja bem-vindo ao Sistema de Gerenciamento de pedidos do Restaurante Comidas do Sertão!\n1Fique a vontade para travez a melhor experiência para os nossos clientes  <3.\n");
        
    do {
        //tabela de opções
        printf("\nMenu:\n");
        printf("======== Restaurante =========\n");
        printf("1 - Adicionar item ao cardápio\n");
        printf("2 - Exibir cardápio\n");
        printf("3 - Criar pedido\n");
        printf("4 - Exibir pedidos\n");
        printf("5 - Alterar status de pedido\n");
        printf("6 - Finalizar pedido\n");
        printf("0 - Sair\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");
        printf("\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarItem(&cardapio, &quantidadeCardapio);
                break;
            case 2:
                exibirCardapio(cardapio, quantidadeCardapio);
                break;
            case 3:
                criarPedido(&pedidos, &quantidadePedidos, cardapio, quantidadeCardapio);
                break;
            case 4:
                exibirPedidos(pedidos, quantidadePedidos);
                break;
            case 5: {
                int idPedido, novoStatus;
                printf("Informe o ID do pedido para alterar o status: ");
                scanf("%d", &idPedido);
                printf("Informe o novo status (0-Pendente, 1-Em Preparo, 2-Pronto, 3-Entregue): ");
                scanf("%d", &novoStatus);
                alterarStatusPedido(pedidos, quantidadePedidos, idPedido, (StatusPedido)novoStatus);
                break;
            }
            case 6: {
                int idPedido;
                printf("Informe o ID do pedido para finalizar: ");
                scanf("%d", &idPedido);
                finalizarPedido(pedidos, quantidadePedidos, idPedido);
                break;
            }
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

free(cardapio); 
int i = 0;
for (i = 0; i < quantidadePedidos; i++) {
    free(pedidos[i].itens);
}
free(pedidos);

return 0;
}