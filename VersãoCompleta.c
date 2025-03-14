#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Enumerações das categorias dos itens e os status dos pedidos
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

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

const char* obterNomeCategoria(Categoria categoria) {
    switch (categoria) {
        case 1: return "Entrada";
        case 2: return "Principal";
        case 3: return "Sobremesa";
        case 4: return "Bebida";
        default: return "Desconhecida";
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

    int nomeValido = 0;
    while (!nomeValido) {
        printf("\nNome do item: ");
        scanf(" %[^\n]", novoItem->nome);
        limparBuffer();

        nomeValido = 1;
        int i;
        for (i = 0; novoItem->nome[i] != '\0'; i++) {
            if (isdigit(novoItem->nome[i])) {
                nomeValido = 0;
                printf("Nome inválido! Por favor, insira um nome sem números.\n");
                break;
            }
        }
    }

    printf("Descrição: ");
    scanf(" %[^\n]", novoItem->descricao);

    printf("Preço: ");
    while (scanf("%f", &novoItem->preco) != 1 || novoItem->preco <= 0) {
        printf("Preço inválido! Por favor, insira um valor positivo: ");
        limparBuffer();
    }
    limparBuffer();
    
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
    printf("\nDigite o ID do item a ser removido: ");
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
    printf("\nDigite o ID do item a ser atualizado: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > quantidade) {
        printf("ID inválido!\n");
        limparBuffer(); 
        return;
    }
    limparBuffer(); 

    Item *item = &cardapio[id - 1];

    printf("Novo nome do item: ");
    scanf(" %[^\n]", item->nome);
    limparBuffer(); // Limpar buffer após leitura do nome

    printf("Nova descrição: ");
    scanf(" %[^\n]", item->descricao);
    limparBuffer(); 

    printf("Novo preço: ");
    if (scanf("%f", &item->preco) != 1) {
        printf("Preço inválido!\n");
        limparBuffer(); 
        return;
    }
    limparBuffer(); 

    printf("Nova categoria (0-Entrada, 1-Prato Principal, 2-Sobremesa, 3-Bebida): ");
    int cat;
    if (scanf("%d", &cat) != 1 || cat < 0 || cat > 3) {
        printf("Categoria inválida!\n");
        limparBuffer(); 
        return;
    }
    item->categoria = (Categoria)cat;
    limparBuffer();

    printf("Item atualizado com sucesso!\n");
}

// Função para gerenciar o cardápio
void exibirCardapioPorCategoria(Item *cardapio, int quantidade, Categoria categoria) {
    printf("\n=== %s ===\n", obterNomeCategoria(categoria));
    for (int i = 0; i < quantidade; i++) {
        if (cardapio[i].categoria == categoria) {
            printf("ID: %d\n", cardapio[i].id);
            printf("Nome: %s\n", cardapio[i].nome);
            printf("Descrição: %s\n", cardapio[i].descricao);
            printf("Preço: %.2f\n", cardapio[i].preco);
            printf("\n");
        }
    }
}

void gerenciarCardapio(Item **cardapio, int *quantidade) {
    int opcao;
    do {
        printf("\n=== Gerenciamento do Cardápio ===\n");
        printf("1. Exibir cardápio\n");
        printf("2. Adicionar item ao cardápio\n");
        printf("3. Remover item do cardápio\n");
        printf("4. Atualizar item do cardápio\n");
        printf("0. Voltar ao menu principal\n");
        printf("==============================\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: {
                int categoriaOpcao;
                printf("\nEscolha a categoria para exibir:\n");
                printf("1. Entrada\n");
                printf("2. Principal\n");
                printf("3. Sobremesa\n");
                printf("4. Bebida\n");
                printf("0. Voltar ao menu\n");
                printf("================================\n");
                printf("Escolha uma opção: ");
                if (scanf("%d", &categoriaOpcao) != 1 || categoriaOpcao < 0 || categoriaOpcao > 4) {
                    printf("Opção inválida!\n");
                    limparBuffer();
                    continue;
                }
                if (categoriaOpcao == 0) {
                    printf("Voltando ao menu principal...\n");
                    break;
                }
                exibirCardapioPorCategoria(*cardapio, *quantidade, (Categoria)categoriaOpcao);
                break;
            }
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

// Função para alterar o status de um pedido
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
// Função para finalizar um pedido
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

float calcularValorPedido(Pedido *pedido) {
    float valorTotal = 0.0;
    for (int i = 0; i < pedido->quantidadeItens; i++) {
        valorTotal += pedido->itens[i].preco;
    }
    return valorTotal;
}

// Função para gerenciar os pedidos
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
                for (int i = 0; i < *quantidadePedidos; i++) {
                    printf("\nID: %d\n", (*pedidos)[i].id);
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


int main() {
    setlocale(LC_ALL, "Portuguese");

    Item *cardapio = NULL;
    int quantidadeCardapio = 0;
    Pedido *pedidos = NULL;
    int quantidadePedidos = 0;
    int opcao;

    printf("\nSeja bem-vindo ao Sistema de Gerenciamento de Pedidos do Restaurante!\n");
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