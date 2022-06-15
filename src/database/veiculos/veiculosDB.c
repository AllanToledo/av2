#include <stdio.h>
#include <stdlib.h>
#include "../../util/structs.h"
#include "../../util/collections.h"

#define filePath "../database/veiculos.dat"
#define tempFilePath "../database/veiculos.tmp"

void inserirVeiculoDB(Veiculo veiculo){
    FILE *file = fopen(filePath, "ab");
    fwrite(&veiculo, sizeof(Veiculo), 1, file);
    fclose(file);
}

ListaVeiculo *pegarVeiculosDB(){
    FILE *file = fopen(filePath, "rb");
    ListaVeiculo *lista = NULL;
    Veiculo veiculo;
    while(fread(&veiculo, sizeof(Veiculo), 1, file) == 1){
        ListaVeiculo *new = (ListaVeiculo *)malloc(sizeof(ListaVeiculo));
        new->veiculo = veiculo;
        new->next = lista;
        lista = new;
    }
    fclose(file);
    return lista;
}

void atualizarVeiculoDB(Veiculo veiculo){
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    Veiculo carroAux;
    while(fread(&carroAux, sizeof(Veiculo), 1, file) == 1){
        if(carroAux.id == veiculo.id){
            fwrite(&veiculo, sizeof(Veiculo), 1, temp);
        }else{
            fwrite(&carroAux, sizeof(Veiculo), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}

void removerVeiculoDB(Veiculo veiculo){
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    Veiculo carroAux;
    while(fread(&carroAux, sizeof(Veiculo), 1, file) == 1){
        if(carroAux.id != veiculo.id){
            fwrite(&carroAux, sizeof(Veiculo), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}