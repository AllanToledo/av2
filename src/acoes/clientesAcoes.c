#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "acoes.h"
#include "../util/collections.h"
#include "../database/clientes/clientesDB.h"

void cadastrarClientes();

void listarClientes();

void atualizarCliente();

// Explicação das ações no arquivo veiculosAcoes.c

const acao *clientesActions = (acao[]) {
        {.nome = "Cadastrar clientes", .acao = cadastrarClientes},
        {.nome = "Lista clientes", .acao = listarClientes},
        {.nome = "Atualizar cliente", .acao = atualizarCliente},
        // Adicionar outras ações acima desta linha
        {.nome = "Voltar", .acao = NULL}
};

acao *pegarListaClientesAcoes() {
    return clientesActions;
}

void cadastrarClientes() {
    Cliente cliente;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", cliente.nome);
    printf("Digite o CPF do cliente (somente numeros): ");
    scanf(" %[^\n]", cliente.cpf);
    printf("Digite a idade do cliente: ");
    scanf("%d", &cliente.idade);
    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", cliente.endereco);
    printf("Digite a cidade do cliente: ");
    scanf(" %[^\n]", cliente.cidade);
    printf("Digite a sigla estado do cliente: ");
    scanf(" %[^\n]", cliente.estado);
    cliente.pontos = 0;
    inserirClientesDB(cliente);
    printf("\n\n");
    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes() {
    ListaClientes *lista = pegarClientesDB();
    Cliente cliente;
    if (lista == NULL) {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }
    do {
        cliente = lista->cliente;
        printCliente(cliente);
        printf("\n");

    } while ((lista = lista->proximo) != NULL);
    liberarListaClientes(lista);
}

void atualizarCliente() {
    ListaClientes *lista = pegarClientesDB();
    if (lista == NULL) {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }
    Cliente cliente;
    char cpf[12];
    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]", cpf);
    int encontrou = FALSE;
    do {
        cliente = lista->cliente;
        if (strcmp(cliente.cpf, cpf) == 0) {
            encontrou = TRUE;
            break;
        }
    } while ((lista = lista->proximo) != NULL);

    if (!encontrou) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printCliente(cliente);
    printf("\n");
    printf("Digite o novo nome do cliente: ");
    scanf(" %[^\n]", cliente.nome);
    printf("Digite o novo CPF do cliente (somente numeros): ");
    scanf(" %[^\n]", cliente.cpf);
    printf("Digite a nova idade do cliente: ");
    scanf("%d", &cliente.idade);
    printf("Digite o novo endereco do cliente: ");
    scanf(" %[^\n]", cliente.endereco);
    printf("Digite a nova cidade do cliente: ");
    scanf(" %[^\n]", cliente.cidade);
    printf("Digite a nova sigla estado do cliente: ");
    scanf(" %[^\n]", cliente.estado);
    atualizarClientesDB(cliente);
    printf("\n\n");
    printf("Cliente atualizado com sucesso!\n");
}