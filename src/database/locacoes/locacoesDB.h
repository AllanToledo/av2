#include "../../util/collections.h"

#ifndef AV2_LOCACOESDB_H
#define AV2_LOCACOESDB_H

ListaLocacoes *pegarLocacoesDB();
int inserirLocacaoDB(Locacao locacao);
void atualizarLocacaoDB(Locacao locacao);
void removerLocacaoDB(Locacao locacao);
void reverterMudancaLocacaoDB();
int buscarLocacaoPorIDDB(int id, Locacao *locacao);

#endif //AV2_LOCACOESDB_H
