#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acoes.h"
#include "../database/locacoes/locacoesDB.h"
#include "../database/clientes/clientesDB.h"
#include "../database/veiculos/veiculosDB.h"
#include "../util/scan/scan.h"

// Explicação das funções no arquivo veiculosAcoes.c

void criarLocacao();

void listarTodasLocacoes();

void listarTodasLocacoesAbertas();

void finalizarLocacao();

void reverterMudancaLocacao();


const acao *locacoesActions = (acao[]) {
        {.nome = "Criar locação", .acesso = FUNCIONARIO, .acao = criarLocacao},
        {.nome = "Listar todas locações", .acesso = FUNCIONARIO, .acao = listarTodasLocacoes},
        {.nome = "Listar todas locações em aberto", .acesso = FUNCIONARIO, .acao = listarTodasLocacoesAbertas},
        {.nome = "Finalizar locação", .acesso = FUNCIONARIO, .acao = finalizarLocacao},
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

    ListaVeiculo *lista = pegarVeiculosDB();
    ListaVeiculo *aux = lista;
    if (lista == NULL) {
        printf("Não possui veículos cadastrados.");
        return;
    }

    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]s", cpf);
    Cliente cliente;
    if (buscarClientePorCPFDB(cpf, &cliente) == 0) {
        printf("Cliente não cadastrado");
        return;
    }


    float motor;
    int possuiArCondicionado;

    printf("Selecione a motorização: \n");
    char motores[][4] = {"1.0", "1.6", "1.8"};
    char stringAux[4] = "";
    scanSelection(stringAux, 3, 4, motores);
    motor = atof(stringAux);
    printf("Motor selecionado: %.1f\n", motor);

    printf("Selecione se possui Ar-Condicionado: \n");
    char opcoes[][4] = {"Sim", "Nao"};
    scanSelection(stringAux, 2, 4, opcoes);
    possuiArCondicionado = strcmp(stringAux, "Sim") == 0;
    printf("Opção selecionada: %s\n", stringAux);


    Veiculo veiculo;
    do {
        veiculo = aux->veiculo;
        if (veiculo.disponivel == FALSE) continue;
        int veiculoCombinaMotor = veiculo.motor == motor;
        int veiculoCombinaArC = veiculo.arCondicionado == possuiArCondicionado;
        if (veiculoCombinaArC && veiculoCombinaMotor) {
            break;
        }
    } while ((aux = aux->proximo) != NULL);

    if (aux == NULL) {
        printf("Não há carro disponível.");
        return;
    }

    liberarListaVeiculos(lista);

    printVeiculoCabecalho();
    printVeiculo(veiculo);

    Locacao locacao = {
            .idCarro = veiculo.id,
            .quilometragemInicial = veiculo.quilometragem,
            .quilometragemFinal = 0,
            .valor = 0,
            .inicio = pegarDataAtual(),
            .devolucao = {0, 0, 0, 0}
    };
    strcpy(locacao.cpfCliente, cpf);
    veiculo.disponivel = FALSE;
    inserirLocacaoDB(locacao);
    atualizarVeiculoDB(veiculo);
    printf("\nLocação feita com sucesso!!\n\n");
}

void listarTodasLocacoes() {
    ListaLocacoes *lista = pegarLocacoesDB();
    if (lista == NULL) {
        printf("Locações estão vazias");
        return;
    }
    ListaLocacoes *aux = lista;
    do {
        Locacao locacao = aux->locacao;
        printLocacao(locacao);
        printf("\n");
    } while ((aux = aux->proximo) != NULL);
    liberarListaLocacoes(lista);
}

void listarTodasLocacoesAbertas() {
    ListaLocacoes *lista = pegarLocacoesDB();
    if (lista == NULL) {
        printf("Locações estão vazias");
        return;
    }
    ListaLocacoes *aux = lista;
    do {
        Locacao locacao = aux->locacao;
        if (dataVazia(locacao.devolucao))
            printLocacao(locacao);
        printf("\n");
    } while ((aux = aux->proximo) != NULL);
    liberarListaLocacoes(lista);
}

void finalizarLocacao() {
    int id;
    printf("Digite o ID da Locação: ");
    scanf(" %d", &id);
    ListaLocacoes *locacoes = pegarLocacoesDB();
    if (locacoes == NULL) {
        printf("Locações estão vazias.\n");
        return;
    }

    Locacao locacao;
    ListaLocacoes *aux = locacoes;
    do {
        locacao = aux->locacao;
        if (locacao.id == id && dataVazia(locacao.devolucao)) break;
    } while ((aux = aux->proximo) != NULL);
    liberarListaLocacoes(locacoes);
    if (aux == NULL) {
        printf("Locação não encontrada.\n");
        return;
    }

    Cliente cliente;
    if (buscarClientePorCPFDB(locacao.cpfCliente, &cliente) == 0) {
        printf("Erro: Cliente não cadastrado.\n");
        return;
    }

    Veiculo veiculo;
    if(buscarVeiculoPorIDDB(locacao.idCarro, &veiculo) == 0) {
        printf("Erro: Veiculo não cadastrado.");
        return;
    }

    printLocacao(locacao);
    printf("\n\n");

    int quilometragemFinal;
    printf("Digite a quilometragem final: ");
    scanf("%d", &quilometragemFinal);
    veiculo.quilometragem = quilometragemFinal;
    locacao.quilometragemFinal = quilometragemFinal;
    veiculo.disponivel = TRUE;
    printf("Digite a data de entrega (dd/mm/aaaa hh): ");
    Data devolucao;
    scanf(" %d/%d/%d %d", &devolucao.dia, &devolucao.mes, &devolucao.ano, &devolucao.hora);
    locacao.devolucao = devolucao;

    int diferenca = diferencaEmHoras(locacao.inicio, locacao.devolucao);
    float custo = ((float) diferenca) * (veiculo.valorDiaria / 24.0);
    locacao.valor = custo;
    cliente.pontos += (int) custo;

    atualizarLocacaoDB(locacao);
    atualizarVeiculoDB(veiculo);
    atualizarClientesDB(cliente);

    printf("Locação finalizada com sucesso!!\n\n");
}