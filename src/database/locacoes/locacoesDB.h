#include "../../util/collections.h"

#ifndef AV2_LOCACOESDB_H
#define AV2_LOCACOESDB_H

ListaLocacoes *pegarLocacoesDB();
void inserirLocacaoDB(Locacao locacao);
void atualizarLocacaoDB(Locacao locacao);
void removerLocacaoDB(Locacao locacao);
void reverterMudancaLocacaoDB();

#endif //AV2_LOCACOESDB_H
