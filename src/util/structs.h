

#ifndef AV2_STRUCTS_H
#define AV2_STRUCTS_H

#define FALSE 0
#define TRUE 1

typedef struct {
    int dia;
    int mes;
    int ano;
    int hora;
} Data;

typedef struct {
    int id;
    char modelo[10];
    char cor[6];
    float motor;
    int anoFabricacao;
    char placa[8];
    int arCondicionado;
    int quilometragem;
    float valorDiaria;
    int disponivel;
} Veiculo;

typedef struct {
    char cpf[12];
    char nome[50];
    int idade;
    char endereco[50];
    char cidade[50];
    char estado[3];
    int pontos;
} Cliente;

typedef struct {
    int id;
    int idCarro;
    char cpfCliente[12];
    Data inicio;
    Data devolucao;
    int quilometragemInicial;
    int quilometragemFinal;
    float valor;
} Locacao;


int diferencaEmHoras(Data inicio, Data fim);

void printCliente(Cliente cliente);
void printVeiculoCabecalho();
void printVeiculo(Veiculo veiculo);
void printLocacao(Locacao locacao);

#endif //AV2_STRUCTS_H
