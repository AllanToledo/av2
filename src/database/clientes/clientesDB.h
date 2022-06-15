#include "../../util/collections.h"

#ifndef AV2_CLIENTESDB_H
#define AV2_CLIENTESDB_H

void insertCliente(Cliente cliente);
void updateCliente(Cliente cliente);
void deleteCliente(Cliente cliente);
ListaClientes *getClientes();

#endif //AV2_CLIENTESDB_H
