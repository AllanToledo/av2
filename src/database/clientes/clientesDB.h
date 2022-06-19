#include "../../util/collections.h"

#ifndef AV2_CLIENTESDB_H
#define AV2_CLIENTESDB_H

void inserirClientesDB(Cliente cliente);
void atualizarClientesDB(Cliente cliente);
void removerClientesDB(Cliente cliente);
ListaClientes *pegarClientesDB();
void reverterMudancaClientesDB();
int buscarClientePorCPFDB(char cpf[12], Cliente *cliente);
int buscarClientePorNome(char nome[50], Cliente *cliente);
#endif //AV2_CLIENTESDB_H
