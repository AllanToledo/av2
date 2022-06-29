cmake_minimum_required(VERSION 3.22)
project(av2 C)

set(CMAKE_C_STANDARD 99)

add_executable(av2
        src/main.c
        src/util/structs.c
        src/util/collections.c
        src/menu/menu.c
        src/database/veiculos/veiculosDB.c
        src/database/clientes/clientesDB.c
        src/database/locacoes/locacoesDB.c
        src/acoes/veiculosAcoes.c
        src/acoes/locacoesAcoes.c
        src/acoes/clientesAcoes.c
        src/util/scan/scan.h
        src/util/scan/scan.c src/database/vendas/vendasDB.c src/database/vendas/vendasDB.h)
