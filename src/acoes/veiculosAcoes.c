#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "acoes.h"
#include "../util/collections.h"
#include "../database/veiculos/veiculosDB.h"
#include "../util/scan/scan.h"
#include "../database/vendas/vendasDB.h"

void cadastrarVeiculo();

void listarVeiculos();

void atualizarVeiculo();

void deletarVeiculo();

void listarVeiculosVelhos();

void reverterMudancaVeiculos();

void listarVeiculosDisponivelLocacao();

void listarVeiculosEmprestados();

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

const acao *veiculoActions = (acao[]){
    {.nome = "Cadastrar Veiculo", .acesso = FUNCIONARIO, .acao = cadastrarVeiculo},
    {.nome = "Listar Veiculos", .acesso = FUNCIONARIO, .acao = listarVeiculos},
    {.nome = "Listar Veiculo Velhos", .acesso = FUNCIONARIO, .acao = listarVeiculosVelhos},
    {.nome = "Atualizar Veiculo", .acesso = FUNCIONARIO, .acao = atualizarVeiculo},
    {.nome = "Listar veiculos disponível para locação", .acesso = FUNCIONARIO, .acao = listarVeiculosDisponivelLocacao},
    {.nome = "Listar veículos locados", .acesso = FUNCIONARIO, .acao = listarVeiculosEmprestados},
    {.nome = "Reverter Mudança (admin)", .acesso = ADMINISTRADOR, .acao = reverterMudancaVeiculos},
    {.nome = "Remover Veiculo (admin)", .acesso = ADMINISTRADOR, .acao = deletarVeiculo},

    // Adicionar outras ações acima
    {.nome = "Voltar", .acao = NULL}

};

acao *pegarListaVeiculosAcoes()
{
    return veiculoActions;
}

void reverterMudancaVeiculos()
{
    printf("Desfazer mudança irá retornar o arquivo carros.dat para o estado anterior.\n");
    printf("Muito cuidado ao desfazer mudanças, pois pode causar perda de dados.\n");
    printf("Caso tenha adicionado um carro, ele será deletado.\n");
    printf("Caro tenha alterado um carro, as alterações serão desfeitas.\n");
    printf("Caso tenha deletado um carro, ele será restaurado.\n");
    printf("Deseja continuar? (s/n)\n");
    char resposta;
    scanf(" %c", &resposta);
    if (resposta == 's')
    {
        reverterMudancaVeiculoDB();
        printf("Mudança desfeita com sucesso!\n");
    }
    else
    {
        printf("Mudança não foi desfeita!\n");
    }
}

void cadastrarVeiculo()
{
    Veiculo veiculo;
    //----------------------------------------------------------
    printf("Selecione o modelo do veiculo: \n");
    char modelos[][10] = {"Uno", "Polo", "Corolla"};
    scanSelection(veiculo.modelo, 3, 10, modelos);
    printf("Modelo Selecionado: %s\n", veiculo.modelo);
    //-----------------------------------------------------------
    printf("Selecione a cor do veículo: \n");
    char cores[][6] = {"Preto", "Prata"};
    scanSelection(veiculo.cor, 2, 6, cores);
    printf("Cor selecionada: %s\n", veiculo.cor);
    //-----------------------------------------------------------
    printf("Selecione a motorização: \n");
    char motores[][4] = {"1.0", "1.6", "1.8"};
    char stringAux[4] = "";
    scanSelection(stringAux, 3, 4, motores);
    veiculo.motor = atof(stringAux);
    printf("Motor selecionado: %.1f\n", veiculo.motor);
    //----------------------------------------------------------
    printf("Digite o ano de fabricação do veículo: ");
    scanf(" %d", &veiculo.anoFabricacao);
    //---------------------------------------------------------
    printf("Digite a placa do veículo: ");
    scanf(" %s", veiculo.placa);
    //---------------------------------------------------------
    printf("Selecione se possui Ar-Condicionado: \n");
    char opcoes[][4] = {"Sim", "Nao"};
    scanSelection(stringAux, 2, 4, opcoes);
    veiculo.arCondicionado = strcmp(stringAux, "Sim") == 0;
    printf("Opção selecionada: %s\n", stringAux);
    //--------------------------------------------------------
    printf("Digite a quilometragem do veículo: ");
    scanf(" %d", &veiculo.quilometragem);
    //--------------------------------------------------------
    printf("Digite o valor da diária do veículo: ");
    scanf(" %f", &veiculo.valorDiaria);
    //----------------------------------------------------
    veiculo.disponivel = TRUE;
    inserirVeiculoDB(veiculo);
    printf("Veículo cadastrado com sucesso!\n");
}

