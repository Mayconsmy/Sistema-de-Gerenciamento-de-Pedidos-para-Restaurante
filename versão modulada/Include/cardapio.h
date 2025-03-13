#ifndef CARDAPIO_H
#define CARDAPIO_H

#include "utils.h"

typedef struct {
    int id;
    char nome[50];
    char descricao[100];
    float preco;
    Categoria categoria;
} Item;

void gerenciarCardapio(Item **cardapio, int *quantidade);
void adicionarItem(Item **cardapio, int *quantidade);
void removerItem(Item **cardapio, int *quantidade);
void atualizarItem(Item *cardapio, int quantidade);

#endif // CARDAPIO_H