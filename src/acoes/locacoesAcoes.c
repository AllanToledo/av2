#include <stdio.h>
#include "acoes.h"
#include "../database/locacoes/locacoesDB.h"

// Explicação das funções no arquivo veiculosAcoes.c

void reverterMudancaLocacao();

const acao *locacoesActions = (acao[]) {

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