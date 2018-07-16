#include <stdio.h>
#include <stdlib.h>
#include "airportADT.h"
#include "functions.h"
#include "queries.h"

void query1(FILE * resp, airportADT airports)
{
	tAirport aux;
	toBegin(airports);
	while(hasNext(airports))
	{
		if(aux->landings + aux->takeOffs)
		{
			aux=nextAirport(airports);
			fprintf(resp, "%s;%s;%s;%d\n", aux->oaci, aux->local, aux->name, (aux->takeOffs + aux->landings));		
		}
	}
}