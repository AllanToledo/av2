#include "stdio.h"
#include "stdlib.h"
#include "locacoesDB.h"

#define filePath "../database/locacoes.dat"
#define tempFilePath "../database/locacoes.tmp"
#define backupFilePath "../database/locacoes.bak"

void criarBackupLocacoesDB() {
    FILE *file = fopen(filePath, "rb");
    FILE *backup = fopen(backupFilePath, "wb");
    Locacao locacaoAux;
    while (fread(&locacaoAux, sizeof(Locacao), 1, file) == 1) {
        fwrite(&locacaoAux, sizeof(Locacao), 1, backup);
    }
    fclose(file);
    fclose(backup);
}

void reverterMudancaLocacaoDB() {
    FILE *backup = fopen(backupFilePath, "rb");
    FILE *file = fopen(filePath, "wb");
    Locacao locacaoAux;
    while (fread(&locacaoAux, sizeof(Locacao), 1, backup) == 1) {
        fwrite(&locacaoAux, sizeof(Locacao), 1, file);
    }
    fclose(backup);
    fclose(file);
}

ListaLocacoes *pegarLocacoesDB() {
    ListaLocacoes *listaLocacoes = NULL;
    FILE *file = fopen(filePath, "rb");
    Locacao locacao;
    ListaLocacoes *aux;
    while (fread(&locacao, sizeof(Locacao), 1, file) == 1) {
        aux = malloc(sizeof(ListaLocacoes));
        aux->locacao = locacao;
        aux->proximo = listaLocacoes;
        listaLocacoes = aux;
    }
    fclose(file);
    return listaLocacoes;
}

void inserirLocacaoDB(Locacao locacao) {
    criarBackupLocacoesDB();
    ListaLocacoes *listaLocacoes = pegarLocacoesDB();
    int maiorId = 0;
    if (listaLocacoes != NULL) {
        ListaLocacoes *lista = listaLocacoes;
        while (lista != NULL) {
            if (lista->locacao.id > maiorId) {
                maiorId = lista->locacao.id;
            }
            lista = lista->proximo;
        }
    }
    locacao.id = maiorId + 1;
    FILE *file = fopen(filePath, "ab");
    fwrite(&locacao, sizeof(Locacao), 1, file);
    fclose(file);
}

void atualizarLocacaoDB(Locacao locacao){
    criarBackupLocacoesDB();
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    Locacao locacaoAux;
    while(fread(&locacaoAux, sizeof(Locacao), 1, file) == 1){
        if(locacaoAux.id == locacao.id){
            fwrite(&locacao, sizeof(Locacao), 1, temp);
        }else{
            fwrite(&locacaoAux, sizeof(Locacao), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}

void removerLocacaoDB(Locacao locacao){
    criarBackupLocacoesDB();
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    Locacao locacaoAux;
    while(fread(&locacaoAux, sizeof(Locacao), 1, file) == 1){
        if(locacaoAux.id != locacao.id){
            fwrite(&locacaoAux, sizeof(Locacao), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}
