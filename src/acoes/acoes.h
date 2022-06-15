//
// Created by allan on 14/06/2022.
//

#ifndef AV2_ACOES_H
#define AV2_ACOES_H

typedef struct acao {
    char *nome;
    void (*acao)();
} acao;

typedef struct listaAcoes {
    acao *acoes;
} listaAcoes;

listaAcoes pegarListaVeiculosAcoes();
listaAcoes pegarListaClientesAcoes();
listaAcoes pegarListaLocacoesAcoes();

#endif //AV2_ACOES_H
