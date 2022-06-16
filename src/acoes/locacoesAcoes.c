#include <stdio.h>
#include "acoes.h"

// Explicação das funções no arquivo veiculosAcoes.c

const acao *locacoesActions = (acao[]) {

        // Adicionar outras ações acima desta linha
        {.nome = "Voltar", .acao = NULL}
};


acao *pegarListaLocacoesAcoes() {
    return locacoesActions;
}