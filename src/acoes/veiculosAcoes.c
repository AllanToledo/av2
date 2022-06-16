#include <stdio.h>
#include <string.h>
#include <time.h>
#include "acoes.h"
#include "../util/collections.h"
#include "../database/veiculos/veiculosDB.h"

void cadastrarVeiculo();

void listarVeiculos();

void atualizarVeiculo();

void deletarVeiculo();

void listarVeiculosVelhos();

/*
 * Menu de locações, que permite ao usuário escolher entre as opções:
 * 1. Cadastrar um novo veículo
 * 2. Listar todos os veículos
 * 3. Atualizar um veículo
 * 4. Deletar um veículo
 * 5. Listar veículos velhos
 * E a ultima é para voltar ao menu principal.
 *
 * listaAcoes é uma estrutura que contém um vetor de funções, que são chamadas
 * ao digitar a opção desejada.
 */

const acao *veiculoActions = (acao[]) {
        {.nome = "Cadastrar Veiculo", .acao = cadastrarVeiculo},
        {.nome = "Listar Veiculos", .acao = listarVeiculos},
        {.nome = "Atualizar Veiculo", .acao = atualizarVeiculo},
        {.nome = "Remover Veiculo", .acao = deletarVeiculo},
        {.nome = "Listar Veiculo Velhos", .acao = listarVeiculosVelhos},

        //Adicionar outras ações acima
        {.nome = "Voltar", .acao = NULL}

};

acao *pegarListaVeiculosAcoes() {
    return veiculoActions;
}


void cadastrarVeiculo() {
    Veiculo veiculo;
    printf("Digite o modelo do veículo: ");
    scanf(" %s", veiculo.modelo);
    printf("Digite a cor do veículo (0 = Preto, 1 = Prata): ");
    int cor;
    scanf("%d", &cor);
    if (cor == 0) {
        strcpy(veiculo.cor, "Preto");
    } else {
        strcpy(veiculo.cor, "Prata");
    }
    printf("Digite o motor do veículo (1.0, 1.6 ou 1.8): ");
    scanf(" %f", &veiculo.motor);
    printf("Digite o ano de fabricação do veículo: ");
    scanf(" %d", &veiculo.anoFabricacao);
    printf("Digite a placa do veículo: ");
    scanf(" %s", veiculo.placa);
    printf("Digite 1 se o veículo possui ar condicionado, 0 caso contrário: ");
    scanf(" %d", &veiculo.arCondicionado);
    printf("Digite a quilometragem do veículo: ");
    scanf(" %d", &veiculo.quilometragem);
    printf("Digite o valor da diária do veículo: ");
    scanf(" %f", &veiculo.valorDiaria);
    veiculo.disponivel = TRUE;
    inserirVeiculoDB(veiculo);
    printf("Veículo cadastrado com sucesso!\n");
}

void listarVeiculos() {
    printf("Veículos cadastrados:\n\n");
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL) {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    printVeiculoCabecalho();
    do {
        Veiculo veiculo = listaVeiculos->veiculo;
        printVeiculo(veiculo);
    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
}

void atualizarVeiculo() {
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL) {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    printf("Digite a placa do veículo: ");
    char placa[8];
    scanf(" %s", placa);
    Veiculo veiculo;
    int achou = FALSE;
    do {
        veiculo = listaVeiculos->veiculo;
        int placaIgual = strcmp(placa, veiculo.placa) == 0;
        if (placaIgual) {
            achou = TRUE;
            break;
        }
    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
    if (!achou) {
        printf("Veículo não encontrado.\n");
        return;
    }
    printVeiculoCabecalho();
    printVeiculo(veiculo);
    printf("\n");

    printf("Digite as novas informações do veículo:\n\n");

    printf("Digite o modelo do veículo: ");
    scanf(" %s", veiculo.modelo);
    printf("Digite a cor do veículo (0 = Preto, 1 = Prata): ");
    int cor;
    scanf(" %d", &cor);
    if (cor == 0) {
        strcpy(veiculo.cor, "Preto");
    } else {
        strcpy(veiculo.cor, "Prata");
    }
    printf("Digite o motor do veículo (1.0, 1.6 ou 1.8): ");
    scanf(" %f", &veiculo.motor);
    printf("Digite o ano de fabricação do veículo: ");
    scanf(" %d", &veiculo.anoFabricacao);
    printf("Digite a placa do veículo: ");
    scanf(" %s", veiculo.placa);
    printf("Digite 1 se o veículo possui ar condicionado, 0 caso contrário: ");
    scanf(" %d", &veiculo.arCondicionado);
    printf("Digite a quilometragem do veículo: ");
    scanf(" %d", &veiculo.quilometragem);
    printf("Digite o valor da diária do veículo: ");
    scanf(" %f", &veiculo.valorDiaria);
    atualizarVeiculoDB(veiculo);
    printf("Veículo atualizado com sucesso!\n");
}

void deletarVeiculo() {
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL) {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    printf("Digite a placa do veículo: ");
    char placa[8];
    scanf(" %s", placa);
    Veiculo veiculo;
    int achou = FALSE;
    do {
        veiculo = listaVeiculos->veiculo;
        int placaIgual = strcmp(placa, veiculo.placa) == 0;
        if (placaIgual) {
            achou = TRUE;
            break;
        }
    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
    if (!achou) {
        printf("Veículo não encontrado.\n");
        return;
    }
    printVeiculoCabecalho();
    printVeiculo(veiculo);
    printf("\n");
    printf("Digite EXCLUIR para confirmar a exclusão do veículo.\n");
    char confirmacao[8];
    scanf(" %s", confirmacao);
    if (strcmp(confirmacao, "EXCLUIR") != 0) {
        printf("Exclusão cancelada.\n");
        return;
    }
    removerVeiculoDB(veiculo);
    printf("Veículo removido com sucesso!\n");
}

//função que retorna o ano atual
int pegarAnoAtual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}


void listarVeiculosVelhos() {
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL) {
        printf("Não há veículos cadastrados.\n");
        return;
    }

    int anoAtual = pegarAnoAtual();

    printf("Veículos fabricados antes de %d:\n", anoAtual - 3);
    printVeiculoCabecalho();
    do {
        Veiculo veiculo = listaVeiculos->veiculo;
        if ((anoAtual - veiculo.anoFabricacao) <= 3) continue;
        printVeiculo(veiculo);
    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
}