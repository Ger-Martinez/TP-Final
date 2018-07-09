#include <stdio.h>
#include "funciones.h"
#include "airportCDT.h"

#define SIZE_FIRST_LINE 300
#define CANT_VUELOS 4

int 
main (void)
{
	FILE * arch=fopen("eana1401-1802.csv", "r");
	if(arch==NULL)
	{
		printf("Error: No se pudo abrir el archivo\n");
		return 1;
	}
	/*Salteo la primera linea de titulos del archivo*/
	char * trash=malloc(SIZE_FIRST_LINE+2);
	fgets(trash, SIZE_FIRST_LINE, arch);
	free(trash);

	TFlight flight;
	for(int i=0; i<CANT_VUELOS; i++)
	{
		flight=readFlight(arch);
		if(flight==NULL)
		{
			printf("NO HAY MAS VUELOS\n");
			return 1;
		}
		printf("Fecha: %s\n", flight->date);
		printf("Hora: %s\n", flight->time);
		printf("Tipo: %s\n", (flight->type==1)?"Internacional":((flight->type==-1)?"Cabotaje":""));
		printf("Movimiento: %s\n", (flight->mv==1)?"Aterrizaje":((flight->mv==-1)?"Despegue":""));
		printf("OR_OACI: %s\n", flight->or_oaci);
		printf("DST_OACI: %s\n", flight->dst_oaci);
		printf("Aerolinea: %s\n", flight->airline);
		free(flight->airline);
		free(flight);
		putchar('\n');
	}
	return 0;
}