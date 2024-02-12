#include <string.h>
#include <stdio.h>
#include <stdbool.h> // Adicionado para utilizar o tipo de dado bool
#include <ctype.h> // Adicionado para utilizar a funcao toupper
#include <time.h>
#include <stdlib.h>
#include "funcoes.h"

struct Cliente* criarClienteProvisorio(struct Hotel *hotel, int *ultimoCodigoProvisorio) {
    if (hotel->numClientesProvisorios >= 1000) {
        printf("Limite de clientes provisorios atingido.\n");
        return NULL;
    }

    struct Cliente novoCliente;
    novoCliente.codigo = ++(*ultimoCodigoProvisorio);

    printf("Nome: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0; // Remove newline character

    printf("Morada: ");
    fgets(novoCliente.morada, sizeof(novoCliente.morada), stdin);
    novoCliente.morada[strcspn(novoCliente.morada, "\n")] = 0; // Remove newline character

    printf("Codigo Postal: ");
    fgets(novoCliente.codigoPostal, sizeof(novoCliente.codigoPostal), stdin);
    novoCliente.codigoPostal[strcspn(novoCliente.codigoPostal, "\n")] = 0; // Remove newline character

    printf("Localidade: ");
    fgets(novoCliente.localidade, sizeof(novoCliente.localidade), stdin);
    novoCliente.localidade[strcspn(novoCliente.localidade, "\n")] = 0; // Remove newline character

    printf("NIF: ");
    fgets(novoCliente.NIF, sizeof(novoCliente.NIF), stdin);
    novoCliente.NIF[strcspn(novoCliente.NIF, "\n")] = 0; // Remove newline character

    // Define a data de criacao como a data atual
    obterDataAtual(novoCliente.dataCriacao);

    do {
        printf("Tipo de cliente (N-Normal; V-Vip; E-Excelência): ");
        scanf(" %c", &novoCliente.tipoCliente);
        novoCliente.tipoCliente = toupper(novoCliente.tipoCliente);
    } while (novoCliente.tipoCliente != 'N' && novoCliente.tipoCliente != 'V' && novoCliente.tipoCliente != 'E');
    getchar();

    novoCliente.estadoFicha = PROVISORIA;

    hotel->clientesProvisorios[hotel->numClientesProvisorios] = novoCliente;

    printf("\nCliente provisorio criado com sucesso.\n");

    return &hotel->clientesProvisorios[hotel->numClientesProvisorios++];
}

void criarClienteDefinitivo(struct Hotel *hotel, int *ultimoCodigoDefinitivo) {
    if (hotel->numClientes >= 1000) {
        printf("Limite de clientes definitivos atingido.\n");
        return;
    }

    struct Cliente novoCliente;
    novoCliente.codigo = ++(*ultimoCodigoDefinitivo);

    printf("Nome: ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0; // Remove newline character

    printf("Morada: ");
    fgets(novoCliente.morada, sizeof(novoCliente.morada), stdin);
    novoCliente.morada[strcspn(novoCliente.morada, "\n")] = 0; // Remove newline character

    printf("Codigo Postal: ");
    fgets(novoCliente.codigoPostal, sizeof(novoCliente.codigoPostal), stdin);
    novoCliente.codigoPostal[strcspn(novoCliente.codigoPostal, "\n")] = 0; // Remove newline character

    printf("Localidade: ");
    fgets(novoCliente.localidade, sizeof(novoCliente.localidade), stdin);
    novoCliente.localidade[strcspn(novoCliente.localidade, "\n")] = 0; // Remove newline character

    printf("NIF: ");
    fgets(novoCliente.NIF, sizeof(novoCliente.NIF), stdin);
    novoCliente.NIF[strcspn(novoCliente.NIF, "\n")] = 0; // Remove newline character

    obterDataAtual(novoCliente.dataCriacao);
do {
    printf("Tipo de cliente (N-Normal; V-Vip; E-Excelência): ");
    scanf(" %c", &novoCliente.tipoCliente);
    getchar();
    novoCliente.tipoCliente = toupper(novoCliente.tipoCliente); // Converte a entrada para maiusculas

    if (novoCliente.tipoCliente != 'N' && novoCliente.tipoCliente != 'V' && novoCliente.tipoCliente != 'E') {
        printf("Entrada invalida. Por favor, insira N, V ou E.\n");
    }
} while (novoCliente.tipoCliente != 'N' && novoCliente.tipoCliente != 'V' && novoCliente.tipoCliente != 'E');

    novoCliente.estadoFicha = DEFINITIVA;

    hotel->clientesDefinitivos[hotel->numClientes++] = novoCliente;

    printf("\nCliente definitivo criado com sucesso.\n");
}

void mostrarClientes(struct Hotel *hotel) {
    char tipoCliente;

    // Pergunta ao usuario que tipo de cliente ele quer ver
    printf("Mostrar clientes provisorios (P) ou definitivos (D)? ");
    scanf(" %c", &tipoCliente);
    tipoCliente = toupper(tipoCliente); // Converte a entrada para maiusculas

    if (tipoCliente == 'P') {
        // Mostra os clientes provisorios
        for (int i = 0; i < hotel->numClientesProvisorios; i++) {
            printf("Cliente %d: %s\n", hotel->clientesProvisorios[i].codigo, hotel->clientesProvisorios[i].nome);
            printf("Morada: %s\n", hotel->clientesProvisorios[i].morada);
            printf("NIF: %s\n", hotel->clientesProvisorios[i].NIF);
            printf("Data de Criacao: %s\n", hotel->clientesProvisorios[i].dataCriacao);
            printf("\n");
        }
    } else if (tipoCliente == 'D') {
        // Mostra os clientes definitivos
        for (int i = 0; i < hotel->numClientes; i++) {
            printf("Cliente %d: %s\n", hotel->clientesDefinitivos[i].codigo, hotel->clientesDefinitivos[i].nome);
            printf("Morada: %s\n", hotel->clientesDefinitivos[i].morada);
            printf("NIF: %s\n", hotel->clientesDefinitivos[i].NIF);
            printf("Data de Criacao: %s\n", hotel->clientesDefinitivos[i].dataCriacao);
            printf("\n");
        }
    } else {
        printf("Entrada invalida. Por favor, insira P para clientes provisorios ou D para clientes definitivos.\n");
    }
}
struct Cliente* ProcurarProvisorio(struct Hotel *hotel) {
    int codigo;
    printf("Insira o codigo do cliente provisorio: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < hotel->numClientesProvisorios; i++) {
        if (hotel->clientesProvisorios[i].codigo == codigo) {
            return &hotel->clientesProvisorios[i];
        }
    }

    printf("Cliente provisorio nao encontrado.\n");
    return NULL;
}

struct Cliente* ProcurarDefinitivo(struct Hotel *hotel) {
    int codigo;
    printf("Insira o codigo do cliente definitivo: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < hotel->numClientes; i++) {
        if (hotel->clientesDefinitivos[i].codigo == codigo) {
            return &hotel->clientesDefinitivos[i];
        }
    }

    printf("Cliente definitivo nao encontrado.\n");
    return NULL;
}

void alterarClienteProvisorio(struct Hotel *hotel) {
    int codigo;
    printf("Insira o codigo do cliente provisorio a alterar: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < hotel->numClientesProvisorios; i++) {
        if (hotel->clientesProvisorios[i].codigo == codigo) {
            printf("Nome: ");
            fgets(hotel->clientesProvisorios[i].nome, sizeof(hotel->clientesProvisorios[i].nome), stdin);
            hotel->clientesProvisorios[i].nome[strcspn(hotel->clientesProvisorios[i].nome, "\n")] = 0; // Remove newline character

            printf("Morada: ");
            fgets(hotel->clientesProvisorios[i].morada, sizeof(hotel->clientesProvisorios[i].morada), stdin);
            hotel->clientesProvisorios[i].morada[strcspn(hotel->clientesProvisorios[i].morada, "\n")] = 0; // Remove newline character

            printf("Codigo Postal: ");
            fgets(hotel->clientesProvisorios[i].codigoPostal, sizeof(hotel->clientesProvisorios[i].codigoPostal), stdin);
            hotel->clientesProvisorios[i].codigoPostal[strcspn(hotel->clientesProvisorios[i].codigoPostal, "\n")] = 0; // Remove newline character

            printf("Localidade: ");
            fgets(hotel->clientesProvisorios[i].localidade, sizeof(hotel->clientesProvisorios[i].localidade), stdin);
            hotel->clientesProvisorios[i].localidade[strcspn(hotel->clientesProvisorios[i].localidade, "\n")] = 0; // Remove newline character

            printf("NIF: ");
            fgets(hotel->clientesProvisorios[i].NIF, sizeof(hotel->clientesProvisorios[i].NIF), stdin);
            hotel->clientesProvisorios[i].NIF[strcspn(hotel->clientesProvisorios[i].NIF, "\n")] = 0; // Remove newline character

            // Define a data de criacao como a data atual
            obterDataAtual(hotel->clientesProvisorios[i].dataCriacao);

            do {
                printf("Tipo de cliente (N-Normal; V-Vip; E-Excelência): ");
                scanf(" %c", &hotel->clientesProvisorios[i].tipoCliente);
                hotel->clientesProvisorios[i].tipoCliente = toupper(hotel->clientesProvisorios[i].tipoCliente);
            } while (hotel->clientesProvisorios[i].tipoCliente != 'N' && hotel->clientesProvisorios[i].tipoCliente != 'V' && hotel->clientesProvisorios[i].tipoCliente != 'E');
            getchar();

            printf("\nCliente provisorio alterado com sucesso.\n");
            return;
        }
    }

    printf("Cliente provisorio nao encontrado.\n");
}

void eliminarClienteProvisorio(struct Hotel *hotel) {
    int codigo;
    printf("Insira o codigo do cliente provisorio a eliminar: ");
    scanf("%d", &codigo);
    getchar();

    for (int i = 0; i < hotel->numClientesProvisorios; i++) {
        if (hotel->clientesProvisorios[i].codigo == codigo) {
            // Move todos os clientes após o cliente a ser removido uma posicao para tras
            for (int j = i; j < hotel->numClientesProvisorios - 1; j++) {
                hotel->clientesProvisorios[j] = hotel->clientesProvisorios[j + 1];
            }

            hotel->numClientesProvisorios--;

            printf("\nCliente provisorio eliminado com sucesso.\n");
            return;
        }
    }

    printf("Cliente provisorio nao encontrado.\n");
}

void moverCliente(int idClienteProvisorio, struct Cliente* clientesProvisorios, int* numClientesProvisorios, struct Cliente* clientesDefinitivos, int* numClientesDefinitivos) {
    // Encontre o cliente provisório
    for (int i = 0; i < *numClientesProvisorios; i++) {
        if (clientesProvisorios[i].codigo == idClienteProvisorio) {
            // Adicione o cliente ao array de clientes definitivos
            clientesDefinitivos[*numClientesDefinitivos] = clientesProvisorios[i];
            // Atribua o próximo código disponível ao cliente
            clientesDefinitivos[*numClientesDefinitivos].codigo = *numClientesDefinitivos + 1;
            (*numClientesDefinitivos)++;

            // Remova o cliente do array de clientes provisórios
            for (int j = i; j < *numClientesProvisorios - 1; j++) {
                clientesProvisorios[j] = clientesProvisorios[j + 1];
            }
            (*numClientesProvisorios)--;

            // Corrija os códigos dos clientes provisórios restantes
            for (int j = i; j < *numClientesProvisorios; j++) {
                clientesProvisorios[j].codigo = j + 1;
            }

            return;
        }
    }

    printf("Cliente provisório com código %d nao encontrado.\n", idClienteProvisorio);
}



//teste


void criarClientesProvisoriosTeste(struct Hotel *hotel, int *ultimoCodigoProvisorio) {
    struct Cliente clientesTeste[5] = {
        {++(*ultimoCodigoProvisorio), "Cliente 1P", "Morada 1", "1234-567", "Localidade 1", "123456789", "01/01", 'N', PROVISORIA},
        {++(*ultimoCodigoProvisorio), "Cliente 2P", "Morada 2", "2345-678", "Localidade 2", "234567890", "02/02", 'V', PROVISORIA},
        {++(*ultimoCodigoProvisorio), "Cliente 3P", "Morada 3", "3456-789", "Localidade 3", "345678901", "03/03", 'E', PROVISORIA},
        {++(*ultimoCodigoProvisorio), "Cliente 4P", "Morada 4", "4567-890", "Localidade 4", "456789012", "04/04", 'N', PROVISORIA},
        {++(*ultimoCodigoProvisorio), "Cliente 5P", "Morada 5", "5678-901", "Localidade 5", "567890123", "05/05", 'V', PROVISORIA}
    };

    for (int i = 0; i < 5; i++) {
        if (hotel->numClientesProvisorios >= 1000) {
            printf("Limite de clientes provisorios atingido.\n");
            return;
        }

        hotel->clientesProvisorios[hotel->numClientesProvisorios++] = clientesTeste[i];
    }

    printf("\nClientes provisorios de teste criados com sucesso.\n");
}

void criarClientesDefinitivosTeste(struct Hotel *hotel, int *ultimoCodigoDefinitivo) {
    struct Cliente clientesTeste[5] = {
        {++(*ultimoCodigoDefinitivo), "Cliente 1D", "Morada 1", "1234-567", "Localidade 1", "123456789", "01/01", 'N', DEFINITIVA},
        {++(*ultimoCodigoDefinitivo), "Cliente 2D", "Morada 2", "2345-678", "Localidade 2", "234567890", "02/02", 'V', DEFINITIVA},
        {++(*ultimoCodigoDefinitivo), "Cliente 3D", "Morada 3", "3456-789", "Localidade 3", "345678901", "03/03", 'E', DEFINITIVA},
        {++(*ultimoCodigoDefinitivo), "Cliente 4D", "Morada 4", "4567-890", "Localidade 4", "456789012", "04/04", 'N', DEFINITIVA},
        {++(*ultimoCodigoDefinitivo), "Cliente 5D", "Morada 5", "5678-901", "Localidade 5", "567890123", "05/05", 'V', DEFINITIVA}
    };

    for (int i = 0; i < 5; i++) {
        if (hotel->numClientes >= 1000) {
            printf("Limite de clientes definitivos atingido.\n");
            return;
        }

        hotel->clientesDefinitivos[hotel->numClientes++] = clientesTeste[i];
    }

    printf("\nClientes definitivos de teste criados com sucesso.\n");
}


