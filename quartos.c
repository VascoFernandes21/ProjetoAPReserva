#include <string.h>
#include <stdio.h>
#include <stdbool.h> 
#include <ctype.h> 
#include <time.h>
#include <stdlib.h>
#include "funcoes.h"

void inicializarQuartos(struct Hotel *hotel) {
    for (int i = 0; i < 400; i++) {
        hotel->quartos[i].denominacao = 0;
    }
}

void criarQuarto(struct Hotel *hotel) {
    int torre, andar, numeroQuarto;
    char vista, qualidade, ocupacaoMaxima;


    // Verifica se ja atingiu o limite total de quartos (200 por torre, 2 torres)
    if (hotel->numQuartos >= 2 * 200) {
        printf("O hotel ja atingiu o limite de quartos.\n");
        return;
    }

    // Loop para garantir que o andar inserido e valido (entre 1 e 10)
    while (1) {
        printf("Andar (1 a 10): ");
        scanf("%d", &andar);
        if (andar < 1 || andar > 10) {
            printf("Andar invalido. Deve ser um numero entre 1 e 10.\n");
        } else {
            break; // Sai do loop se o andar for valido
        }
    }

    // Loop para garantir que o numero do quarto no andar e valido (entre 1 e 20)
    while (1) {
        printf("Numero do Quarto no Andar: ");
        scanf("%d", &numeroQuarto);
        if (numeroQuarto < 1 || numeroQuarto > 20) {
            printf("Numero do Quarto invalido. Deve ser um numero entre 1 e 20.\n");
        } else {
            break; // Sai do loop se o numero do quarto for valido
        }
    }

    // Loop para garantir que a vista inserida e valida ('M', 'P')
    while (1) {
        printf("Vista (M-Mar, P-Piscina/Parque de Diversões): ");
        scanf(" %c", &vista); // Alterado para ler um unico caractere

        // Converte a primeira letra para maiuscula
        vista = toupper(vista);

        if (vista != 'M' && vista != 'P') {
            printf("Vista invalida. Deve ser 'M' ou 'P'.\n");
        } else {
            break; // Sai do loop se a vista for valida
        }
    }

    // Loop para garantir que a qualidade inserida e valida ('B', 'S')
    while (1) {
        printf("Qualidade (B-Base, S-Superior): ");
        scanf(" %c", &qualidade); // Alterado para ler um unico caractere

        // Converte a primeira letra para maiuscula
        qualidade = toupper(qualidade);

        if (qualidade != 'B' && qualidade != 'S') {
            printf("Qualidade invalida. Deve ser 'B' ou 'S'.\n");
        } else {
            break; // Sai do loop se a qualidade for valida
        }
    }

    // Loop para garantir que a ocupacao maxima inserida e valida ('S', 'D', 'T', 'F')
    while (1) {
        printf("Numero Maximo de Pessoas (S-Single; D-Duplo; T-Triplo; F-Familiar (max. 5 pessoas)): ");
        scanf(" %c", &ocupacaoMaxima); // Ja estava lendo um unico caractere

        ocupacaoMaxima = toupper(ocupacaoMaxima); // Converte o caractere para maiusculo

        if (ocupacaoMaxima != 'S' && ocupacaoMaxima != 'D' && ocupacaoMaxima != 'T' && ocupacaoMaxima != 'F') {
            printf("Ocupacao maxima invalida. Deve ser 'S', 'D', 'T' ou 'F'.\n");
        } else {
            break; // Sai do loop se a ocupacao maxima for valida
        }
    }


    // Define a torre com base no numero do quarto, se for abaixo de 200 vai para a torre 1, se for acima torre 2
    torre = (hotel->numQuartos < 200) ? 1 : 2;

    // Atribui automaticamente a denominacao do quarto
    hotel->quartos[hotel->numQuartos].vista = vista;
    hotel->quartos[hotel->numQuartos].qualidade = qualidade;
    hotel->quartos[hotel->numQuartos].ocupacaoMaxima = ocupacaoMaxima;
    hotel->quartos[hotel->numQuartos].torre = torre;
    hotel->quartos[hotel->numQuartos].andar = andar;
    hotel->quartos[hotel->numQuartos].numeroQuarto = numeroQuarto;
    hotel->quartos[hotel->numQuartos].denominacao = torre * 10000 + andar * 100 + numeroQuarto;
    // Incrementa o numero total de quartos no hotel
    hotel->numQuartos++;
}


void mostrarQuartos(struct Hotel *hotel) {
    printf("Quartos existentes:\n");
    printf("----------------------------------------------------------------------------\n");
    printf("| Torre | Andar | Numero | Vista | Qualidade | Ocupacao Max. | Denominacao |\n");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < hotel->numQuartos; i++) {
        printf("|   %d   |   %2d   |   %3d   |   %c   |     %c     |        %c       |   %5d    |\n",
               hotel->quartos[i].torre, hotel->quartos[i].andar, hotel->quartos[i].numeroQuarto,
               hotel->quartos[i].vista, hotel->quartos[i].qualidade, hotel->quartos[i].ocupacaoMaxima,
               hotel->quartos[i].denominacao);
    }

    printf("-------------------------------------------------------------------\n");
}