void listarVeiculos()
{
    printf("Veículos cadastrados:\n\n");
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL)
    {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    printVeiculoCabecalho();
    do
    {
        Veiculo veiculo = listaVeiculos->veiculo;
        printVeiculo(veiculo);
    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
}

void atualizarVeiculo()
{
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL)
    {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    printf("Digite a placa do veículo: ");
    char placa[8];
    scanf(" %s", placa);
    Veiculo veiculo;
    if (buscarVeiculoPorPlacaDB(placa, &veiculo) == FALSE)
    {
        printf("Veículo não encontrado.\n");
        return;
    }
    printVeiculoCabecalho();
    printVeiculo(veiculo);
    printf("\n");
    char stringAux[100];
    printf("Digite APENAS as novas informações do veículo:\n"
           "Sim, ele só vai alterar se a entrada conter algo.\n\n");
    //----------------------------------------------
    printf("Digite o modelo do veículo: \n");
    char modelos[][10] = {"", "Uno", "Polo", "Corolla"};
    scanSelection(stringAux, 4, 10, modelos);
    if (strlen(stringAux) > 0)
    {
        strcpy(veiculo.modelo, stringAux);
    }
    //--------------------------------------------
    printf("Selecione a cor: \n");
    char cores[][10] = {"", "Preto", "Prata"};
    scanSelection(stringAux, 3, 10, cores);
    if (strlen(stringAux) > 0)
    {
        strcpy(veiculo.cor, stringAux);
    }
    //--------------------------------------------------------
    printf("Selecione o motor do veículo: \n");
    char motores[][4] = {"", "1.0", "1.6", "1.8"};
    scanSelection(stringAux, 4, 4, motores);
    if (strlen(stringAux) > 0)
    {
        veiculo.motor = atof(stringAux);
    }
    //--------------------------------------------------------
    printf("Digite o ano de fabricação do veículo: ");
    scanString(stringAux, 100);
    if (strlen(stringAux) > 0)
    {
        veiculo.anoFabricacao = atoi(stringAux);
    }
    //--------------------------------------------------------
    printf("Digite a placa do veículo: ");
    scanString(stringAux, 100);
    if (strlen(stringAux) > 0)
    {
        strcpy(veiculo.placa, stringAux);
    }
    //-------------------------------------------------------
    printf("Possui ar condicinado?\n ");
    char opcoes[][4] = {"", "Sim", "Nao"};
    scanSelection(stringAux, 3, 4, opcoes);
    if (strlen(stringAux) > 0)
    {
        veiculo.arCondicionado = strcmp(stringAux, "Sim") == 0 ? 1 : 0;
    }
    //---------------------------------------------------------
    printf("Digite a quilometragem do veículo: ");
    scanString(stringAux, 100);
    if (strlen(stringAux) > 0)
    {
        veiculo.quilometragem = atoi(stringAux);
    }
    //-----------------------------------------------------------
    printf("Digite o valor da diária do veículo: ");
    scanString(stringAux, 100);
    if (strlen(stringAux) > 0)
    {
        veiculo.valorDiaria = atof(stringAux);
    }
    //------------------------------------------------------------
    atualizarVeiculoDB(veiculo);
    printf("Veículo atualizado com sucesso!\n");
}

void deletarVeiculo()
{
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL)
    {
        printf("Não há veículos cadastrados.\n");
        return;
    }
    printf("Digite a placa do veículo: ");
    char placa[8];
    scanf(" %s", placa);
    Veiculo veiculo;
    if (buscarVeiculoPorPlacaDB(placa, &veiculo) == FALSE)
    {
        printf("Veículo não encontrado.\n");
        return;
    }
    //    int achou = FALSE;
    //    do {
    //        veiculo = listaVeiculos->veiculo;
    //        int placaIgual = strcmp(placa, veiculo.placa) == 0;
    //        if (placaIgual) {
    //            achou = TRUE;
    //            break;
    //        }
    //    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    //    liberarListaVeiculos(listaVeiculos);
    //    if (!achou) {
    //        printf("Veículo não encontrado.\n");
    //        return;
    //    }
    printVeiculoCabecalho();
    printVeiculo(veiculo);
    printf("\n");
    printf("Digite EXCLUIR para confirmar a exclusão do veículo.\n");
    char confirmacao[8];
    scanf(" %s", confirmacao);
    if (strcmp(confirmacao, "EXCLUIR") != 0)
    {
        printf("Exclusão cancelada.\n");
        return;
    }
    removerVeiculoDB(veiculo);
    printf("Veículo removido com sucesso!\n");
}

