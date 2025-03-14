#ifndef UTILS_H
#define UTILS_H

// Enumeradores para as categorias dos itens
typedef enum {
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} Categoria;

// Enumerador para os status dos pedidos
typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

// Funções utilitárias
void limparBuffer();
const char* obterNomeCategoria(Categoria categoria);
const char* obterNomeStatus(StatusPedido status);

#endif // UTILS_H