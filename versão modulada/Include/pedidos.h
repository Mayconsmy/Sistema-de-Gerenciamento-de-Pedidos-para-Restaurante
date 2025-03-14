#ifndef PEDIDOS_H
#define PEDIDOS_H

#include "cardapio.h"

typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct {
    int id;
    char cliente[50];
    int quantidadeItens;
    Item *itens;
    StatusPedido status;
} Pedido;

void gerenciarPedidos(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio);
float calcularValorPedido(Pedido *pedido);
void criarPedido(Pedido **pedidos, int *quantidadePedidos, Item *cardapio, int quantidadeCardapio);
void alterarStatusPedido(Pedido *pedidos, int quantidadePedidos, int idPedido, StatusPedido novoStatus);
void finalizarPedido(Pedido *pedidos, int quantidadePedidos, int idPedido);
const char* obterNomeStatus(StatusPedido status);
void limparBuffer();

#endif // PEDIDOS_H