// função que retorna o ano atual
int pegarAnoAtual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

void listarVeiculosVelhos()
{
    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    if (listaVeiculos == NULL)
    {
        printf("Não há veículos cadastrados.\n");
        return;
    }

    int anoAtual = pegarAnoAtual();
    limparVendas();
    printf("Veículos fabricados antes de %d:\n", anoAtual - 3);
    printVeiculoCabecalho();
    do
    {
        Veiculo veiculo = listaVeiculos->veiculo;
        if ((anoAtual - veiculo.anoFabricacao) <= 3)
            continue;
        inserirVenda(veiculo);
        printVeiculo(veiculo);
    } while ((listaVeiculos = listaVeiculos->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
}

void listarVeiculosDisponivelLocacao()
{

    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    int ordem = 1;
    if (listaVeiculos == NULL)
    {
        printf("Não há nenhum modelo de veículo disponível.\n");
        return;
    }

    ListaVeiculo *aux = listaVeiculos;
    printf("Qual modelo de veículo deseja locar? \n");
    char modelo[10];
    scanf(" %[^\n]s ", modelo);
    do
    {
        Veiculo veiculo = aux->veiculo;
        if (veiculo.disponivel && strcmp(veiculo.modelo, modelo) == 0)
        {
            printf("%d - Veiculo ", ordem);
            printf("Placa: %s \n", veiculo.placa);
            printf("Modelo %s \n", veiculo.modelo);
            printf("Cor: %d \n", veiculo.cor);
            printf("Ar condicionado: %s \n", veiculo.arCondicionado ? "sim" : "não");
            ordem++;
        }
    } while ((aux = aux->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
}

void listarVeiculosEmprestados()
{

    ListaVeiculo *listaVeiculos = pegarVeiculosDB();
    int ordem = 1;
    int total = 0;
    int locado = 0;

    if (listaVeiculos == NULL)
    {
        printf("Não há veículos locados.\n");
        return;
    }

    ListaVeiculo *aux = listaVeiculos;
    printf("Lista dos veículos locados.\n");
    do
    {
        total++;
        Veiculo veiculo = aux->veiculo;
        if (!veiculo.disponivel)
        {
            printf("%d - Veiculo", ordem);
            printf("Placa: %s \n", veiculo.placa);
            printf("Modelo %s \n", veiculo.modelo);
            printf("Cor: %d \n", veiculo.cor);
            ordem++;
            locado++;
        }
    } while ((aux = aux->proximo) != NULL);
    liberarListaVeiculos(listaVeiculos);
    printf("Total de veículos locados: %d \n", locado);
    printf("Total de veículos: %d \n", total);
}
