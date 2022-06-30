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

void listarPorCliente();


const acao *locacoesActions = (acao[]) {
        {.nome = "Criar locação", .acesso = FUNCIONARIO, .acao = criarLocacao},
        {.nome = "Listar todas locações", .acesso = FUNCIONARIO, .acao = listarTodasLocacoes},
        {.nome = "Listar todas locações em aberto", .acesso = FUNCIONARIO, .acao = listarTodasLocacoesAbertas},
        {.nome = "Listar todas locações de um cliente", .acesso = FUNCIONARIO, .acao = listarPorCliente},
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
    if (buscarVeiculoPorIDDB(locacao.idCarro, &veiculo) == 0) {
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

void listarPorCliente() {
    printf("Deseja buscar por NOME ou CPF?\n");
    char opcoes[2][5] = {"CPF", "NOME"};
    char escolha[5] = "\0";
    scanSelection(escolha, 2, 5, opcoes);
    printf("Selecionado: %s\n\n", escolha);

    Cliente cliente;
    int compararCPF = strcmp(escolha, "CPF") == 0;
    char busca[50];
    printf("Digite o %s: ", compararCPF ? "CPF" : "NOME");
    scanf(" %[^\n]s", busca);
    int encontrouCliente;
    if (compararCPF) {
        encontrouCliente = buscarClientePorCPFDB(busca, &cliente);
    } else {
        encontrouCliente = buscarClientePorNomeDB(busca, &cliente);
    }
    if (!encontrouCliente) {
        printf("\n\nCliente não encontrado\n\n");
        return;
    }

    printf("\nNome cliente: %s\n\n", cliente.nome);

    ListaLocacoes *listaLocacoes = pegarLocacoesDB();
    if (listaLocacoes == NULL) {
        printf("\n\nNenhuma locação cadastrada.\n\n");
    }
    ListaLocacoes *aux = listaLocacoes;
    int vazia = 1;
    do {
        Locacao locacao = aux->locacao;
        if (strcmp(locacao.cpfCliente, cliente.cpf) != 0) continue;
        vazia = 0;

        Veiculo veiculo;
        if (buscarVeiculoPorIDDB(locacao.idCarro, &veiculo) == 0) {
            printf("Erro ao carregar dados do veículos.\n");
        } else {
            printf("Placa: %s\n", veiculo.placa);
        }
        Data data = locacao.inicio;
        printf("Data Inicial: %d/%d/%d %d:00\n", data.dia, data.mes, data.ano, data.hora);
        data = locacao.devolucao;
        printf("Data Final: %d/%d/%d %d:00\n", data.dia, data.mes, data.ano, data.hora);
        printf("Valor: R$ %.2f\n", locacao.valor);
    } while ((aux = aux->proximo) != NULL);
    liberarListaLocacoes(listaLocacoes);
    if (vazia) {
        printf("Este cliente não possui nenhuma locação.\n\n");
    }
}