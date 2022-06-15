#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../util/collections.h"

#define filePath "../database/clientes.dat"
#define tempFilePath "../database/clientes.tmp"

void insertCliente(Cliente cliente){
    FILE *file = fopen(filePath, "ab");
    fwrite(&cliente, sizeof(Cliente), 1, file);
    fclose(file);
}

void updateCliente(Cliente cliente){
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

void deleteCliente(Cliente cliente){
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

ListaClientes *getClientes(){
    FILE *file = fopen(filePath, "rb");
    ListaClientes *lista = NULL;
    Cliente cliente;
    while(fread(&cliente, sizeof(Cliente), 1, file) == 1){
        ListaClientes *new = (ListaClientes *)malloc(sizeof(ListaClientes));
        new->cliente = cliente;
        new->next = lista;
        lista = new;
    }
    fclose(file);
    return lista;
}