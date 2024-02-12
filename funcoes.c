#include <string.h>
#include <stdio.h>
#include <stdbool.h> // Adicionado para utilizar o tipo de dado bool
#include <ctype.h> // Adicionado para utilizar a funcao toupper
#include <time.h>
#include <stdlib.h>

#include "funcoes.h"


void inicializarPrecosBase(struct Hotel *hotel) {
    hotel->precosBase[0] = (struct PrecoBase){'M', 'B', 'S', 50, 10, "03/01", "05/31", 5};
    hotel->precosBase[1] = (struct PrecoBase){'M', 'B', 'D', 70, 15, "", "", 0};
    hotel->precosBase[2] = (struct PrecoBase){'M', 'B', 'T', 80, 20, "03/01", "05/31", 5};
    hotel->precosBase[3] = (struct PrecoBase){'M', 'B', 'F', 100, 50, "03/01", "05/31", 10};
    hotel->precosBase[4] = (struct PrecoBase){'M', 'S', 'S', 70, 20, "02/01", "05/31", 15};
    hotel->precosBase[5] = (struct PrecoBase){'M', 'S', 'D', 90, 30, "", "", 0};
    hotel->precosBase[6] = (struct PrecoBase){'M', 'S', 'T', 100, 50, "03/01", "05/31", 5};
    hotel->precosBase[7] = (struct PrecoBase){'M', 'S', 'F', 120, 60, "03/01", "05/31", 10};
    hotel->precosBase[8] = (struct PrecoBase){'P', 'B', 'S', 40, 10, "01/01", "05/31", 10};
    hotel->precosBase[9] = (struct PrecoBase){'P', 'B', 'D', 60, 15, "01/01", "05/31", 5};
    hotel->precosBase[10] = (struct PrecoBase){'P', 'B', 'T', 70, 20, "03/01", "05/31", 10};
    hotel->precosBase[11] = (struct PrecoBase){'P', 'B', 'F', 90, 40, "03/01", "05/31", 15};
    hotel->precosBase[12] = (struct PrecoBase){'P', 'S', 'S', 50, 10, "01/01", "05/31", 10};
    hotel->precosBase[13] = (struct PrecoBase){'P', 'S', 'D', 70, 30, "01/01", "05/31", 5};
    hotel->precosBase[14] = (struct PrecoBase){'P', 'S', 'T', 80, 40, "03/01", "05/31", 10};
    hotel->precosBase[15] = (struct PrecoBase){'P', 'S', 'F', 100, 50, "03/01", "05/31", 15};
}



void inicializarSobretaxas(struct Hotel *hotel) {
    struct SobretaxaEpoca sobretaxas[] = {
        {'B', "11/01", "03/31", 0},
        {'I', "04/01", "05/31", 50},
        {'M', "06/01", "06/30", 60},
        {'A', "06/01", "08/31", 10}
    };

    for (int i = 0; i < 4; i++) {
        hotel->sobretaxas[i] = sobretaxas[i];
    }
}

void inicializarValoresSuplementares(struct Hotel *hotel) {
    struct ValorSuplementar valoresSuplementares[] = {
        {1, "PA", 10},
        {2, "A", 20},
        {3, "PA+A", 25},
        {4, "J", 20},
        {5, "PA+J", 20},
        {6, "PA+A+J", 30},
        {7, "B&C", 10},
        {8, "PC", 50},
        {9, "O", 10}
    };

    for (int i = 0; i < 9; i++) {
        hotel->valoresSuplementares[i] = valoresSuplementares[i];
    }
}

void inicializarHotel(struct Hotel *hotel) {
    hotel->numClientes = 0;
    hotel->numQuartos = 0;
    hotel->numReservas = 0;


    inicializarPrecosBase(hotel);
    inicializarSobretaxas(hotel);
    inicializarValoresSuplementares(hotel);
}


void inicializarServicosComplementares(struct Hotel *hotel) {
    for (int i = 0; i < 1000; i++) {
        hotel->servicosComplementares[i].numeroSequencial = 0;
    }
}

