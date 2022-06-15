#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void menuPrincipal() {
    int opcao;
    do {
        printf("\n\n");
        printf("1. Locações\n");
        printf("2. Clientes\n");
        printf("3. Veículos\n");
        printf("9. Sair\n");
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf(" %d", &opcao);
        system("cls");
        switch (opcao) {
            case 1:
                menuLocacoes();
                break;
            case 2:
                menuClientes();
                break;
            case 3:
                menuVeiculos();
                break;
            case 9:
                return;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (1);
}

void menuLocacoes() {
    int opcao;
    do {
        printf("\n\n");
        listaAcoes locacoesActions = pegarListaLocacoesAcoes();
        int quantidadeAcoes = 1;
        int i = 0;
        while(locacoesActions.acoes[i].acao != NULL) {
            printf("%d. %s\n", i + 1, locacoesActions.acoes[i].nome);
            i++;
        }
        printf("%d. %s\n", i + 1, locacoesActions.acoes[i].nome);
        quantidadeAcoes += i;
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf(" %d", &opcao);
        system("cls");
        if(opcao >= 1 && opcao < quantidadeAcoes) {
            locacoesActions.acoes[opcao - 1].acao();
            printf("\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            getchar();
        }
        if (opcao == quantidadeAcoes)
            return;
        system("cls");
    } while (1);
}

void menuClientes() {
    int opcao;
    do {
        printf("\n\n");
        listaAcoes clientesActions = pegarListaClientesAcoes();
        int quantidadeAcoes = 1;
        int i = 0;
        while(clientesActions.acoes[i].acao != NULL) {
            printf("%d. %s\n", i + 1, clientesActions.acoes[i].nome);
            i++;
        }
        printf("%d. %s\n", i + 1, clientesActions.acoes[i].nome);
        quantidadeAcoes += i;
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf(" %d", &opcao);
        system("cls");
        if (opcao >= 1 && opcao < quantidadeAcoes) {
            clientesActions.acoes[opcao - 1].acao();
            printf("\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            getchar();
        }
        if (opcao == quantidadeAcoes)
            return;
        system("cls");
    } while (1);
}

void menuVeiculos() {
    int opcao;
    do {
        printf("\n\n");
        listaAcoes veiculosActions = pegarListaVeiculosAcoes();
        int quantidadeAcoes = 1;
        int i = 0;
        while(veiculosActions.acoes[i].acao != NULL) {
            printf("%d. %s\n", i + 1, veiculosActions.acoes[i].nome);
            i++;
        }
        printf("%d. %s\n", i + 1, veiculosActions.acoes[i].nome);
        quantidadeAcoes += i;
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf(" %d", &opcao);
        system("cls");
        if (opcao >= 1 && opcao < quantidadeAcoes) {
            veiculosActions.acoes[opcao - 1].acao();
            printf("\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            getchar();
        }
        if (opcao == quantidadeAcoes)
            return;
        system("cls");
    } while (1);
}