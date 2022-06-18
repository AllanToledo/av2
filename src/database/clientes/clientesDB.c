#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../util/collections.h"
#include "clientesDB.h"

#define filePath "../database/clientes.dat"
#define tempFilePath "../database/clientes.tmp"
#define backupFilePath "../database/clientes.bak"


void criarBackupClientesDB() {
    FILE *file = fopen(filePath, "rb");
    FILE *backup = fopen(backupFilePath, "wb");
    Cliente clienteAux;
    while (fread(&clienteAux, sizeof(Cliente), 1, file) == 1) {
        fwrite(&clienteAux, sizeof(Cliente), 1, backup);
    }
    fclose(file);
    fclose(backup);
}

void reverMudancaClientesDB() {
    FILE *backup = fopen(backupFilePath, "rb");
    FILE *file = fopen(filePath, "wb");
    Cliente clienteAux;
    while (fread(&clienteAux, sizeof(Cliente), 1, backup) == 1) {
        fwrite(&clienteAux, sizeof(Cliente), 1, file);
    }
    fclose(backup);
    fclose(file);
}


/*
 * A função recebe um cliente e adiciona seus dados ao final do arquivo.
 */
void inserirClientesDB(Cliente cliente){
    criarBackupClientesDB();
    FILE *file = fopen(filePath, "ab");
    fwrite(&cliente, sizeof(Cliente), 1, file);
    fclose(file);
}

/*
 * A função reescreve todos os dados do arquivo de clientes em um arquivo temporário, exceto quando o cpf do cliente
 * é igual ao cpf do cliente passado como parâmetro, neste caso é escrito o cliente passado
 * como parâmetro. E depois o arquivo original é excluido e o arquivo temporário renomeado para o
 * nome do arquivo original.
 */

void atualizarClientesDB(Cliente cliente){
    criarBackupClientesDB();
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    Cliente clienteAux;
    while(fread(&clienteAux, sizeof(Cliente), 1, file) == 1){
        if(strcmp(clienteAux.cpf, cliente.cpf) == 0){
            fwrite(&cliente, sizeof(Cliente), 1, temp);
        }else{
            fwrite(&clienteAux, sizeof(Cliente), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}

/*
 * A função reescreve todos os dados do arquivo de clientes em um arquivo temporário, exceto quando o cpf do cliente
 * é igual ao cpf do cliente passado como parâmetro, neste caso a função pula para o próximo cliente.
 * E depois o arquivo original é excluido e o arquivo temporário renomeado para o nome do arquivo original.
 */

void removerClientesDB(Cliente cliente){
    criarBackupClientesDB();
    FILE *file = fopen(filePath, "rb");
    FILE *temp = fopen(tempFilePath, "wb");
    Cliente clienteAux;
    while(fread(&clienteAux, sizeof(Cliente), 1, file) == 1){
        if(strcmp(clienteAux.cpf, cliente.cpf) == 0){
            fwrite(&clienteAux, sizeof(Cliente), 1, temp);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filePath);
    rename(tempFilePath, filePath);
}

/*
 * A função cria uma lista encadeada de clientes e retorna o ponteiro para o primeiro nó.
 */

ListaClientes *pegarClientesDB(){
    FILE *file = fopen(filePath, "rb");
    ListaClientes *lista = NULL;
    Cliente cliente;
    while(fread(&cliente, sizeof(Cliente), 1, file) == 1){
        ListaClientes *new = (ListaClientes *)malloc(sizeof(ListaClientes));
        new->cliente = cliente;
        new->proximo = lista;
        lista = new;
    }
    fclose(file);
    return lista;
}