#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"
#include <time.h>

#define PROVISORIA 0
#define DEFINITIVA 1

void salvarHotel(struct Hotel *hotel);
void carregarHotel(struct Hotel *hotel);
void inicializarPrecosBase(struct Hotel *hotel);
void inicializarSobretaxas(struct Hotel *hotel);
void inicializarValoresSuplementares(struct Hotel *hotel);
void inicializarHotel(struct Hotel *hotel);
void inicializarServicosComplementares(struct Hotel *hotel);
void inicializarPagamentos(struct Hotel *hotel);
void inicializarHotelCompleto(struct Hotel *hotel);
void mostrarPrecosBase(struct Hotel *hotel);
void mostrarSobretaxas(struct Hotel *hotel);
void mostrarValoresSuplementares(struct Hotel *hotel);
void mostrarHotelCompleto(struct Hotel *hotel);
void obterDataAtual(char dataAtual[6]);
int calcularDiferencaDias(char *data1, char *data2);
void receberData(const char *date, struct tm *tm);
void registarPagamento(struct Hotel *hotel, struct Reserva *reserva, double valorTotal);
void mostrarPagamentos(struct Hotel *hotel);
void guardarPagamentos(struct Hotel *hotel);
void corrigirPagamento(struct Hotel *hotel);
void anularPagamento(struct Hotel *hotel);

// Funcões de quartos.c
void inicializarQuartos(struct Hotel *hotel);
void criarQuarto(struct Hotel *hotel);
void mostrarQuartos(struct Hotel *hotel);
void mostrarQuartoPorDenominacao(struct Hotel *hotel);
void alterarQuarto(struct Hotel *hotel);
void removerQuartoPorDenominacao(struct Hotel *hotel);
bool verificarDisponibilidadeQuarto(struct Hotel *hotel, int codigoQuarto, char *data);
int obterDesignacaoQuartoPorReserva(struct Hotel* hotel, int numeroReserva);
int obterPrecoBasePorQuarto(struct Hotel *hotel, struct CaracteristicasQuarto quarto);
struct CaracteristicasQuarto* obterQuartoPorCodigo(struct Hotel* hotel, int codigoQuarto);

// Funcões de clientes.c
struct Cliente* criarClienteProvisorio(struct Hotel *hotel, int *ultimoCodigoProvisorio);
void criarClienteDefinitivo(struct Hotel *hotel, int *ultimoCodigoDefinitivo);
void mostrarClientes(struct Hotel *hotel);
struct Cliente* ProcurarProvisorio(struct Hotel *hotel);
struct Cliente* ProcurarDefinitivo(struct Hotel *hotel);
void alterarClienteProvisorio(struct Hotel *hotel);
void eliminarClienteProvisorio(struct Hotel *hotel);
void moverCliente(int idClienteProvisorio, struct Cliente* clientesProvisorios, int* numClientesProvisorios, struct Cliente* clientesDefinitivos, int* numClientesDefinitivos);


// Funcões de reservas.c
void criarReserva(struct Hotel *hotel, int *ultimoNumeroReserva);
void mostrarReservas(struct Hotel *hotel);
void checkIn(struct Hotel *hotel, int *ultimoCodigoDefinitivo);
void checkOut(struct Hotel *hotel);
double calcularValorTotal(struct Hotel *hotel, int numeroReserva);
void alterarReserva(struct Hotel *hotel, int numeroReserva);
void apagarReserva(struct Hotel *hotel, int numeroReserva);
double solicitarServicosUtilizados(struct Hotel *hotel, int idServico);
void listarReservasCheckIn(struct Hotel *hotel, char *dataInicial, char *dataFinal);
void listarReservasCheckOut(struct Hotel *hotel, char *dataInicial, char *dataFinal);




//testes
void mostrarClientesProvisorio(struct Hotel *hotel);
void inicializar(struct Hotel *hotel);
void criarClientesProvisoriosTeste(struct Hotel *hotel, int *ultimoCodigoProvisorio);
void criarClientesDefinitivosTeste(struct Hotel *hotel, int *ultimoCodigoDefinitivo);
void criarQuartosTeste(struct Hotel *hotel);
void menu(struct Hotel *hotel);
void criarReservaTeste(struct Hotel *hotel, int *ultimoNumeroReserva);


#endif // FUNCOES_H
