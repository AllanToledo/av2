#include <stdio.h>
#include "acoes.h"
#include "../database/locacoes/locacoesDB.h"
#include "../database/clientes/clientesDB.h"

// Explicação das funções no arquivo veiculosAcoes.c

void criarLocacao();

void reverterMudancaLocacao();

const acao *locacoesActions = (acao[]) {

        {.nome = "Criar locação", .acesso = FUNCIONARIO, .acao = criarLocacao},
        {.nome = "Reverter mudança (admin)", .acesso = ADMINISTRADOR, .acao = reverterMudancaLocacao},

        // Adicionar outras ações acima desta linha
        {.nome = "Voltar", .acao = NULL}
};


acao *pegarListaLocacoesAcoes() {
    return locacoesActions;
}

void reverterMudancaLocacao() {
    printf("Desfazer mudança irá retornar o arquivo carros.dat para o estado anterior.\n");
    printf("Muito cuidado ao desfazer mudanças, pois pode causar perda de dados.\n");
    printf("Caso tenha adicionado uma locação, ela será deletada.\n");
    printf("Caro tenha alterado uma locação, as alterações serão desfeitas.\n");
    printf("Caso tenha deletado uma locação, ela será restaurada.\n");
    printf("Deseja continuar? (s/n)\n");
    char resposta;
    scanf(" %c", &resposta);
    if (resposta == 's') {
        reverterMudancaLocacaoDB();
        printf("Mudança desfeita com sucesso!\n");
    } else {
        printf("Mudança não foi desfeita!\n");
    }
}

void criarLocacao() {
    char cpf[12];
    printf("Digite o CPF do cliente");
    scanf(" %[^\n]s", cpf);
    Cliente cliente;
    if(buscarClientePorCPFDB(cpf, &cliente) == 0){
        printf("Cliente não cadastrado");
        return;
    }
    printf("Escolha o tipo de motor (1.0, 1.6, 1.8)");
}