void inicializarPagamentos(struct Hotel *hotel) {
    for (int i = 0; i < 1000; i++) {
        hotel->pagamentos[i].codigoQuarto = 0;
    }
}

void inicializarHotelCompleto(struct Hotel *hotel) {
    inicializarHotel(hotel);
    inicializarQuartos(hotel);
    inicializarServicosComplementares(hotel);
    inicializarPagamentos(hotel);
}

void mostrarPrecosBase(struct Hotel *hotel) {
    printf("Precos base:\n");

    for (int i = 0; i < 16; i++) {
        struct PrecoBase precoBase = hotel->precosBase[i];
        printf("Vista: %s, Qualidade: %s, Numero de pessoas: %s, Valor: %.2f, Valor de cancelamento: %.2f, Inicio da promocao: %s, Fim da promocao: %s, Valor da promocao: %d\n", precoBase.vista, precoBase.qualidade, precoBase.np, precoBase.valor, precoBase.valorCancelamento, precoBase.inicioPromocao, precoBase.fimPromocao, precoBase.valorPromocao);
    }
}

void mostrarSobretaxas(struct Hotel *hotel) {
    printf("Sobretaxas:\n");

    for (int i = 0; i < 4; i++) {
        struct SobretaxaEpoca sobretaxa = hotel->sobretaxas[i];
        printf("Epoca: %s, Inicio: %s, Fim: %s, Percentual adicional: %d%%\n", sobretaxa.epoca, sobretaxa.inicio, sobretaxa.fim, sobretaxa.percentualAdicional);
    }
}

void mostrarValoresSuplementares(struct Hotel *hotel) {
    printf("Valores suplementares:\n");

    for (int i = 0; i < 9; i++) {
        struct ValorSuplementar valorSuplementar = hotel->valoresSuplementares[i];
        printf("Tipo de servico: %s, Valor: %.2f\n", valorSuplementar.tipoServico, valorSuplementar.valor);
    }
}

void mostrarHotelCompleto(struct Hotel *hotel) {
    mostrarPrecosBase(hotel);
    mostrarSobretaxas(hotel);
    mostrarValoresSuplementares(hotel);
}



// Funcao para obter a data atual no formato "MM/DD"
void obterDataAtual(char dataAtual[6]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataAtual, "%02d/%02d", tm.tm_mon + 1, tm.tm_mday);
}

void receberData(const char *date, struct tm *tm) {
    sscanf(date, "%d/%d", &tm->tm_mon, &tm->tm_mday);
    tm->tm_mon--;  // tm_mon is 0-based
}

int calcularDiferencaDias(char *data1, char *data2) {
    struct tm tm1 = {0}, tm2 = {0};
    time_t t1, t2;

    // Preenche as estruturas tm
    receberData(data1, &tm1);
    receberData(data2, &tm2);

    // Define o ano para evitar problemas com anos bissextos
    tm1.tm_year = 2024 - 1900; // years since 1900
    tm2.tm_year = 2024 - 1900; // years since 1900

    // Converte as estruturas tm para time_t
    t1 = mktime(&tm1);
    t2 = mktime(&tm2);

    // Calcula a diferenca em segundos e converte para dias
    return difftime(t2, t1) / (60 * 60 * 24);
}

//TESTEEEEEEEEEEEEEEEEEEEEEEEEE



void inicializar(struct Hotel *hotel) {
    int ultimoCodigoDefinitivo = 0;
    int ultimoCodigoProvisorio = 0;
    int ultimoNumeroQuarto = 0;

    criarClientesDefinitivosTeste(hotel, &ultimoCodigoDefinitivo);
    criarClientesProvisoriosTeste(hotel, &ultimoCodigoProvisorio);
}


