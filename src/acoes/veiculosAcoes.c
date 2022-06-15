#include <stdio.h>
#include <string.h>
#include "acoes.h"
#include "../util/collections.h"
#include "../database/veiculos/veiculosDB.h"

void cadastrarVeiculo();
void listarVeiculos();
void atualizarVeiculo();


const listaAcoes veiculoActions = {
        .acoes = (acao[]) {
                {.nome = "Cadastrar Veiculo", .acao = cadastrarVeiculo},
                {.nome = "Listar Veiculos", .acao = listarVeiculos},
                {.nome = "Atualizar Veiculo", .acao = atualizarVeiculo},

                    //Adicionar outras ações acima
                {.nome = "Voltar", .acao = NULL}
        },
};

listaAcoes pegarListaVeiculosAcoes() {
    return veiculoActions;
}


void cadastrarVeiculo() {
    Veiculo veiculo;
    printf("Digite o modelo do veículo: ");
    scanf(" %s", veiculo.modelo);
    printf("Digite a cor do veículo: ");
    scanf(" %s", veiculo.cor);
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
    do {
        Veiculo veiculo = listaVeiculos->veiculo;
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Cor: %s\n", veiculo.cor);
        printf("Motor: %.1f\n", veiculo.motor);
        printf("Ano de fabricação: %d\n", veiculo.anoFabricacao);
        printf("Placa: %s\n", veiculo.placa);
        printf("Ar condicionado: %s\n", veiculo.arCondicionado ? "sim" : "não");
        printf("Quilometragem: %dKm\n", veiculo.quilometragem);
        printf("Valor da diária: R$%.2f\n", veiculo.valorDiaria);
        printf("Disponível: %s\n", veiculo.disponivel ? "sim" : "não");
        printf("\n");
    } while ((listaVeiculos = listaVeiculos->next) != NULL);
    liberarListaVeiculos(listaVeiculos);
}

void atualizarVeiculo() {
    printf("Digite a placa do veículo: ");
    char placa[8];
    scanf(" %s", placa);
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL) {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    Veiculo veiculo;
    int achou = FALSE;
    do {
        veiculo = listaVeiculos->veiculo;
        int placaIgual = strcmp(placa, veiculo.placa) == 0;
        if (placaIgual) {
            achou = TRUE;
            break;
        }
    } while ((listaVeiculos = listaVeiculos->next) != NULL);
    liberarListaVeiculos(listaVeiculos);
    if (!achou) {
        printf("Veículo não encontrado.\n");
        return;
    }
    printf("Veículo encontrado:\n");
    printf("Modelo: %s\n", veiculo.modelo);
    printf("Cor: %s\n", veiculo.cor);
    printf("Motor: %.1f\n", veiculo.motor);
    printf("Ano de fabricação: %d\n", veiculo.anoFabricacao);
    printf("Placa: %s\n", veiculo.placa);
    printf("Ar condicionado: %s\n", veiculo.arCondicionado ? "sim" : "não");
    printf("Quilometragem: %dKm\n", veiculo.quilometragem);
    printf("Valor da diária: R$%.2f\n", veiculo.valorDiaria);
    printf("Disponível: %s\n", veiculo.disponivel ? "sim" : "não");
    printf("\n");

    printf("Digite as novas informações do veículo:\n\n");

    printf("Digite o modelo do veículo: ");
    scanf(" %s", veiculo.modelo);
    printf("Digite a cor do veículo: ");
    scanf(" %s", veiculo.cor);
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