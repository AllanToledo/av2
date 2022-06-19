#include "../../util/collections.h"

#ifndef AV2_VEICULOSDB_H
#define AV2_VEICULOSDB_H

ListaVeiculo *pegarVeiculosDB();
void inserirVeiculoDB(Veiculo veiculo);
void atualizarVeiculoDB(Veiculo veiculo);
void removerVeiculoDB(Veiculo veiculo);
void reverterMudancaVeiculoDB();
int buscarVeiculoPorIDDB(int id, Veiculo *veiculo);
int buscarVeiculoPorPlacaDB(char placa[8], Veiculo *veiculo);

#endif //AV2_VEICULOSDB_H
