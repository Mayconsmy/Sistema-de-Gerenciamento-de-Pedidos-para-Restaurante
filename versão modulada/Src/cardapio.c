#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cardapio.h"

// Função para exibir o cardápio por categoria
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
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida!\n");
            limparBuffer();
            continue;
        }

        switch (opcao) {
            case 1: {
                int categoriaOpcao;
                printf("\nEscolha a categoria para exibir:\n");
                printf("0. Entrada\n");
                printf("1. Principal\n");
                printf("2. Sobremesa\n");
                printf("3. Bebida\n");
                printf("Escolha uma opção: ");
                if (scanf("%d", &categoriaOpcao) != 1 || categoriaOpcao < 0 || categoriaOpcao > 3) {
                    printf("Opção inválida!\n");
                    limparBuffer();
                    continue;
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

// Função para adicionar um item ao cardápio
void adicionarItem(Item **cardapio, int *quantidade) {
    *cardapio = realloc(*cardapio, (*quantidade + 1) * sizeof(Item));
    if (*cardapio == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    Item *novoItem = &(*cardapio)[*quantidade];
    novoItem->id = *quantidade + 1;
    printf("Nome: ");
    limparBuffer();
    fgets(novoItem->nome, 50, stdin);
    novoItem->nome[strcspn(novoItem->nome, "\n")] = '\0';
    printf("Descrição: ");
    fgets(novoItem->descricao, 100, stdin);
    novoItem->descricao[strcspn(novoItem->descricao, "\n")] = '\0';
    printf("Preço: ");
    scanf("%f", &novoItem->preco);
    printf("Categoria (0: Entrada, 1: Principal, 2: Sobremesa, 3: Bebida): ");
    int categoria;
    scanf("%d", &categoria);
    novoItem->categoria = (Categoria)categoria;

    (*quantidade)++;
}

// Função para remover um item do cardápio
void removerItem(Item **cardapio, int *quantidade) {
    int id;
    printf("ID do item a ser removido: ");
    scanf("%d", &id);

    for (int i = 0; i < *quantidade; i++) {
        if ((*cardapio)[i].id == id) {
            for (int j = i; j < *quantidade - 1; j++) {
                (*cardapio)[j] = (*cardapio)[j + 1];
            }
            (*cardapio) = realloc(*cardapio, (*quantidade - 1) * sizeof(Item));
            (*quantidade)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Função para atualizar um item do cardápio
void atualizarItem(Item *cardapio, int quantidade) {
    int id;
    printf("ID do item a ser atualizado: ");
    scanf("%d", &id);

    for (int i = 0; i < quantidade; i++) {
        if (cardapio[i].id == id) {
            printf("Novo nome: ");
            limparBuffer();
            fgets(cardapio[i].nome, 50, stdin);
            cardapio[i].nome[strcspn(cardapio[i].nome, "\n")] = '\0';
            printf("Nova descrição: ");
            fgets(cardapio[i].descricao, 100, stdin);
            cardapio[i].descricao[strcspn(cardapio[i].descricao, "\n")] = '\0';
            printf("Novo preço: ");
            scanf("%f", &cardapio[i].preco);
            printf("Nova categoria (0: Entrada, 1: Principal, 2: Sobremesa, 3: Bebida): ");
            int categoria;
            scanf("%d", &categoria);
            cardapio[i].categoria = (Categoria)categoria;
            printf("Item atualizado com sucesso!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}