#ifndef CARDAPIO_H
#define CARDAPIO_H

// Enumeração para as categorias dos itens do cardápio
typedef enum {
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} Categoria;

// Estrutura para os itens do cardápio
typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    float preco;
    Categoria categoria;
} Item;

// Protótipos das funções do cardápio
void gerenciarCardapio(Item **cardapio, int *quantidade);
void exibirCardapioPorCategoria(Item *cardapio, int quantidade, Categoria categoria);
void adicionarItem(Item **cardapio, int *quantidade);
void removerItem(Item **cardapio, int *quantidade);
void atualizarItem(Item *cardapio, int quantidade);
const char* obterNomeCategoria(Categoria categoria);
void limparBuffer();

#endif