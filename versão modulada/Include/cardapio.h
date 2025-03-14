#ifndef CARDAPIO_H
#define CARDAPIO_H

typedef enum {
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} Categoria;

typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    float preco;
    Categoria categoria;
} Item;

void gerenciarCardapio(Item **cardapio, int *quantidade);
void exibirCardapioPorCategoria(Item *cardapio, int quantidade, Categoria categoria);
void adicionarItem(Item **cardapio, int *quantidade);
void removerItem(Item **cardapio, int *quantidade);
void atualizarItem(Item *cardapio, int quantidade);
const char* obterNomeCategoria(Categoria categoria);
void limparBuffer();

#endif // CARDAPIO_H