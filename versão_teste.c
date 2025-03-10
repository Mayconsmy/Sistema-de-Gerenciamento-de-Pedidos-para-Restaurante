#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
    if (scanf("%d", &cat) != 1 || cat < 0 || cat > 3) {
        printf("\nOpçao Invalida!\n");
        limparBuffer();
        return;
    }
    else{
    novoItem->categoria = (Categoria)cat;
    }    
    (*quantidade)++;
    printf("Item adicionado com sucesso!\n");
}


// Função para remover um item do cardápio
void removerItem(Item **cardapio, int *quantidade) {
    if (*quantidade == 0) {
        printf("O cardápio está vazio!\n");
        return;
    }

    int id;
    int i;
    printf("Digite o ID do item a ser removido: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > *quantidade) {
        printf("ID inválido!\n");
        limparBuffer(); 
        return;
    }

    for (i = id - 1; i < *quantidade - 1; i++) {
        (*cardapio)[i] = (*cardapio)[i + 1];
    }

    (*quantidade)--;
    Item *temp = realloc(*cardapio, (*quantidade) * sizeof(Item));
    if (temp == NULL && *quantidade > 0) {
        printf("Erro ao realocar memória.\n");
        return;
    }
    *cardapio = temp;

    printf("Item removido com sucesso!\n");
}

// Função para atualizar um item do cardápio
void atualizarItem(Item *cardapio, int quantidade) {
    if (quantidade == 0) {
        printf("O cardápio está vazio!\n");
        return;
    }
    int id;
    printf("Digite o ID do item a ser atualizado: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > quantidade) {
        printf("ID inválido!\n");
        limparBuffer(); 
        return;
    }

    Item *item = &cardapio[id - 1];

    printf("Novo nome do item: ");
    scanf(" %[^\n]", item->nome);
    limparBuffer(); 

    printf("Nova descrição: ");
    scanf(" %[^\n]", item->descricao);
    limparBuffer(); 

    printf("Novo preço: ");
    if (scanf("%f", &item->preco) != 1) {
        printf("Preço inválido!\n");
        limparBuffer(); 
        return;
    }

    printf("Nova categoria (0-Entrada, 1-Prato Principal, 2-Sobremesa, 3-Bebida): ");
    int cat;
    if (scanf("%d", &cat) != 1 || cat < 0 || cat > 3) {
        printf("Categoria inválida!\n");
        limparBuffer(); 
        return;
    }
    item->categoria = (Categoria)cat;

    printf("Item atualizado com sucesso!\n");
}

// Função para gerenciar o cardápio
void gerenciarCardapio(Item **cardapio, int *quantidade) {
    int opcao;
    do {
        printf("\n=== Gerenciamento do Cardápio ===\n");
        printf("1. Exibir cardápio\n");
        printf("2. Adicionar item ao cardápio\n");
        printf("3. Remover item do cardápio\n");
        printf("4. Atualizar item do cardápio\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        //resolvido
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if (*quantidade == 0) {
                    printf("\nO cardápio está vazio!\n");
                } else {
                    printf("\n=== Cardápio ===\n");
                    int i = 0;
                    for (i = 0; i < *quantidade; i++) {
                        printf("ID: %d\n", (*cardapio)[i].id);
                        printf("Nome: %s\n", (*cardapio)[i].nome);
                        printf("Descrição: %s\n", (*cardapio)[i].descricao);
                        printf("Preço: R$ %.2f\n", (*cardapio)[i].preco);
                        printf("Categoria: %s\n", obterNomeCategoria((*cardapio)[i].categoria));
                        printf("-----------------------\n");
                    }
                }
                break;
            case 2:
                adicionarItem(cardapio, quantidade);
                break;
            case 3:
                removerItem(cardapio, quantidade);
                break;
            case 4:
                atualizarItem(*cardapio, *quantidade);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                if (scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 4){
                    printf("Opção inválida!\n");
                    limparBuffer();
                    return;
                }
        }
    } while (opcao != 0);
}

