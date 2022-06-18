#include "structs.h"
#include <stdio.h>

int diasDesdeAnoZero(int ano, Data data);

int diferencaEmHoras(Data inicio, Data fim) {
    int diferenca = 0;
    int diaAbsolutoInicio = diasDesdeAnoZero(inicio.ano, inicio);
    int diaAbsolutoFim = diasDesdeAnoZero(inicio.ano, fim);

    diferenca += (diaAbsolutoFim - diaAbsolutoInicio) * 24;
    diferenca += (fim.hora - inicio.hora);
    return diferenca;
}

int diasDesdeAnoZero(int ano, Data data) {
    int dias = 0;
    for (int anoAtual = ano; anoAtual <= data.ano; anoAtual++) {
        int anoBissexto = anoAtual % 4 == 0 && anoAtual % 100 != 0 || anoAtual % 400 == 0;
        int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (anoBissexto) {
            meses[1] = 29;
        }
        for (int i = 0; i < data.mes - 1; i++) {
            dias += meses[i];
        }
        dias += data.dia;
    }
    return dias;
}

void printCliente(Cliente cliente) {
    printf("Nome: %s\n", cliente.nome);
    printf("CPF: %s\n", cliente.cpf);
    printf("Idade: %d\n", cliente.idade);
    printf("Endereco: %s\n", cliente.endereco);
    printf("Cidade: %s\n", cliente.cidade);
    printf("Estado: %s\n", cliente.estado);
    printf("Pontos: %d\n", cliente.pontos);
}

void printVeiculoCabecalho() {
    printf("|ID|Modelo| Cor |Motor| Ano| Placa |Ar C|Quilometragem|Valor D.|Disp|\n");
}

void printVeiculo(Veiculo veiculo) {
    printf("|%2d", veiculo.id);
    printf("|%6s", veiculo.modelo);
    printf("|%5s", veiculo.cor);
    printf("| %.1f ", veiculo.motor);
    printf("|%d", veiculo.anoFabricacao);
    printf("|%7s", veiculo.placa);
    printf("|%4s", veiculo.arCondicionado ? "Sim" : "Nao");
    printf("|%11dKm", veiculo.quilometragem);
    printf("|R$%6.2f", veiculo.valorDiaria);
    printf("|%4s|\n", veiculo.disponivel ? "Sim" : "Nao");
}