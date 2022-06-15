#include "structs.h"

#ifndef AV2_COLLECTIONS_H
#define AV2_COLLECTIONS_H

typedef struct ListaVeiculo ListaVeiculo;
typedef struct ListaVeiculo {
    Veiculo veiculo;
    ListaVeiculo *next;
} ListaVeiculo;

typedef struct ListaClientes ListaClientes;
typedef struct ListaClientes {
    Cliente cliente;
    ListaClientes *next;
} ListaClientes;

typedef struct ListaLocacoes ListaLocacoes;
typedef struct ListaLocacoes {
    Locacao locacao;
    ListaLocacoes *next;
} ListaLocacoes;

void liberarListaVeiculos(ListaVeiculo *listaVeiculo);

void liberarListaClientes(ListaClientes *listaClientes);

void liberarListaLocacoes(ListaLocacoes *listaLocacoes);

#endif //AV2_COLLECTIONS_H
