#include <string.h>
#include <stdio.h>
#include <stdbool.h> // Adicionado para utilizar o tipo de dado bool
#include <ctype.h> // Adicionado para utilizar a funcao toupper
#include <time.h>
#include <stdlib.h>
#include "funcoes.h"


void criarReserva(struct Hotel *hotel, int *ultimoNumeroReserva) {
    if (hotel->numReservas >= 1000) {
        printf("Limite de reservas atingido.\n");
        return;
    }

    struct Reserva novaReserva;

    char dataAtual[6];
    obterDataAtual(dataAtual);
    strcpy(novaReserva.dataReserva, dataAtual);

    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    char input[100];
    printf("O cliente e novo ou existente? (N - Novo, E - Existente): ");
    fgets(input, sizeof(input), stdin);
    char novoCliente, tipoCliente;
    sscanf(input, " %c", &novoCliente);

    int ultimoCodigoProvisorio = 0;

    if (toupper(novoCliente) == 'N') {
        novaReserva.cliente = criarClienteProvisorio(hotel, &ultimoCodigoProvisorio);
    } else if (toupper(novoCliente) == 'E') {
        printf("Tipo de cliente (P - Provisorio, D - Definitivo): ");
        do {
            fgets(input, sizeof(input), stdin);
            sscanf(input, " %c", &tipoCliente);

            if (toupper(tipoCliente) == 'P') {
                novaReserva.cliente = ProcurarProvisorio(hotel);
            } else if (toupper(tipoCliente) == 'D') {
                novaReserva.cliente = ProcurarDefinitivo(hotel);
            } else {
                printf("Tipo de cliente invalido.\n");
            }
        } while (novaReserva.cliente == NULL);
    } else {
        printf("Opcao invalida.\n");
        return;
    }

    printf("Codigo do quarto: ");
    scanf("%d", &novaReserva.codigoQuarto);
    while ((getchar()) != '\n'); // Limpa o buffer de entrada

    // Verifica se o quarto existe
    bool quartoExiste = false;
    for (int i = 0; i < hotel->numQuartos; i++) {
        if (hotel->quartos[i].denominacao == novaReserva.codigoQuarto) {
            quartoExiste = true;
            break;
        }
    }

    if (!quartoExiste) {
        printf("O quarto com o codigo %d nao existe.\n", novaReserva.codigoQuarto);
        return;
    }

    printf("Data do check-in (MM/DD): ");
    scanf("%6s", novaReserva.dataCheckIn);
    while ((getchar()) != '\n'); // Limpa o buffer de entrada

    printf("Data do check-out (MM/DD): ");
    scanf("%6s", novaReserva.dataCheckOut);
    while ((getchar()) != '\n'); // Limpa o buffer de entrada

    // Verifica a disponibilidade do quarto
    if (!verificarDisponibilidadeQuarto(hotel, novaReserva.codigoQuarto, novaReserva.dataCheckIn) ||
        !verificarDisponibilidadeQuarto(hotel, novaReserva.codigoQuarto, novaReserva.dataCheckOut)) {
        printf("O quarto nao esta disponível nas datas selecionadas.\n");
        return;
    }

    int numDias = calcularDiferencaDias(novaReserva.dataCheckIn, novaReserva.dataCheckOut);
    if (numDias < 0) {
        printf("A data de check-out deve ser posterior à data de check-in.\n");
        return;
    }
    novaReserva.numDias = numDias;
    
    printf("Numero de pessoas: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &novaReserva.numPessoas);

    // Encontre o quarto selecionado na lista de quartos do hotel
    for (int i = 0; i < hotel->numQuartos; i++) {
        if (hotel->quartos[i].denominacao == novaReserva.codigoQuarto) {
            // Verifique se o numero de pessoas e permitido para o quarto selecionado
            switch (hotel->quartos[i].ocupacaoMaxima) {
                case 'S': // Single
                    if (novaReserva.numPessoas > 1) {
                        printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                        return;
                    }
                    break;
                case 'D': // Duplo
                    if (novaReserva.numPessoas > 2) {
                        printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                        return;
                    }
                    break;
                case 'T': // Triplo
                    if (novaReserva.numPessoas > 3) {
                        printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                        return;
                    }
                    break;
                case 'F': // Familiar
                    if (novaReserva.numPessoas > 5) {
                        printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                        return;
                    }
                    break;
            }
            break;
        }
    }

    novaReserva.situacaoReserva = 'P';  // Provisoria
    novaReserva.numeroReserva = ++(*ultimoNumeroReserva);

    printf("Quantos quartos extras estão na reserva? ");
    scanf("%d", &novaReserva.numQuartosExtra);
    for (int i = 0; i < novaReserva.numQuartosExtra; i++) {
        printf("Digite o código do quarto extra %d: ", i + 1);
        scanf("%d", &novaReserva.quartosExtra[i]);
        while ((getchar()) != '\n'); // Limpa o buffer de entrada

        // Verifica se o quarto extra existe
        bool quartoExtraExiste = false;
        for (int j = 0; j < hotel->numQuartos; j++) {
            if (hotel->quartos[j].denominacao == novaReserva.quartosExtra[i]) {
                quartoExtraExiste = true;
                break;
            }
        }

        if (!quartoExtraExiste) {
            printf("O quarto extra com o codigo %d nao existe.\n", novaReserva.quartosExtra[i]);
            return;
        }

        // Verifica a disponibilidade do quarto extra
        if (!verificarDisponibilidadeQuarto(hotel, novaReserva.quartosExtra[i], novaReserva.dataCheckIn) ||
            !verificarDisponibilidadeQuarto(hotel, novaReserva.quartosExtra[i], novaReserva.dataCheckOut)) {
            printf("O quarto extra %d nao esta disponível nas datas selecionadas.\n", i + 1);
            return;
        }
    }

    // Limpa o buffer de entrada
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Deseja adicionar observacões? (S - Sim, N - Nao): ");
    fgets(input, sizeof(input), stdin);
    char adicionarObservacoes;
    sscanf(input, " %c", &adicionarObservacoes);

    if (toupper(adicionarObservacoes) == 'S') {
        printf("Insira as observacoes: ");
        fgets(novaReserva.observacoes, sizeof(novaReserva.observacoes), stdin);
        novaReserva.observacoes[strcspn(novaReserva.observacoes, "\n")] = 0; // Remove newline character
    } else {
        novaReserva.observacoes[0] = '\0'; // No observations
    }

    hotel->reservas[hotel->numReservas++] = novaReserva;

    printf("\nReserva criada com sucesso.\n");
}


void mostrarReservas(struct Hotel *hotel) {
    if (hotel->numReservas == 0) {
        printf("Nao ha reservas.\n");
        return;
    }

    printf("\nReservas:\n");
    for (int i = 0; i < hotel->numReservas; i++) {
        printf("Numero da reserva: %d\n", hotel->reservas[i].numeroReserva);
        printf("Data da reserva: %s\n", hotel->reservas[i].dataReserva);
        printf("Cliente: %s\n", hotel->reservas[i].cliente->nome);
        printf("Codigo do quarto: %d\n", hotel->reservas[i].codigoQuarto); 
        printf("Data do check-in: %s\n", hotel->reservas[i].dataCheckIn);
        printf("Data do check-out: %s\n", hotel->reservas[i].dataCheckOut);
        printf("Numero de pessoas: %d\n", hotel->reservas[i].numPessoas);
        printf("Situacao da reserva: %c\n", hotel->reservas[i].situacaoReserva);
        printf("Observacoes: %s\n", hotel->reservas[i].observacoes);
        
        // Mostrar quartos extras
        printf("Quartos extras: ");
        for (int j = 0; j < hotel->reservas[i].numQuartosExtra; j++) {
            printf("%d ", hotel->reservas[i].quartosExtra[j]);
        }
        printf("\n\n");
    }
}

    void checkIn(struct Hotel *hotel, int *ultimoCodigoDefinitivo) {
        int numReserva;
        char confirmacao;
        struct Cliente* cliente = NULL;
        struct Reserva* reserva = NULL;
        int indexClienteProvisorio = -1;
        double valorTotal = 0.0; // Definindo valorTotal aqui para que possa ser acessado mais tarde

        // Solicita o numero da reserva
        printf("Numero de reserva: ");
        scanf("%d", &numReserva);
        getchar(); // Remove newline character

        // Solicita confirmacao para realizar o check-in
        printf("Deseja fazer check-in? (S/N): ");
        scanf(" %c", &confirmacao);
        getchar();
        confirmacao = toupper(confirmacao); // Converte a entrada para maiusculas

        if (confirmacao == 'S') {
            // Procura o cliente e a reserva com base no numero de reserva
            for (int i = 0; i < hotel->numClientes; i++) {
                if (hotel->clientesDefinitivos[i].codigo == numReserva) {
                    cliente = &hotel->clientesDefinitivos[i];
                    break;
                }
            }

            for (int i = 0; i < hotel->numClientesProvisorios; i++) {
                if (hotel->clientesProvisorios[i].codigo == numReserva) {
                    cliente = &hotel->clientesProvisorios[i];
                    indexClienteProvisorio = i;
                    break;
                }
            }

            for (int i = 0; i < hotel->numReservas; i++) {
                if (hotel->reservas[i].numeroReserva == numReserva) {
                    reserva = &hotel->reservas[i];
                    break;
                }
            }

            // Se o cliente e a reserva foram encontrados
            if(cliente != NULL && reserva != NULL) {
                // Se o cliente e provisório
                if (cliente->estadoFicha == PROVISORIA) {
                    // Move o cliente para o array de clientes definitivos
                    moverCliente(cliente->codigo, hotel->clientesProvisorios, &hotel->numClientesProvisorios, hotel->clientesDefinitivos, &hotel->numClientes);
                }

                // Atualiza o estado da ficha do cliente e a situacao da reserva
                cliente->estadoFicha = DEFINITIVA;
                reserva->situacaoReserva = 'C';
                printf("Check-in realizado com sucesso.\n");

                // Calcula e imprime o valor total
                valorTotal = calcularValorTotal(hotel, reserva->numeroReserva);
                if (valorTotal >= 0) {
                    printf("O valor total a pagar e: %.2f\n", valorTotal);
                } else {
                    printf("Nao foi possível calcular o valor total.\n");
                }
                registarPagamento(hotel, reserva, valorTotal);
            } else {
                printf("Cliente ou reserva nao encontrados.\n");
            }
        } else {
            printf("Check-in cancelado.\n");
        }
    }

    void checkOut(struct Hotel *hotel) {
    int codigoReserva;
    printf("Por favor, insira o código da reserva:\n");
    scanf("%d", &codigoReserva);

    struct Reserva* reserva = NULL;
    for (int i = 0; i < hotel->numReservas; i++) {
        if (hotel->reservas[i].numeroReserva == codigoReserva) {
            reserva = &hotel->reservas[i];
            break;
        }
    }

    if (reserva != NULL) {
        reserva->situacaoReserva = 'F'; // Atualiza a situação da reserva para finalizada

        char utilizouServicos;
        printf("Usufruiu de serviços extras? (S/N)\n");
        scanf(" %c", &utilizouServicos);

        double valorTotalServicos = 0.0;

        if (utilizouServicos == 'S' || utilizouServicos == 's') {
            printf("ID\tServiço\tValor\n");
            for (int i = 0; i < 9; i++) {
                printf("%d\t%s\t%.2f\n", hotel->valoresSuplementares[i].id, hotel->valoresSuplementares[i].tipoServico, hotel->valoresSuplementares[i].valor);
            }
            printf("\n");

            int idServico;
            double valorServico;

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
            // Registra o pagamento dos serviços extras
            registarPagamento(hotel, reserva, valorTotalServicos);
        }

        // Apaga a reserva após o checkout
        apagarReserva(hotel, codigoReserva);
    } else {
        printf("Reserva não encontrada.\n");
    }
}


double calcularValorTotal(struct Hotel *hotel, int numeroReserva) {
    int codigoQuarto = obterDesignacaoQuartoPorReserva(hotel, numeroReserva);
    struct CaracteristicasQuarto* quarto = obterQuartoPorCodigo(hotel, codigoQuarto);
    if (quarto == NULL) {
        printf("Quarto com codigo %d nao encontrado.\n", codigoQuarto);
        return -1.0;
    }

    int indicePrecoBase = obterPrecoBasePorQuarto(hotel, *quarto);
    if (indicePrecoBase == -1) {
        printf("Nao foi possível encontrar o preco base para o quarto.\n");
        return -1.0;
    }

    double precoBase = hotel->precosBase[indicePrecoBase].valor;

    
   // Procura a reserva correta
    struct Reserva *reserva = NULL;
    for (int i = 0; i < hotel->numReservas; i++) {
        if (hotel->reservas[i].numeroReserva == numeroReserva) {
            reserva = &hotel->reservas[i];
            break;
        }
    }

    // Verifica se a reserva foi encontrada
    if (reserva == NULL) {
        printf("Reserva nao encontrada.\n");
        return -1.0;
    }


    // Calcula o numero de dias da reserva
    int numDias = calcularDiferencaDias(reserva->dataCheckIn, reserva->dataCheckOut);

    double promo = 0.0; // Inicializa promo com 0

    if (strcmp(reserva->dataCheckIn, hotel->precosBase[indicePrecoBase].inicioPromocao) >= 0 && strcmp(reserva->dataCheckOut, hotel->precosBase[indicePrecoBase].fimPromocao) <= 0) {
        promo = hotel->precosBase[indicePrecoBase].valorPromocao;
        printf("A reserva esta dentro do periodo de promocao.\n");
    } else {
        printf("A reserva nao esta dentro do período de promocao.\n");
    }

    double extra = 0.0;
    char epoca = ' ';
    for (int i = 0; i < 4; i++) {
        if (strcmp(reserva->dataCheckOut, hotel->sobretaxas[i].fim) <= 0) {
            epoca = hotel->sobretaxas[i].epoca;
            extra = hotel->sobretaxas[i].percentualAdicional;
            printf("A reserva esta dentro da epoca %c.\n", epoca);
            break;
        }
    }

    if (epoca == ' ') {
        printf("A reserva nao esta dentro de nenhuma epoca.\n");
    }

    // Calcula o valor total
    double valorTotal = precoBase * numDias * ((100.0 - promo) / 100.0);
    valorTotal += valorTotal * (extra / 100.0);

    return valorTotal;
}

void alterarReserva(struct Hotel *hotel, int numeroReserva) {
    // Encontre a reserva com o numero fornecido
    for (int i = 0; i < hotel->numReservas; i++) {
        if (hotel->reservas[i].numeroReserva == numeroReserva) {
            // Solicite ao usuário os novos dados para a reserva
            printf("Insira os novos dados para a reserva:\n");

            // Por exemplo, se a reserva tem um campo 'quarto'
            printf("Codigo do quarto: ");
            scanf("%d", &hotel->reservas[i].codigoQuarto);
            while ((getchar()) != '\n'); // Limpa o buffer de entrada

            printf("Data do check-in (MM/DD): ");
            scanf("%6s", hotel->reservas[i].dataCheckIn);
            while ((getchar()) != '\n'); // Limpa o buffer de entrada

            printf("Data do check-out (MM/DD): ");
            scanf("%6s", hotel->reservas[i].dataCheckOut);
            while ((getchar()) != '\n'); // Limpa o buffer de entrada

            int numDias = calcularDiferencaDias(hotel->reservas[i].dataCheckIn, hotel->reservas[i].dataCheckOut);
            if (numDias < 0) {
                printf("A data de check-out deve ser posterior à data de check-in.\n");
                return;
            }
            hotel->reservas[i].numDias = numDias;

            printf("Numero de pessoas: ");
            int numPessoas;
            scanf("%d", &numPessoas);
            while ((getchar()) != '\n'); // Limpa o buffer de entrada

            // Verifique se o numero de pessoas e permitido para o quarto selecionado
            for (int j = 0; j < hotel->numQuartos; j++) {
                if (hotel->quartos[j].denominacao == hotel->reservas[i].codigoQuarto) {
                    switch (hotel->quartos[j].ocupacaoMaxima) {
                        case 'S': // Single
                            if (numPessoas > 1) {
                                printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                                return;
                            }
                            break;
                        case 'D': // Duplo
                            if (numPessoas > 2) {
                                printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                                return;
                            }
                            break;
                        case 'T': // Triplo
                            if (numPessoas > 3) {
                                printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                                return;
                            }
                            break;
                        case 'F': // Familiar
                            if (numPessoas > 5) {
                                printf("O numero de pessoas excede a ocupacao maxima do quarto selecionado.\n");
                                return;
                            }
                            break;
                    }
                    break;
                }
            }

            hotel->reservas[i].numPessoas = numPessoas;

            printf("Reserva alterada com sucesso.\n");
            return;
        }
    }

    printf("Nenhuma reserva encontrada com o numero fornecido.\n");
}

void apagarReserva(struct Hotel *hotel, int numeroReserva) {
    int index = -1;
    // Encontre a reserva com o numero fornecido
    for (int i = 0; i < hotel->numReservas; i++) {
        if (hotel->reservas[i].numeroReserva == numeroReserva) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Desloque todas as reservas após a reserva a ser apagada para a esquerda
        for (int i = index; i < hotel->numReservas - 1; i++) {
            hotel->reservas[i] = hotel->reservas[i + 1];
        }
        hotel->numReservas--;  // Decrementa o numero total de reservas

        printf("Reserva apagada com sucesso.\n");
    } else {
        printf("Nenhuma reserva encontrada com o numero fornecido.\n");
    }
}