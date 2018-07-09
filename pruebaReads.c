#include <stdio.h>
#include "funciones.h"
#include "airportCDT.h"

#define SIZE_FIRST_LINE 182
#define CANT_AEROPUERTOS 50

int 
main (void)
{
	FILE * arch=fopen("aeropuertos_detalle.csv", "r");
	if(arch==NULL)
	{
		printf("Error: No se pudo abrir el archivo\n");
		return 1;
	}
	/*Salteo la primera linea de titulos del archivo*/
	char * trash=malloc(SIZE_FIRST_LINE+2);
	fgets(trash, SIZE_FIRST_LINE, arch);
	free(trash);

	tAirport air;
	for(int i=0; i<CANT_AEROPUERTOS; i++)
	{
		air=readAirport(arch);
		if(air==NULL)
		{
			printf("NO HAY MAS AEROPUERTOS\n");
			return 1;
		}
		printf("Local: %s\n", air->local_code);
		printf("OACI: %s\n", air->OACI);
		printf("IATA: %s\n", air->IATA);
		printf("Tipo: %s\n", (air->type==1)?"Aeródromo":((air->type==2)?"Helipuerto":""));
		printf("Nombre: %s\n", air->name);
		printf("Condicion: %s\n", (air->condition==1)?"Publico":((air->condition==2)?"Privado":""));
		printf("Trafico: %s\n", (air->traffic==1)?"Nacional":((air->traffic==2)?"Internacional":""));
		free(air);
		putchar('\n');
	}
	return 0;
}