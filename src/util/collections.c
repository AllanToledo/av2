#include <stdlib.h>
#include "collections.h"

void liberarListaVeiculos(ListaVeiculo *listaVeiculo) {
    ListaVeiculo *lista = listaVeiculo;
    while (lista != NULL) { // Percorre a lista até o final
        ListaVeiculo *proximo = lista->proximo; // Guarda o próximo nó
        free(lista); // Libera o nó atual
        lista = proximo; // Atualiza o ponteiro para o próximo nó
    }
}

//Mesma coisa que o código acima, mas para lista de clientes
void liberarListaClientes(ListaClientes *listaClientes) {
    ListaClientes *lista = listaClientes;
    while (lista != NULL) {
        ListaClientes *proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }
}

void liberarListaLocacoes(ListaLocacoes *listaLocacoes) {
    ListaLocacoes *lista = listaLocacoes;
    while (lista != NULL) {
        ListaLocacoes *proximo = lista->proximo;
        free(lista);
        lista = proximo;
    }
}