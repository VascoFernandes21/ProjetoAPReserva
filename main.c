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

    carregarHotel(&hotel);
    menu(&hotel); // Display the menu
    salvarHotel(&hotel);
    guardarPagamentos(&hotel);

}