// Função para criar um novo pedido
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
    limparBuffer(); 

    novoPedido->itens = malloc(sizeof(Item) * 1);
    if (novoPedido->itens == NULL) {
        printf("Erro ao alocar memória para os itens do pedido.\n");
        return;
    }
    novoPedido->quantidadeItens = 0;

    int idItem;
    printf("Informe os IDs dos itens para adicionar ao pedido (0 para finalizar):\n");
    while (1) {
        printf("ID do item: ");
        if (scanf("%d", &idItem) != 1) {
            printf("Entrada inválida. Por favor, insira um número.\n");
            limparBuffer(); 
            continue;
        }

        if (idItem == 0) break;

        if (idItem > 0 && idItem <= quantidadeCardapio) {
            novoPedido->quantidadeItens++;
            novoPedido->itens = realloc(novoPedido->itens, novoPedido->quantidadeItens * sizeof(Item));
            if (novoPedido->itens == NULL) {
                printf("Erro ao alocar memória para adicionar o item ao pedido.\n");
                return;
            }
            novoPedido->itens[novoPedido->quantidadeItens - 1] = cardapio[idItem - 1];  
        } else {
            printf("Item inválido.\n");
        }
    }

    if (novoPedido->quantidadeItens > 0) {
        novoPedido->status = PENDENTE;
        (*quantidadePedidos)++;
        printf("Pedido criado com sucesso!\n");
    } else {
        free(novoPedido->itens);
        printf("Pedido não foi criado. Nenhum item foi adicionado.\n");
    }
}

// Função para alterar o status de um pedido
void alterarStatusPedido(Pedido *pedidos, int quantidadePedidos, int idPedido, StatusPedido novoStatus) {
    int i = 0;
    for (i = 0; i < quantidadePedidos; i++) {
        if (pedidos[i].id == idPedido) {
            pedidos[i].status = novoStatus;
            printf("Status do pedido %d alterado para %s.\n", idPedido, obterNomeStatus(novoStatus));
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

// Função para gerenciar os pedidos
void gerenciarPedidos(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio) {
    int opcao;
    int i;
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
                if (*quantidadePedidos == 0) {
                    printf("\nNão há pedidos registrados!\n");
                } else {
                    printf("\n=== Pedidos ===\n");
                    for (i = 0; i < *quantidadePedidos; i++) {
                        int j;
                        printf("ID do pedido: %d\n", (*pedidos)[i].id);
                        printf("Cliente: %s\n", (*pedidos)[i].cliente);
                        printf("Status: %s\n", obterNomeStatus((*pedidos)[i].status));
                        printf("Itens do pedido:\n");
                        for (j = 0; j < (*pedidos)[i].quantidadeItens; j++) {
                            printf("  - %s (R$ %.2f)\n", (*pedidos)[i].itens[j].nome, (*pedidos)[i].itens[j].preco);
                        }
                        printf("-----------------------\n");
                    }
                }
                break;
            case 2:
                criarPedido(pedidos, quantidadePedidos, cardapio, quantidadeCardapio);
                break;
            case 3: {
                int idPedido, novoStatus;
                printf("Informe o ID do pedido para alterar o status: ");
                if (scanf("%d", &idPedido) != 1) {
                    printf("Entrada inválida. Por favor, insira um número.\n");
                    limparBuffer(); 
                    continue;
                }
                printf("Informe o novo status (0-Pendente, 1-Em Preparo, 2-Pronto, 3-Entregue): ");
                if (scanf("%d", &novoStatus) != 1 || novoStatus < 0 || novoStatus > 3) {
                    printf("Status inválido.\n");
                    limparBuffer(); 
                    continue;
                }
                alterarStatusPedido(*pedidos, *quantidadePedidos, idPedido, (StatusPedido)novoStatus);
                break;
            }
            case 4: {
                int idPedido;
                printf("Informe o ID do pedido para finalizar: ");
                if (scanf("%d", &idPedido) != 1) {
                    printf("Entrada inválida. Por favor, insira um número.\n");
                    limparBuffer(); 
                    continue;
                }
                finalizarPedido(*pedidos, *quantidadePedidos, idPedido);
                break;
            }
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

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
                if (scanf("%d", &opcao) != 1 || opcao < 0 || opcao > 4){
                    printf("Opção inválida!\n");
                    limparBuffer();
                    return;
                }
        }
    }
    while (opcao != 0);

    free(cardapio);
    int i = 0;
    for (i = 0; i < quantidadePedidos; i++) {
        free(pedidos[i].itens);
    }
    free(pedidos);

    return 0;
}