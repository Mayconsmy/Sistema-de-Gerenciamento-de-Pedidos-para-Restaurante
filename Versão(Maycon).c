#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef enum {
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} CategoriaItem;


typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;


typedef struct {
    char nome[50];
    char descricao[100];
    float preco;
    CategoriaItem categoria;
} ItemCardapio;


typedef struct {
    int id;
    char cliente[50];
    ItemCardapio *itens;
    int quantidade;
    StatusPedido status;
} Pedido;


ItemCardapio *cardapio = NULL;
int totalItens = 0;
Pedido *pedidos = NULL;
int totalPedidos = 0;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


CategoriaItem obterCategoriaPorNumero(int num) {
    switch (num) {
        case 0: return ENTRADA;
        case 1: return PRINCIPAL;
        case 2: return SOBREMESA;
        case 3: return BEBIDA;
        default: return ENTRADA;
    }
}


void adicionarItemCardapio() {
    ItemCardapio *temp = realloc(cardapio, (totalItens + 1) * sizeof(ItemCardapio));
    if (!temp) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    cardapio = temp;


    printf("Nome do item: ");
    fgets(cardapio[totalItens].nome, sizeof(cardapio[totalItens].nome), stdin);
    cardapio[totalItens].nome[strcspn(cardapio[totalItens].nome, "\n")] = 0;


    printf("Descrição: ");
    fgets(cardapio[totalItens].descricao, sizeof(cardapio[totalItens].descricao), stdin);
    cardapio[totalItens].descricao[strcspn(cardapio[totalItens].descricao, "\n")] = 0;


    printf("Preço: ");
    if (scanf("%f", &cardapio[totalItens].preco) != 1) {
        printf("Entrada inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();


    int cat;
    printf("Categoria (0-Entrada, 1-Principal, 2-Sobremesa, 3-Bebida): ");
    if (scanf("%d", &cat) != 1 || cat < 0 || cat > 3) {
        printf("Categoria inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();
    cardapio[totalItens].categoria = obterCategoriaPorNumero(cat);


    totalItens++;
    printf("Item adicionado com sucesso!\n");
}


void removerItemCardapio() {
    if (totalItens == 0) {
        printf("O cardápio está vazio!\n");
        return;
    }
    int id;
    printf("Digite o número do item a ser removido: ");
    scanf("%d", &id);
    limparBuffer();


    if (id < 1 || id > totalItens) {
        printf("Item inválido!\n");
        return;
    }
    

    for (int i = id - 1; i < totalItens - 1; i++) {
        cardapio[i] = cardapio[i + 1];
    }


    totalItens--;
    cardapio = realloc(cardapio, totalItens * sizeof(ItemCardapio));
    printf("Item removido com sucesso!\n");
}


void exibirCardapio() {
    if (totalItens == 0) {
        printf("\nO cardápio está vazio!\n");
        return;
    }


    printf("\n--- Cardápio ---\n");
    for (int i = 0; i < totalItens; i++) {
        char *categorias[] = {"Entrada", "Principal", "Sobremesa", "Bebida"};
        printf("%d - %s | %s | R$%.2f | %s\n",
               i + 1, cardapio[i].nome, cardapio[i].descricao, cardapio[i].preco, categorias[cardapio[i].categoria]);
    }
}


void registrarPedido() {
    if (totalItens == 0) {
        printf("Não há itens no cardápio para realizar um pedido!\n");
        return;
    }


    Pedido *temp = realloc(pedidos, (totalPedidos + 1) * sizeof(Pedido));
    if (!temp) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    pedidos = temp;


    Pedido *p = &pedidos[totalPedidos];
    p->id = totalPedidos + 1;


    printf("Nome do cliente: ");
    fgets(p->cliente, sizeof(p->cliente), stdin);
    p->cliente[strcspn(p->cliente, "\n")] = 0;


    exibirCardapio();
    printf("Quantos itens deseja? ");
    if (scanf("%d", &p->quantidade) != 1 || p->quantidade <= 0) {
        printf("Entrada inválida!\n");
        limparBuffer();
        return;
    }
    limparBuffer();


    p->itens = malloc(p->quantidade * sizeof(ItemCardapio));
    if (!p->itens) {
        printf("Erro ao alocar memória!\n");
        return;
    }


    for (int i = 0; i < p->quantidade; i++) {
        int itemIndex;
        printf("Escolha o item %d (número do cardápio): ", i + 1);
        if (scanf("%d", &itemIndex) != 1 || itemIndex < 1 || itemIndex > totalItens) {
            printf("Número inválido!\n");
            limparBuffer();
            return;
        }
        limparBuffer();
        p->itens[i] = cardapio[itemIndex - 1];
    }


    p->status = PENDENTE;
    totalPedidos++;
    printf("Pedido registrado com sucesso!\n");
}


void removerPedido() {
    if (totalPedidos == 0) {
        printf("Não há pedidos registrados!\n");
        return;
    }
    int id;
    printf("Digite o ID do pedido a ser removido: ");
    scanf("%d", &id);
    limparBuffer();


    if (id < 1 || id > totalPedidos) {
        printf("Pedido não encontrado!\n");
        return;
    }


    free(pedidos[id - 1].itens);
    for (int i = id - 1; i < totalPedidos - 1; i++) {
        pedidos[i] = pedidos[i + 1];
    }


    totalPedidos--;
    pedidos = realloc(pedidos, totalPedidos * sizeof(Pedido));
    printf("Pedido removido com sucesso!\n");
}


void atualizarStatusPedido() {
    if (totalPedidos == 0) {
        printf("Não há pedidos para atualizar!\n");
        return;
    }


    int id, status;
    printf("Digite o ID do pedido: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > totalPedidos) {
        printf("Pedido não encontrado!\n");
        limparBuffer();
        return;
    }
    limparBuffer();


    printf("Selecione o novo status (0-Pendente, 1-Em Preparo, 2-Pronto, 3-Entregue): ");
    if (scanf("%d", &status) != 1 || status < 0 || status > 3) {
        printf("Status inválido!\n");
        limparBuffer();
        return;
    }
    limparBuffer();


    pedidos[id - 1].status = status;
    printf("Status atualizado com sucesso!\n");
}


void exibirPedidos() {
    if (totalPedidos == 0) {
        printf("\nNão há pedidos registrados!\n");
        return;
    }


    printf("\n--- Pedidos ---\n");
    for (int i = 0; i < totalPedidos; i++) {
        printf("Pedido #%d | Cliente: %s | Status: %d | Itens: %d\n",
               pedidos[i].id, pedidos[i].cliente, pedidos[i].status, pedidos[i].quantidade);
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    do {
        printf("\n1. Adicionar item ao cardápio\n2. Remover item do cardápio\n3. Exibir cardápio\n4. Registrar pedido\n5. Remover pedido\n6. Atualizar status de pedido\n7. Exibir pedidos\n0. Sair\nEscolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao) {
            case 1: adicionarItemCardapio(); break;
            case 2: removerItemCardapio(); break;
            case 3: exibirCardapio(); break;
            case 4: registrarPedido(); break;
            case 5: removerPedido(); break;
            case 6: atualizarStatusPedido(); break;
            case 7: exibirPedidos(); break;
            case 0: printf("Encerrando sistema...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);


    free(cardapio);
    for (int i = 0; i < totalPedidos; i++) free(pedidos[i].itens);
    free(pedidos);
    return 0;
}

