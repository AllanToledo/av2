//
// Created by allan on 14/06/2022.
//

#ifndef AV2_ACOES_H
#define AV2_ACOES_H

typedef enum {
    FUNCIONARIO,
    ADMINISTRADOR
} NivelAcesso;

typedef struct acao {
    char *nome;
    NivelAcesso acesso;
    void (*acao)();
} acao;

typedef struct listaAcoes {
    acao *acoes;
} listaAcoes;

acao *pegarListaVeiculosAcoes();
acao *pegarListaClientesAcoes();
acao *pegarListaLocacoesAcoes();

#endif //AV2_ACOES_H
