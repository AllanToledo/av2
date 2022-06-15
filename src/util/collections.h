#include "structs.h"

#ifndef AV2_COLLECTIONS_H
#define AV2_COLLECTIONS_H

/*
 * Como não sabemos o tamanho da lista, usamos uma lista encadeada.
 * Cada nó da lista contém um elemento e um ponteiro para o próximo nó.
 */


typedef struct ListaVeiculo ListaVeiculo;
typedef struct ListaVeiculo {
    Veiculo veiculo;
    ListaVeiculo *proximo;
} ListaVeiculo;

typedef struct ListaClientes ListaClientes;
typedef struct ListaClientes {
    Cliente cliente;
    ListaClientes *proximo;
} ListaClientes;

typedef struct ListaLocacoes ListaLocacoes;
typedef struct ListaLocacoes {
    Locacao locacao;
    ListaLocacoes *proximo;
} ListaLocacoes;

/*
 * Somente a função free() não limparia toda a lista, então as funções
 * abaixo percorrem a lista liberando o espaço de memória alocado para cada nó.
 */

void liberarListaVeiculos(ListaVeiculo *listaVeiculo);

void liberarListaClientes(ListaClientes *listaClientes);

void liberarListaLocacoes(ListaLocacoes *listaLocacoes);

#endif //AV2_COLLECTIONS_H
