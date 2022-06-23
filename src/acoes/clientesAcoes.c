#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "acoes.h"
#include "../util/collections.h"
#include "../database/clientes/clientesDB.h"
#include "../util/scan/scan.h"

void cadastrarClientes();

void listarClientes();

void atualizarCliente();

void reverterMudancaCliente();
// Explicação das ações no arquivo veiculosAcoes.c

void removerCliente();

const acao *clientesActions = (acao[]) {
        {.nome = "Cadastrar clientes", .acesso = FUNCIONARIO, .acao = cadastrarClientes},
        {.nome = "Lista clientes", .acesso = FUNCIONARIO, .acao = listarClientes},
        {.nome = "Atualizar cliente", .acesso = FUNCIONARIO, .acao = atualizarCliente},
        {.nome = "Reverter mudança (admin)", .acesso = ADMINISTRADOR, .acao = reverterMudancaCliente},
        {.nome = "Remover cliente (admin)", .acesso = ADMINISTRADOR, .acao = removerCliente},
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

    char stringAux[100];
    printf("Digite APENAS as novas informações do veículo:\n"
           "Sim, ele só vai alterar se a entrada conter algo.\n\n");

    printf("Digite o novo nome do cliente: ");
    scanString(stringAux, 100);
    if(strlen(stringAux) > 0) {
        strcpy(cliente.nome, stringAux);
    }
    printf("Digite o novo CPF do cliente (somente numeros): ");
    scanString(stringAux, 100);
    if(strlen(stringAux) > 0) {
        strcpy(cliente.cpf, stringAux);
    }
    printf("Digite a nova idade do cliente: ");
    scanString(stringAux, 100);
    if(strlen(stringAux) > 0) {
        cliente.idade = atoi(stringAux);
    }
    printf("Digite o novo endereco do cliente: ");
    scanString(stringAux, 100);
    if(strlen(stringAux) > 0) {
        strcpy(cliente.endereco, stringAux);
    }
    printf("Digite a nova cidade do cliente: ");
    scanString(stringAux, 100);
    if(strlen(stringAux) > 0) {
        strcpy(cliente.cidade, stringAux);
    }
    printf("Digite a nova sigla estado do cliente: ");
    scanString(stringAux, 100);
    if(strlen(stringAux) > 0) {
        strcpy(cliente.estado, stringAux);
    }
    atualizarClientesDB(cliente);
    printf("\n\n");
    printf("Cliente atualizado com sucesso!\n");
}

void reverterMudancaCliente() {
    printf("Desfazer mudança irá retornar o arquivo carros.dat para o estado anterior.\n");
    printf("Muito cuidado ao desfazer mudanças, pois pode causar perda de dados.\n");
    printf("Caso tenha adicionado um cliente, ele será deletado.\n");
    printf("Caro tenha alterado um cliente, as alterações serão desfeitas.\n");
    printf("Caso tenha deletado um cliente, ele será restaurado.\n");
    printf("Deseja continuar? (s/n)\n");
    char resposta;
    scanf(" %c", &resposta);
    if (resposta == 's') {
        reverterMudancaClientesDB();
        printf("Mudança desfeita com sucesso!\n");
    } else {
        printf("Mudança não foi desfeita!\n");
    }
}

void removerCliente(){
    ListaClientes *lista = pegarClientesDB();
    if (lista == NULL) {
        printf("Nenhum cliente cadastrado!\n");
        return;
    }
    liberarListaClientes(lista);

    Cliente cliente;
    char cpf[12];
    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]", cpf);
    if(buscarClientePorCPFDB(cpf, &cliente) == FALSE) {
        printf("Cliente nao encontrado!\n");
        return;
    }
    printCliente(cliente);
    printf("\n");

    printf("Digite EXCLUIR para remover o cliente.\n");
    char resposta[8];
    scanf(" %[^\n]", resposta);
    if(strcmp(resposta, "EXCLUIR") == 0) {
        removerClientesDB(cliente);
        printf("Cliente removido com sucesso!\n");
    } else {
        printf("Cliente não foi removido!\n");
    }
}