#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

// Verifique se os tipos Categoria e StatusPedido estão definidos
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

#endif // UTILS_H

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

const char* obterNomeCategoria(Categoria categoria) {
    switch (categoria) {
        case ENTRADA: return "Entrada";
        case PRINCIPAL: return "Prato Principal";
        case SOBREMESA: return "Sobremesa";
        case BEBIDA: return "Bebida";
        default: return "Desconhecido";
    }
}

const char* obterNomeStatus(StatusPedido status) {
    switch (status) {
        case PENDENTE: return "Pendente";
        case EM_PREPARO: return "Em Preparação";
        case PRONTO: return "Pronto";
        case ENTREGUE: return "Entregue";
        default: return "Desconhecido";
    }
}