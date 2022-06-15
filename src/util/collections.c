#include <stdlib.h>
#include "collections.h"

void liberarListaVeiculos(ListaVeiculo *listaVeiculo) {
    ListaVeiculo *lista = listaVeiculo;
    while (lista != NULL) {
        ListaVeiculo *proximo = lista->next;
        free(lista);
        lista = proximo;
    }
}

void liberarListaClientes(ListaClientes *listaClientes) {
    ListaClientes *lista = listaClientes;
    while (lista != NULL) {
        ListaClientes *proximo = lista->next;
        free(lista);
        lista = proximo;
    }
}

void liberarListaLocacoes(ListaLocacoes *listaLocacoes) {
    ListaLocacoes *lista = listaLocacoes;
    while (lista != NULL) {
        ListaLocacoes *proximo = lista->next;
        free(lista);
        lista = proximo;
    }
}