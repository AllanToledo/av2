#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/*
 * Menu principal, que permite ao usuário escolher entre as opções:
 * 1. Entrar no submenu de locações de veículos
 * 2. Entrar no submenu do cadastro de clientes
 * 3. Entrar no submenu do cadastro de veículos
 */
void subMenu(listaAcoes acoes);

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
                subMenu(pegarListaLocacoesAcoes());
                break;
            case 2:
                subMenu(pegarListaClientesAcoes());
                break;
            case 3:
                subMenu(pegarListaVeiculosAcoes());
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
void subMenu(listaAcoes acoes){
    int opcao;
    do {
        printf("\n\n");
        int quantidadeAcoes = 1; //Começa em 1 porque o último elemento é sempre o "Voltar"
        int i = 0;
        /*
         * Percorre o vetor de opções, imprimindo cada opção.
         * A cada iteração, a quantidade de opções é incrementada.
         * A última opção é um retorno ao menu principal, que possui a ação NULL.
         */
        while(acoes.acoes[i].acao != NULL) {
            printf("%d. %s\n", i + 1, acoes.acoes[i].nome);
            i++; //Poderia usar direto a variavel quantidadeAcoes, mas é melhor para o entendimento usar i
            //já que dentro desse escopo ele representa o índice mesmo
        }
        //Pela lógica, ele sempre sai antes de imprimir a ultima, que é o retorno ao menu principal.
        //Então imprimimos a ultima opção depois do loop.
        printf("%d. %s\n", i + 1, acoes.acoes[i].nome);

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
            acoes.acoes[opcao - 1].acao();
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
