#include "structs.h"
#include <stdio.h>

void printCliente(Cliente cliente) {
    printf("Nome: %s\n", cliente.nome);
    printf("CPF: %s\n", cliente.cpf);
    printf("Idade: %d\n", cliente.idade);
    printf("Endereco: %s\n", cliente.endereco);
    printf("Cidade: %s\n", cliente.cidade);
    printf("Estado: %s\n", cliente.estado);
    printf("Pontos: %d\n", cliente.pontos);
}

void printVeiculoCabecalho(){
    printf("|ID|Modelo| Cor |Motor| Ano| Placa |Ar C|Quilometragem|Valor D.|Disp|\n");
}

void printVeiculo(Veiculo veiculo) {
    printf("|%2d", veiculo.id);
    printf("|%6s", veiculo.modelo);
    printf("|%5s", veiculo.cor);
    printf("| %.1f ", veiculo.motor);
    printf("|%d", veiculo.anoFabricacao);
    printf("|%7s", veiculo.placa);
    printf("|%4s", veiculo.arCondicionado? "Sim" : "Nao");
    printf("|%11dKm", veiculo.quilometragem);
    printf("|R$%6.2f", veiculo.valorDiaria);
    printf("|%4s|\n", veiculo.disponivel? "Sim" : "Nao");
}