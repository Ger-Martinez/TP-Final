#include <stdio.h>

#include "functions.h"

#include "airportsADT.h"

#define SIZE_FIRST_LINE_A 184

#define SIZE_FIRST_LINE_F 144

#define CANT_AEROPUERTOS 5



int

main (void)

{

	FILE * archF=fopen("eana1401-1802.csv", "r");
	FILE * archA=fopen("aeropuertos_detalle.csv", "r");
	if( archA ==NULL || archF == NULL)
	{
		printf("Error: Alguno de los archivos se pudo abrir :( \n");
		return 1;
	}
	/* Salteo la primera linea de titulos del archivo de Vuelos */
	char * trash=malloc(SIZE_FIRST_LINE_F+2);
	fgets(trash, SIZE_FIRST_LINE_F, archF);
	free(trash);

	/* Salteo la primera linea de titulos del archivo de Aeropuertos */
	trash=malloc(SIZE_FIRST_LINE_A+2);
	fgets(trash, SIZE_FIRST_LINE_A, archA);
	free(trash);

    /* Comienzo a trabajar */
    airportADT ap = newAirportList();
    flightADT f = newFlightList();
    airlineQueryADT ar = newAirlineList();

	addAirports( ap , archA );
	addFlights( ap , ar , f , "2014" , archF );

	showMeAirlines( ar );


	return 0;

}
