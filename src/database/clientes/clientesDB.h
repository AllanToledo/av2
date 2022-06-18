#include "../../util/collections.h"

#ifndef AV2_CLIENTESDB_H
#define AV2_CLIENTESDB_H

void inserirClientesDB(Cliente cliente);
void atualizarClientesDB(Cliente cliente);
void removerClientesDB(Cliente cliente);
ListaClientes *pegarClientesDB();
void reverterMudancaClientesDB();
#endif //AV2_CLIENTESDB_H
