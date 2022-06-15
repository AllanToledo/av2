#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/*
 * Menu principal, que permite ao usuário escolher entre as opções:
 * 1. Entrar no submenu de locações de veículos
 * 2. Entrar no submenu do cadastro de clientes
 * 3. Entrar no submenu do cadastro de veículos
 */
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
        system("cls"); // Limpa a tela, diminui a poluição do console
        /*
         * Verifica se a opção escolhida é válida, se não for, o usuário é
         * informado e o menu é exibido novamente.
         */
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

/*
 * Os submenus utilizam um esquema dinâmico de opções, onde cada opção é
 * pegada do vetor de opções.
 * O vetor de opções é inicializado no início do programa, no arquivo de ações.
 */

void menuLocacoes() {
    int opcao;
    do {
        printf("\n\n");
        listaAcoes locacoesActions = pegarListaLocacoesAcoes();
        int quantidadeAcoes = 1; //Começa em 1 porque o último elemento é o "Voltar"
        int i = 0;
        /*
         * Percorre o vetor de opções, imprimindo cada opção.
         * A cada iteração, a quantidade de opções é incrementada.
         * A última opção é um retorno ao menu principal, que possui a ação NULL.
         */
        while(locacoesActions.acoes[i].acao != NULL) {
            printf("%d. %s\n", i + 1, locacoesActions.acoes[i].nome);
            i++; //Poderia usar direto a variavel quantidadeAcoes, mas é melhor para o entendimento usar i
            //já que dentro desse escopo ele representa o índice mesmo
        }
        //Pela lógica, ele sempre sai antes de imprimir a ultima, que é o retorno ao menu principal.
        //Então imprimimos a ultima opção depois do loop.
        printf("%d. %s\n", i + 1, locacoesActions.acoes[i].nome);

        quantidadeAcoes += i;
        printf("\n");
        printf("Digite a opção desejada: ");
        scanf(" %d", &opcao);
        system("cls");
        /*
         * Verifica se a opção escolhida é válida e executa, se não for,
         * o menu é exibido novamente.
         */
        if(opcao >= 1 && opcao < quantidadeAcoes) {
            //Pega a ação da posição opcao - 1, pois o índice começa em 0
            locacoesActions.acoes[opcao - 1].acao();
            //Para não limpar a tela após a execução da ação, o loop é interrompido.
            printf("\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            getchar();
        }
        /*
         * Se a opção escolhida for a última, então o usuário é retornado ao menu principal.
         */
        if (opcao == quantidadeAcoes)
            return;
        system("cls");
    } while (1);
}

/*
 * A mesma lógica do menuLocacoes, porém com a lista de ações para clientes.
 */
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