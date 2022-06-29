#include <stdio.h>
#include "vendasDB.h"

#define filePath "../database/vendas.csv"

void limparVendas() {
    remove(filePath);
}

void inserirVenda(Veiculo veiculo) {
    FILE *arquivo = fopen(filePath, "a");
    fprintf(arquivo,
            "%d,%s,%s,%.2f,%d,%s,%d,%d,%.2f,%d\n",
            veiculo.id,
            veiculo.modelo,
            veiculo.cor,
            veiculo.motor,
            veiculo.anoFabricacao,
            veiculo.placa,
            veiculo.arCondicionado,
            veiculo.quilometragem,
            veiculo.valorDiaria,
            veiculo.disponivel
    );
    fclose(arquivo);
}

