#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdbool.h>

// Enum para representar o estado da ficha do cliente
enum EstadoFicha {
    PROVISORIA,
    DEFINITIVA
};

// Estrutura para representar as características de um quarto
struct CaracteristicasQuarto {
    int torre;
    int andar;
    int numeroQuarto;
    char vista; // Can hold one character
    char qualidade; // Can hold one character
    char ocupacaoMaxima;
    int denominacao; 
    // Outros campos relevantes
};

// Estrutura para representar um cliente
struct Cliente {
    int codigo;
    char nome[50];
    char morada[100];
    char codigoPostal[10];
    char localidade[50];
    char NIF[15];
    char dataCriacao[11]; // Aumentei o tamanho do campo para acomodar "YYYY-MM-DD"
    char tipoCliente; // Ainda nao esta claro o tipo desse campo
    enum EstadoFicha estadoFicha;
};

// Estrutura para representar uma reserva
struct Reserva {
    int numeroReserva;
    char dataReserva[6]; // Modificado para acomodar "MM/DD"
    struct Cliente* cliente;
    char tipoFichaCliente;
    int codigoQuarto;
    char dataCheckIn[6]; // Modificado para acomodar "MM/DD"
    char dataCheckOut[6]; // Modificado para acomodar "MM/DD"
    int numDias;
    int numPessoas;
    char codigosServicosComplementares[5][20];
    char codigosOutrosQuartos[5][20];
    char formaPagamento[20];
    double valorCheckIn;
    char situacaoReserva;
    double valorCheckOut;
    char observacoes[100];
    int quartosExtra[5];
    int numQuartosExtra;
};

// Estrutura para representar um servico complementar
struct ServicoComplementar {
    int numeroSequencial;
    int codigoQuarto;
    char funcionario[50];
    char dataHoraPrestacao[20];
    char tipoServico[20];
    char codigoServicoEspecifico[20];
    char observacoes[100];
};

// Estrutura para representar um pagamento
struct Pagamento {
    int id;
    int codigoQuarto;
    double valor;
    char formaPagamento;
    // Outros campos relevantes
};

// Estrutura para representar uma linha da Tabela 1
struct PrecoBase {
    char vista; // Aumentei o tamanho do campo para acomodar "M" e "P"
    char qualidade; // Aumentei o tamanho do campo para acomodar "B" e "S"
    char np;
    double valor;
    double valorCancelamento;
    char inicioPromocao[6];
    char fimPromocao[6];
    int valorPromocao;
};

// Estrutura para representar uma linha da Tabela 2
struct SobretaxaEpoca {
    char epoca;
    char inicio[6];
    char fim[6];
    int percentualAdicional;
};

// Estrutura para representar uma linha da Tabela 3
struct ValorSuplementar {
    int id;
    char tipoServico[20]; // Aumentei o tamanho do campo para acomodar "Pensao Completa"
    double valor;
};

// Estrutura para representar um registro de servico
struct RegistoServico {
    int numeroSequencial;
    int quarto;
    int funcionario;
    char dataHora[20];
    char tipoServico[20];
    char codigoServico[20];
    char observacoes[100];
};

// Estrutura para representar o Hotel
struct Hotel {
    struct CaracteristicasQuarto quartos[200];
    struct Reserva reservas[1000];
    struct Cliente clientesDefinitivos[1000];
    struct Cliente clientesProvisorios[1000]; // Adicione esta linha
    int numClientes;
    int numClientesProvisorios; // Adicione esta linha
    int numClientesDefinitivos;
    int numReservas;
    int numQuartos;
    struct ServicoComplementar servicosComplementares[1000];
    struct Pagamento pagamentos[200];
    int numPagamentos;
    struct PrecoBase precosBase[16];
    struct SobretaxaEpoca sobretaxas[4];
    struct ValorSuplementar valoresSuplementares[10]; // Aumentei o tamanho do array para 10
    struct RegistoServico registosServicos[1000];
    // Outras estruturas e campos relevantes
};

#endif // ESTRUTURAS_H
