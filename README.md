# Sistema Restaurante "Comidas do Sertão"

Projeto desenvolvido para a disciplina **Estruturas de Dados 1** do professor **George Felipe Fernandes Vieira**.

## Descrição do Projeto

O **Sistema Restaurante "Dividão"** simula o funcionamento de um restaurante, permitindo o gerenciamento completo do cardápio e dos pedidos realizados pelos clientes. O sistema foi implementado na linguagem **C** e tem como objetivo aplicar conceitos fundamentais de estruturas de dados, tais como:

- **Ponteiros e Manipulação de Strings:** Operações básicas (cópia, concatenação, comparação) utilizando ponteiros.
- **Alocação Dinâmica de Memória:** Utilização de `malloc`, `realloc` e `free` para um gerenciamento eficiente dos dados.
- **Vetores Dinâmicos:** Implementação de listas dinâmicas para armazenamento dos itens do cardápio e dos pedidos.
- **Structs e Enumerações:** Organização dos dados em estruturas definidas, facilitando a manipulação e a legibilidade do código.

## Funcionalidades

- **Cadastro do Cardápio**
  - Adicionar, remover e atualizar itens do cardápio.
  - Cada item possui: nome, descrição, preço e categoria (utilizando enums para categorias como *Entrada*, *Prato Principal*, *Sobremesa* e *Bebida*).

- **Gerenciamento de Pedidos**
  - Criação de pedidos com identificador, dados do cliente, lista de itens (referenciando os itens do cardápio) e status (utilizando enums como *Pendente*, *Em Preparo*, *Pronto* e *Entregue*).
  - Alteração do status dos pedidos e finalização dos mesmos, simulando o fluxo de atendimento de um restaurante.

## Tecnologias e Conceitos Utilizados

- Linguagem C
- Manipulação de Ponteiros e Strings
- Alocação Dinâmica de Memória
- Vetores Dinâmicos
- Estruturas (Structs) e Enumerações
