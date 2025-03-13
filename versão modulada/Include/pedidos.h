#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "utils.h"
#include "cardapio.h"

typedef struct {
    int id;
    char cliente[50];
    Item *itens;
    int quantidadeItens;
    StatusPedido status;
} Pedido;

void gerenciarPedidos(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio);
void criarPedido(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio);
void alterarStatusPedido(Pedido *pedidos, int quantidadePedidos, int idPedido, StatusPedido novoStatus);
void finalizarPedido(Pedido *pedidos, int quantidadePedidos, int idPedido);

#endif // PEDIDOS_H