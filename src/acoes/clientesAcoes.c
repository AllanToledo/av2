#include <stdlib.h>
#include "acoes.h"

const listaAcoes clientesActions = {
        .acoes = (acao[]) {

                //Adicionar outras ações acima desta linha
                {.nome = "Voltar", .acao = NULL}
        },
};

listaAcoes pegarListaClientesAcoes() {
    return clientesActions;
}