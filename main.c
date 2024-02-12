#include "funcoes.h"
#include "estruturas.h"
#include <stdio.h>

int main() {
    struct Hotel hotel;
    hotel.numClientes = 0;
    hotel.numClientesProvisorios = 0;
    hotel.numQuartos = 0; // Make sure to initialize numQuartos to 0

    int ultimoCodigoProvisorio = 0;
    int ultimoCodigoDefinitivo;
    int ultimoNumeroReserva = 0;
    int ultimoNumeroQuarto = 0; // Define this variable

    inicializarQuartos(&hotel); // Initialize the rooms
    inicializarHotel(&hotel); // Initialize the hotel
    inicializarPrecosBase(&hotel); // Initialize the base prices
    criarQuartosTeste(&hotel); // Create test rooms
    criarClientesDefinitivosTeste(&hotel, &ultimoCodigoDefinitivo); // Create test definitive clients
    criarClientesProvisoriosTeste(&hotel, &ultimoCodigoProvisorio); // Create test provisional clients
    criarReservaTeste(&hotel, &ultimoNumeroReserva); 
    


    menu(&hotel); // Display the menu
}