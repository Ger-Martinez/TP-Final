#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "airportADT.h"
#include "destinationADT.h"
#include "airlineADT.h"
#include "queries.h"
#define MAX_YEAR "2018"
#define MIN_YEAR "2014"
#define SIZE_FIRST_LINE_A 184
#define SIZE_FIRST_LINE_F 144
#define CANT_AEROPUERTOS 5

int
main(int argc, char const *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr, "Error: Se debe ingresar un solo año\n");
		return 1;
	}
	if(strcmp(argv[1],MAX_YEAR)>0 || strcmp(argv[1],MIN_YEAR)<0)
	{
		fprintf(stderr, "Error: El año ingresado no esta adentro del rango\n");
		return 2;
	}
	FILE * archF=fopen("eana1401-1802.csv", "r");
	FILE * archA=fopen("aeropuertos_detalle.csv", "r");

	if( archA == NULL || archF == NULL)
	{
		fprintf(stderr, "Error: Alguno de los archivos se pudo abrir\n");
		return 3;
	}

	/* Salteo la primera linea de titulos del archivo de vuelos */
	char * trash=malloc(SIZE_FIRST_LINE_F+2);
	fgets(trash, SIZE_FIRST_LINE_F, archF);
	free(trash);

	/* Salteo la primera linea de titulos del archivo de aeropuertos */
	trash=malloc(SIZE_FIRST_LINE_A+2);
	fgets(trash, SIZE_FIRST_LINE_A, archA);
	free(trash);

    /* Comienzo a trabajar */

    airportADT airport = newAirportList();
    internationalADT inter = newInternationalList();
		airlineADT airline = newAirlineList();
    addAirports( airport , archA );
    addMovements( airport , inter , airline , archF , argv[1]);

	FILE *query1F = fopen("movs_aeropuerto.csv", "w");
	FILE *query2F = fopen("movs_internacional.csv", "w");
	FILE *query3F = fopen("semanal.csv", "w");
	FILE *query4F = fopen("aerop_detalle.csv", "w");
	FILE *query5F = fopen("movs_internacion5.csv", "w");
	FILE *query6F = fopen("aerolinea.csv","w");
	FILE *query7F = fopen("movimiento.csv", "w");

	query1(query1F, airport);
	query2(query2F, airport);
	query3(query3F, airport);
	query4(query4F, airport);
	query5(query5F, inter  );
query7(query7F, airport);

	fclose(query1F);
	fclose(query2F);
	fclose(query3F);
	fclose(query4F);
	fclose(query5F);
	fclose(query6F);
	fclose(query7F);

	return 0;
}
