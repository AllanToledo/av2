#include <stdio.h>
#include "acoes.h"

// Explicação das funções no arquivo veiculosAcoes.c

const listaAcoes locacoesActions = {
    .acoes = (acao[]){

        // Adicionar outras ações acima desta linha
        {.nome = "Voltar", .acao = NULL}},
};

listaAcoes pegarListaLocacoesAcoes()
{
        return locacoesActions;
}