#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../util/structs.h"
#include "../../util/collections.h"
#include "veiculosDB.h"

#define filePath "../database/carros.dat"
#define tempFilePath "../database/carros.tmp"
#define backupFilePath "../database/carros.bak"

//Mesma lógica utilizada no arquivo clientesDB.c, acesse o arquivo para mais informações.

void criarBackupVeiculosDB() {
    FILE *file = fopen(filePath, "rb");
    FILE *backup = fopen(backupFilePath, "wb");
    if(file == NULL || backup == NULL){
        printf("Erro ao abrir arquivo de veiculos.\n");
        return;
    }
    Veiculo carroAux;
    while (fread(&carroAux, sizeof(Veiculo), 1, file) == 1) {
        fwrite(&carroAux, sizeof(Veiculo), 1, backup);
    }
    fclose(file);
    fclose(backup);
}

void reverterMudancaVeiculoDB() {
    FILE *backup = fopen(backupFilePath, "rb");
    FILE *file = fopen(filePath, "wb");
    if(file == NULL || backup == NULL){
        printf("Erro ao abrir arquivo de veiculos.\n");
        return;
    }
    Veiculo carroAux;
    while (fread(&carroAux, sizeof(Veiculo), 1, backup) == 1) {
        fwrite(&carroAux, sizeof(Veiculo), 1, file);
    }
    fclose(backup);
    fclose(file);
}

void inserirVeiculoDB(Veiculo veiculo) {
    criarBackupVeiculosDB();
    ListaVeiculo *listaVeiculo = pegarVeiculosDB();
    int maiorId = 0;
    if (listaVeiculo != NULL) {
        ListaVeiculo *lista = listaVeiculo;
        while (lista != NULL) {
            if (lista->veiculo.id > maiorId) {
                maiorId = lista->veiculo.id;
            }
            lista = lista->proximo;
        }
    }
    veiculo.id = maiorId + 1;
    FILE *file = fopen(filePath, "ab");
    if(file == NULL){
        printf("Erro ao abrir arquivo de veiculos.\n");
        return;
    }
    fwrite(&veiculo, sizeof(Veiculo), 1, file);
    fclose(file);
}


ListaVeiculo *pegarVeiculosDB() {
    FILE *file = fopen(filePath, "rb");
    if(file == NULL){
        printf("Erro ao abrir arquivo de veiculos.\n");
        return NULL;
    }
    ListaVeiculo *lista = NULL;
    Veiculo veiculo;
    while (fread(&veiculo, sizeof(Veiculo), 1, file) == 1) {
        ListaVeiculo *new = (ListaVeiculo *) malloc(sizeof(ListaVeiculo));
        new->veiculo = veiculo;
        new->proximo = lista;
        lista = new;
    }
    fclose(file);
    return lista;
}

void atualizarVeiculoDB(Veiculo veiculo) {
    criarBackupVeiculosDB();
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    if(file == NULL || temp == NULL){
        printf("Erro ao abrir arquivo de veiculos.\n");
        return;
    }
    Veiculo carroAux;
    while (fread(&carroAux, sizeof(Veiculo), 1, file) == 1) {
        if (carroAux.id == veiculo.id) {
            fwrite(&veiculo, sizeof(Veiculo), 1, temp);
        } else {
            fwrite(&carroAux, sizeof(Veiculo), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}

void removerVeiculoDB(Veiculo veiculo) {
    criarBackupVeiculosDB();
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    if(file == NULL || temp == NULL){
        printf("Erro ao abrir arquivo de veiculos.\n");
        return;
    }
    Veiculo carroAux;
    while (fread(&carroAux, sizeof(Veiculo), 1, file) == 1) {
        if (carroAux.id != veiculo.id) {
            fwrite(&carroAux, sizeof(Veiculo), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}

/*
 * Função que busca um veículo pelo id, caso encontre, retorna 1, caso não encontre, retorna 0.
 * O veículo é retornado por referência.
 */

int buscarVeiculoPorIDDB(int id, Veiculo *veiculo) {
    ListaVeiculo *lista = pegarVeiculosDB();
    ListaVeiculo *aux = lista;
    int retorno = 0;
    while (aux != NULL) {
        if (aux->veiculo.id == id) {
            *veiculo = aux->veiculo;
            retorno = 1;
            break;
        }
        aux = aux->proximo;
    }
    liberarListaVeiculos(lista);
    return retorno;
}

/*
 * Função que busca um veículo pela placa, caso encontre, retorna 1, caso contrário, retorna 0.
 * O veículo é retornado por referência.
 */

int buscarVeiculoPorPlacaDB(char placa[8], Veiculo *veiculo) {
    ListaVeiculo *lista = pegarVeiculosDB();
    while (lista != NULL) {
        if (strcmp(lista->veiculo.placa, placa) == 0) {
            *veiculo = lista->veiculo;
            liberarListaVeiculos(lista);
            return 1;
        }
        lista = lista->proximo;
    }
    liberarListaVeiculos(lista);
    return 0;
}