void menu(struct Hotel *hotel) {
    int ultimoCodigoDefinitivo = 0;
    int ultimoCodigoProvisorio = 0;
    int ultimoNumeroQuarto = 0;
    int ultimoNumeroReserva = 0;
    int opcao;
    int numeroReserva;
    double valor;
    int codigoQuarto;
    double valorTotalServicos = 0.0;
    double valorServico;
    
    while (1) {
        printf("1. Operacoes Clientes\n");
        printf("2. Operacoes Quartos\n");
        printf("3. Operacoes Reservas\n");
        printf("4. Operacoes Check-in/Out\n");
        printf("5. Pagamentos\n");
        printf("6. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        

        int subOpcao;

        switch (opcao) {
            case 1:
                printf("1. Adicionar Cliente\n");
                printf("2. Editar Cliente\n");
                printf("3. Remover Cliente\n");
                printf("4. Mostrar Clientes\n");
                printf("Escolha uma sub-opcao: ");
                scanf("%d", &subOpcao);
               

                switch (subOpcao) {
                    case 1:
                        criarClienteProvisorio(hotel, &ultimoCodigoProvisorio);
                        break;
                    case 2:
                        alterarClienteProvisorio(hotel);
                        break;
                    case 3:
                        eliminarClienteProvisorio(hotel);
                        break;
                    case 4:
                        mostrarClientes(hotel);
                        break;
                    default:
                        printf("Sub-opcao invalida. Tente novamente.\n");
                }
                break;
            case 2:
                printf("1. Adicionar Quarto\n");
                printf("2. Editar Quarto\n");
                printf("3. Remover Quarto\n");
                printf("4. Mostrar Quartos\n");
                printf("Escolha uma sub-opcao: ");
                scanf("%d", &subOpcao);
                
                switch (subOpcao) {
                    case 1:
                        criarQuarto(hotel);
                        break;
                    case 2:
                        alterarQuarto(hotel);
                        break;
                    case 3:
                        removerQuartoPorDenominacao(hotel);
                        break;
                    case 4:
                        mostrarQuartos(hotel);
                        break;
                    default:
                        printf("Sub-opcao invalida. Tente novamente.\n");
                }
                break;
            case 3:
                printf("1. Adicionar Reserva\n");
                printf("2. Editar Reserva\n");
                printf("3. Remover Reserva\n");
                printf("4. Mostrar Reservas\n");
                printf("Escolha uma sub-opcao: ");
                scanf("%d", &subOpcao);
                
                switch (subOpcao) {
                    case 1:
                        criarReserva(hotel, &ultimoNumeroReserva);
                        while ((getchar()) != '\n'); // Limpa o buffer de entrada
                        break;
                    case 2:
                        printf("Insira o numero da reserva que deseja alterar: ");
                        scanf("%d", &numeroReserva);
                        while ((getchar()) != '\n'); // Limpa o buffer de entrada

                        alterarReserva(hotel, numeroReserva);
                        break;
                    case 3:
                        printf("Insira o numero da reserva que deseja apagar: ");
                        scanf("%d", &numeroReserva);
                        while ((getchar()) != '\n'); // Limpa o buffer de entrada

                        apagarReserva(hotel, numeroReserva);
                        break;
                    case 4:
                        mostrarReservas(hotel);
                        break;
                    default:
                        printf("Sub-opcao invalida. Tente novamente.\n");
                }
                break;
            case 4:
                printf("1. Check-in\n");
                printf("2. Check-out\n");
                printf("Escolha uma sub-opcao: ");
                scanf("%d", &subOpcao);
                
                switch (subOpcao) {
                    case 1:
                        checkIn(hotel, &ultimoCodigoDefinitivo);
                        break;
                    case 2:
                        checkOut(hotel);
                        break;
                    default:
                        printf("Sub-opcao invalida. Tente novamente.\n");
                }
                break;
            case 5:
                printf("1. Mostrar Pagamentos\n");
                printf("2. Corrigir Pagamento\n");
                printf("3. Anular Pagamento\n");
                printf("Escolha uma sub-opcao: ");
                scanf("%d", &subOpcao);
                
                switch (subOpcao) {
                    case 1:
                        mostrarPagamentos(hotel);
                        break;
                    case 2:
                        corrigirPagamento(hotel);
                        break;
                    case 3:
                        anularPagamento(hotel);
                        break;
                    default:
                        printf("Sub-opcao invalida. Tente novamente.\n");
                }
                break;
            case 6:
                return;
            case 7:
                printf("ID\tServiço\tValor\n");
            for (int i = 0; i < 9; i++) {
                printf("%d\t%s\t%.2f\n", hotel->valoresSuplementares[i].id, hotel->valoresSuplementares[i].tipoServico, hotel->valoresSuplementares[i].valor);
            }

            int idServico;
            double valorServico;
            double valorTotalServicos = 0.0;

            printf("Por favor, insira o ID do serviço utilizado. Quando terminar, insira 0:\n");
            while (1) {
                scanf("%d", &idServico);
                if (idServico == 0) {
                    break;
                }
                valorServico = solicitarServicosUtilizados(hotel, idServico);
                if (valorServico != -1.0) {
                    valorTotalServicos += valorServico;
                } else {
                    printf("ID do serviço não encontrado. Tente novamente.\n");
                }
            }
            printf("O valor total dos serviços utilizados é: %.2f\n", valorTotalServicos);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}


void criarReservaTeste(struct Hotel *hotel, int *ultimoNumeroReserva) {
    if (hotel->numReservas >= 1000) {
        printf("Limite de reservas atingido.\n");
        return;
    }

    struct Reserva novaReserva;

    strcpy(novaReserva.dataReserva, "01/01");

    novaReserva.cliente = &hotel->clientesDefinitivos[0]; // Assume que existe pelo menos um cliente definitivo

    novaReserva.codigoQuarto = 10101; // Assume que o quarto 101 existe

    strcpy(novaReserva.dataCheckIn, "04/02");
    strcpy(novaReserva.dataCheckOut, "04/07");

    novaReserva.numDias = calcularDiferencaDias(novaReserva.dataCheckIn, novaReserva.dataCheckOut);

    if (!verificarDisponibilidadeQuarto(hotel, novaReserva.codigoQuarto, novaReserva.dataCheckIn) ||
        !verificarDisponibilidadeQuarto(hotel, novaReserva.codigoQuarto, novaReserva.dataCheckOut)) {
        printf("O quarto nao esta disponível nas datas selecionadas.\n");
        return;
    }

    novaReserva.numPessoas = 1;

    novaReserva.situacaoReserva = 'P';  // Provisoria
    novaReserva.numeroReserva = ++(*ultimoNumeroReserva);

    strcpy(novaReserva.observacoes, "Reserva de teste");

    hotel->reservas[hotel->numReservas++] = novaReserva;

    printf("\nReserva de teste criada com sucesso.\n");
}


int obterDesignacaoQuartoPorReserva(struct Hotel* hotel, int numeroReserva) {
    // Encontre a reserva com o numero fornecido
    struct Reserva* reserva = NULL;
    for (int i = 0; i < hotel->numReservas; i++) {
        if (hotel->reservas[i].numeroReserva == numeroReserva) {
            reserva = &hotel->reservas[i];
            break;
        }
    }

    if (reserva == NULL) {
        printf("Reserva com numero %d nao encontrada.\n", numeroReserva);
        return -1;
    }

    // Se a reserva foi encontrada, retorne a designacao do quarto associado
    return reserva->codigoQuarto;
}



int obterPrecoBasePorQuarto(struct Hotel *hotel, struct CaracteristicasQuarto quarto) {
    for (int i = 0; i < 16; i++) {
        if (hotel->precosBase[i].vista == quarto.vista &&
            hotel->precosBase[i].qualidade == quarto.qualidade &&
            hotel->precosBase[i].np == quarto.ocupacaoMaxima) {
            return i;
        }
    }
    return -1;
}

void registarPagamento(struct Hotel *hotel, struct Reserva *reserva, double valorTotal) {
    printf("Escolha o tipo de pagamento (M para Multibanco, D para Dinheiro): ");
    char formaPagamento;
    scanf(" %c", &formaPagamento);
    getchar();
    formaPagamento = toupper(formaPagamento); // Converte a entrada para maiusculas

    // Verifica se a forma de pagamento e valida
    if (formaPagamento != 'M' && formaPagamento != 'D') {
        printf("Forma de pagamento invalida.\n");
    } else {
        // Cria um novo pagamento
        struct Pagamento pagamento;
        pagamento.id = hotel->numPagamentos + 1; // Atribui um ID sequencial ao pagamento
        pagamento.codigoQuarto = reserva->codigoQuarto;
        pagamento.valor = valorTotal;
        pagamento.formaPagamento = formaPagamento;

        // Adiciona o pagamento ao array de pagamentos
        hotel->pagamentos[hotel->numPagamentos] = pagamento;
        hotel->numPagamentos++;
        printf("Pagamento registado com sucesso.\n");
    }
}

void mostrarPagamentos(struct Hotel *hotel) {
    printf("Pagamentos:\n");
    for (int i = 0; i < hotel->numPagamentos; i++) {
        struct Pagamento pagamento = hotel->pagamentos[i];
        printf("Pagamento ID: %d\n", pagamento.id);
        printf("  Codigo do quarto: %d\n", pagamento.codigoQuarto);
        printf("  Valor: %.2f\n", pagamento.valor);
        printf("  Forma de pagamento: %c\n", pagamento.formaPagamento);
    }
}

void corrigirPagamento(struct Hotel *hotel) {
    printf("Insira o ID do pagamento que deseja corrigir: ");
    int idPagamento;
    scanf("%d", &idPagamento);
    while ((getchar()) != '\n'); // Limpa o buffer de entrada

    int indicePagamento = -1;
    for (int i = 0; i < hotel->numPagamentos; i++) {
        if (hotel->pagamentos[i].id == idPagamento) {
            indicePagamento = i;
            break;
        }
    }

    if (indicePagamento == -1) {
        printf("ID de pagamento inválido.\n");
        return;
    }

    printf("Escolha o novo tipo de pagamento (M para Multibanco, D para Dinheiro): ");
    char formaPagamento;
    scanf(" %c", &formaPagamento);
    getchar();
    formaPagamento = toupper(formaPagamento); // Converte a entrada para maiusculas

    // Verifica se a forma de pagamento e valida
    if (formaPagamento != 'M' && formaPagamento != 'D') {
        printf("Forma de pagamento invalida.\n");
    } else {
        // Altera a forma de pagamento no pagamento selecionado
        hotel->pagamentos[indicePagamento].formaPagamento = formaPagamento;

        printf("Pagamento corrigido com sucesso.\n");
    }
}

void anularPagamento(struct Hotel *hotel) {
    printf("Insira o ID do pagamento que deseja anular: ");
    int idPagamento;
    scanf("%d", &idPagamento);
    while ((getchar()) != '\n'); // Limpa o buffer de entrada

    int indicePagamento = -1;
    for (int i = 0; i < hotel->numPagamentos; i++) {
        if (hotel->pagamentos[i].id == idPagamento) {
            indicePagamento = i;
            break;
        }
    }

    if (indicePagamento == -1) {
        printf("ID de pagamento inválido.\n");
        return;
    }

    for (int i = indicePagamento; i < hotel->numPagamentos - 1; i++) {
        hotel->pagamentos[i] = hotel->pagamentos[i + 1];
    }
    hotel->numPagamentos--;
    printf("Pagamento anulado com sucesso.\n");
}
double solicitarServicosUtilizados(struct Hotel *hotel, int idServico) {
    double valorTotalServicos = 0.0;
    int found = 0;
    for (int i = 0; i < 9; i++) {
        if (hotel->valoresSuplementares[i].id == idServico) {
            valorTotalServicos += hotel->valoresSuplementares[i].valor;
            found = 1;
            break;
        }
    }
    if (!found) {
        return -1.0;
    }
    return valorTotalServicos;
}
