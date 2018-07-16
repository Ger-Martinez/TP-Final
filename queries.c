#include <stdio.h>
#include <stdlib.h>
#include "airportADT.h"
#include "functions.h"
#include "queries.h"

void query1(FILE * resp, airportADT airports)
{
	tAirport aux;
	toBeginAirport(airports);
	while(hasNextAirport(airports))
	{
		aux=nextAirport(airports);
		if(aux->landings + aux->takeOffs)
			fprintf(resp, "%s;%s;%s;%u\n", aux->oaci, aux->local, aux->name, (aux->takeOffs + aux->landings));		
	}
}

void query2(FILE * resp, airportADT airports)
{
	tAirport aux;
	toBeginAirport(airports);
	while(hasNextAirport(airports))
	{
		aux=nextAirport(airports);
		if(aux->isInternational && (aux->landings + aux->takeOffs))
			fprintf(resp, "%s;%s;%u;%u;%u\n", aux->oaci, aux->iata, aux->takeOffs, aux->landings, aux->landings + aux->takeOffs);
	}
}

void query3(FILE * resp, airportADT airports)
{
	unsigned int days[7]=getDayVec(airports);
	fprintf(resp, "Lunes;%u\n", days[1]);
	fprintf(resp, "Martes;%u\n", days[2]);
	fprintf(resp, "Miercoles;%u\n", days[3]);
	fprintf(resp, "Jueves;%u\n", days[4]);
	fprintf(resp, "Viernes:%u\n", days[5]);
	fprintf(resp, "Sabado;%u\n", days[6]);
	fprintf(resp, "Domingo;%u\n", days[0]);
}

void query4(FILE * resp, airportADT airports)
{
	tAirport aux;
	tDestination dest;
	toBeginAirport(airports);
	while(hasNextAirport(airports))
	{
		aux=nextAirport(airports);
		toBeginDestinations(aux->destinations);
		while(hasNextDestination(aux->destinations))
		{
			dest=nextDestination(aux->destinations);
			fprintf(resp, "%s;%s;%u;%u\n", aux->oaci, dest->oaci, dest->landings, dest->takeOffs);
		}
	}
}

void query5(FILE * resp, airportADT airports)
{
	tAirport aux;
	toBeginAirport(airports);
	total=getTotal(airports);
	while(hasNextAirport(airports))
	{
		aux=nextAirport(airports);
		if(aux->isInternational && (aux->landings + aux->takeOffs))
		{
			fprintf(resp, "%s;%s;%u;%u;%u;%.2f\n", aux->oaci, aux->iata, aux->takeOffs, aux->landings, aux->landings + aux->takeOffs, (aux->landings + aux->takeOffs)*100/(float)total);
		}
	}
}

void query6(FILE * resp, airlinesADT airlines)
{
	tAirline aux;
	toBeginAirlines(airlines);
	while(hasNextAirport(airlines))
	{
		aux=nextAirline(airlines);
		fprintf(resp, "%s;%u\n", aux->name, aux->movs);
	}
}

void query7(FILE * resp, airportADT airports)
{
	fprintf(resp, "Aterrizaje;Cabotaje;%u\n", );
	fprintf(resp, "Aterrizaje;Internacional;%u\n", );
	fprintf(resp, "Despegue;Cabotaje;%u\n", );
	fprintf(resp, "Despegue;Internacional;%u\n", );
}