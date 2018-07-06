#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_YEAR 2014
#define MAX_YEAR 2018


// Testing
int
main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		printf("Error: Ingresar solo un argumento\n");
		return 1;
	}
	short year;
	year=atoi(argv[1]);
	if(year<MIN_YEAR || year>MAX_YEAR)
	{
		printf("Error: Ingresar un año que esté entre %d y %d\n", MIN_YEAR, MAX_YEAR);
		return 2;
	}

	FILE * aeropuertos, * movimientos;
	if( (aeropuertos=fopen("aeropuertos_detalle.csv", "r")) || (movimientos=fopen("eana1401-1802.csv", "r")))
	{
		printf("Error: No se pudo abrir un archivo\n");
		return 3;
	}

	doQueries(aeropuertos, movimientos, year);

	return 0;
}
