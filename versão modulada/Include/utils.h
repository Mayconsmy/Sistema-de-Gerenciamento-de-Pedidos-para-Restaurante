#ifndef UTILS_H
#define UTILS_H

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

void limparBuffer();
const char* obterNomeCategoria(Categoria categoria);
const char* obterNomeStatus(StatusPedido status);

#endif // UTILS_H