void mostrarQuartoPorDenominacao(struct Hotel *hotel) {
    int denominacao;

    printf("Insira a denominacao do quarto que procura: ");
    scanf("%d", &denominacao);

    for (int i = 0; i < hotel->numQuartos; i++) {
        if (hotel->quartos[i].denominacao == denominacao) {
            printf("Quarto encontrado:\n");
            printf("Torre: %d\n", hotel->quartos[i].torre);
            printf("Andar: %d\n", hotel->quartos[i].andar);
            printf("Numero do Quarto: %d\n", hotel->quartos[i].numeroQuarto);
            printf("Vista: %c\n", hotel->quartos[i].vista);
            printf("Qualidade: %c\n", hotel->quartos[i].qualidade);
            printf("Ocupacao Maxima: %c\n", hotel->quartos[i].ocupacaoMaxima);
            return;
        }
    }

    printf("Nenhum quarto encontrado com a denominacao %d.\n", denominacao);
}

void alterarQuarto(struct Hotel *hotel) {
    int denominacao;
    char vista, qualidade;
    int ocupacaoMaxima, disponivelParaReserva;

    printf("Insira a denominacao do quarto que deseja alterar: ");
    scanf("%d", &denominacao);

    for (int i = 0; i < hotel->numQuartos; i++) {
        if (hotel->quartos[i].denominacao == denominacao) {
            printf("Insira a nova vista (M-Mar, P-Piscina/Parque de Diversões): ");
            scanf(" %c", &vista); // note the space before %c
            printf("Insira a nova qualidade (B-Base, S-Superior): ");
            scanf(" %c", &qualidade); // note the space before %c
            printf("Insira a nova ocupacao maxima: ");
            scanf("%d", &ocupacaoMaxima);

            hotel->quartos[i].vista = vista;
            hotel->quartos[i].qualidade = qualidade;
            hotel->quartos[i].ocupacaoMaxima = ocupacaoMaxima;

            printf("Quarto %d atualizado com sucesso!\n", denominacao);
            return;
        }
    }

    printf("Nenhum quarto encontrado com a denominacao %d.\n", denominacao);
}

void removerQuartoPorDenominacao(struct Hotel *hotel) {
    int denominacao;
    printf("Insira a denominacao do quarto que deseja remover: ");
    scanf("%d", &denominacao);

    int indiceRemover = -1;

    // Procurar o quarto com a denominacao fornecida
    for (int i = 0; i < hotel->numQuartos; i++) {
        if (hotel->quartos[i].denominacao == denominacao) {
            indiceRemover = i;
            break;  // Encontrou o quarto, pode sair do loop
        }
    }

    // Se o quarto foi encontrado, remover e mover os quartos subsequentes
    if (indiceRemover != -1) {
        for (int i = indiceRemover; i < hotel->numQuartos - 1; i++) {
            hotel->quartos[i] = hotel->quartos[i + 1];
        }
        // Decrementar o contador de quartos
        hotel->numQuartos--;
        printf("Quarto com a denominacao %d foi removido com sucesso.\n", denominacao);
    } else {
        printf("Nenhum quarto encontrado com a denominacao %d.\n", denominacao);
    }
}

//testeee

void criarQuartosTeste(struct Hotel *hotel) {
    struct CaracteristicasQuarto quartosTeste[] = {
        { .denominacao = 10101, .vista = 'P', .qualidade = 'B', .ocupacaoMaxima = 'D', .torre = 1, .andar = 1, .numeroQuarto = 1 },
        { .denominacao = 10201, .vista = 'P', .qualidade = 'S', .ocupacaoMaxima = 'D',  .torre = 1, .andar = 2, .numeroQuarto = 1 },
        { .denominacao = 10301, .vista = 'M', .qualidade = 'B', .ocupacaoMaxima = 'T',  .torre = 1, .andar = 3, .numeroQuarto = 1 },
        { .denominacao = 10401, .vista = 'P', .qualidade = 'S', .ocupacaoMaxima = 'F',  .torre = 1, .andar = 4, .numeroQuarto = 1 },
        // Continue adicionando quartos conforme necessario
    };

    int numQuartosTeste = sizeof(quartosTeste) / sizeof(struct CaracteristicasQuarto);

    for (int i = 0; i < numQuartosTeste; i++) {
        if (hotel->numQuartos >= 2 * 200) {
            printf("O hotel ja atingiu o limite de quartos.\n");
            return;
        }

        hotel->quartos[hotel->numQuartos++] = quartosTeste[i]; // Incrementa numQuartos após adicionar o quarto
        printf("Quarto %d criado com sucesso.\n", quartosTeste[i].denominacao);
    }
}

bool verificarDisponibilidadeQuarto(struct Hotel *hotel, int codigoQuarto, char *data) {
    for (int i = 0; i < hotel->numReservas; i++) {
        if (hotel->reservas[i].codigoQuarto == codigoQuarto) {
            if (strcmp(data, hotel->reservas[i].dataCheckIn) >= 0 && strcmp(data, hotel->reservas[i].dataCheckOut) <= 0) {
                return false;
            }
        }
    }
    return true;
}

    struct CaracteristicasQuarto* obterQuartoPorCodigo(struct Hotel* hotel, int codigoQuarto) {
        for (int i = 0; i < hotel->numQuartos; i++) {
            if (hotel->quartos[i].denominacao == codigoQuarto) {
                return &hotel->quartos[i];
            }
        }
        return NULL;
    }