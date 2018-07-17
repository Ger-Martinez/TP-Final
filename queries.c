#include <stdio.h>
#include <stdlib.h>
#include "airportADT.h"
#include "functions.h"
#include "airlineADT.h"
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
	unsigned int v[7];
	vectorDias( airports, v);
	fprintf(resp, "Lunes;%u\n", v[1]);
	fprintf(resp, "Martes;%u\n", v[2]);
	fprintf(resp, "Miercoles;%u\n", v[3]);
	fprintf(resp, "Jueves;%u\n", v[4]);
	fprintf(resp, "Viernes:%u\n", v[5]);
	fprintf(resp, "Sabado;%u\n", v[6]);
	fprintf(resp, "Domingo;%u\n", v[0]);
}

void query4(FILE * resp, airportADT airports)
{
	tAirport aux;
	tDestination dest;
	toBeginAirport(airports);
	while(hasNextAirport(airports))
	{
		aux=nextAirport(airports);
		toBeginDestination(aux->destinations);
		while(hasNextDestination(aux->destinations))
		{
			dest=nextDestination(aux->destinations);
			fprintf(resp, "%s;%s;%u;%u\n", aux->oaci, dest->oaci, dest->landings, dest->takeOffs);
		}
	}
}

void query5(FILE * resp, internationalADT interList)
{
	tInter aux;
	toBeginInter(interList);
	int total=getTotal(interList);
	while(hasNextInter(interList))
	{
		aux=nextInter(interList);
		fprintf(resp, "%s;%u;%u;%u;%.2f\n", aux->iata, aux->takeOffs, aux->landings, aux->landings + aux->takeOffs, (aux->landings + aux->takeOffs)*100/(float)total);
	}
}

void query6(FILE * resp, airlineADT airlines)
{
	tAirline aux;
	toBeginAirline(airlines);
	while(hasNextAirline(airlines))
	{
		aux=nextAirline(airlines);
		fprintf(resp, "%s;%u\n", aux->name, aux->movs);
	}
}

void query7(FILE * resp, airportADT airport)
{
	unsigned int v[4];
	query7Vector( airport, v );
	fprintf(resp, "Aterrizaje;Cabotaje;%u\n", v[0]);
	fprintf(resp, "Aterrizaje;Internacional;%u\n", v[1] );
	fprintf(resp, "Despegue;Cabotaje;%u\n", v[2] );
	fprintf(resp, "Despegue;Internacional;%u\n", v[3] );
}
