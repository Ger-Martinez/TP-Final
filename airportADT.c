#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airportADT.h"
#include "airlineADT.h"
#include "destinationADT.h"
#include "functions.h"

typedef struct airportNode * tAirportNode;
typedef struct interNode * tInterNode;


struct airportNode
{
	tAirport airport;
	struct airportNode * next;
};

struct airportCDT
{
	tAirportNode first;
	tAirportNode iterator;
	unsigned int days [7];
	unsigned int query7[4];
	/*(aterrizaje,cabotaje),(aterrizaje, internacional), (despegue,cabotaje), (despegue, internacional)*/
};

struct interNode
{
    tInter inter;
    struct interNode * next;
};

struct internationalCDT
{
	tInterNode first;
  tInterNode iterator;
	unsigned int totalMoves;
};

airportADT newAirportList(void)
{
	return calloc(1, sizeof(struct airportCDT));
}

static tAirportNode addAirportRec ( tAirportNode first , tAirport newAp )
{
    if(first == NULL || (strcmp( first -> airport -> oaci , newAp -> oaci )>0))
    {
        tAirportNode aux = malloc(sizeof(*aux));
        aux -> airport = newAp;
        aux -> next = first;
        return aux;
    }
    // Se asume que no hay 2 aeropuertos con el mismo OACI
    first -> next = addAirportRec( first -> next , newAp );
    return first;
}

void addAirports ( airportADT ap , FILE * a )
{
    tAirport toAdd=readAirport( a );
    while(toAdd)
    {
        if(toAdd -> oaci[0])
        {
            ap -> first = addAirportRec ( ap -> first , toAdd );
        } else free(toAdd);
        toAdd = readAirport( a );
    }
}

void toBeginAirport(airportADT airport)
{
    airport->iterator=airport->first;
}

int hasNextAirport(airportADT airport)
{
    return airport->iterator != NULL;
}

tAirport nextAirport(airportADT airport)
{
    if(hasNextAirport(airport))
    {
        tAirport aux=airport->iterator->airport;
        airport->iterator=airport->iterator->next;
        return aux;
    }
    return NULL;
}


internationalADT newInternationalList(void)
{
	return calloc(1, sizeof(struct internationalCDT));
}

static tInterNode addInter(tInterNode first, char iata [4], unsigned int landings, unsigned int takeOffs)
{
    if(first==NULL || (first->inter->takeOffs + first->inter->landings) < (landings + takeOffs) )
    {
        tInterNode resp=malloc(sizeof(*resp));
        resp->inter=malloc(sizeof(*(resp->inter)));
        strcpy(resp->inter->iata, iata);
        resp->inter->landings=landings;
        resp->inter->takeOffs=takeOffs;
        resp->next=first;
        return resp;
    }
    first->next=addInter(first->next, iata, landings, takeOffs);
    return first;
}

void fillInter(internationalADT inter, airportADT airports)
{
    tAirportNode aux;
    for(aux=airports->first; aux; aux=aux->next)
    {
        inter->first=addInter(inter->first, aux->airport->iata, aux->airport->landings, aux->airport->takeOffs);
        inter->totalMoves=(inter->totalMoves + aux->airport->landings + aux->airport->takeOffs);
    }
}

unsigned int getTotal(internationalADT interList)
{
    return interList->totalMoves;
}

void toBeginInter(internationalADT interList)
{
    interList->iterator=interList->first;
}

int hasNextInter(internationalADT interList)
{
    return interList->iterator != NULL;
}

tInter nextInter(internationalADT interList)
{
    if(hasNextInter(interList))
    {
        tInter aux=interList->iterator->inter;
        interList->iterator=interList->iterator->next;
        return aux;
    }
    return NULL;
}

void addMovements( airportADT airportList , internationalADT interList, airlineADT airlines, FILE * f, const char * year)
{
	if( airportList==NULL )
	{
		fprintf(stderr, "Error: Se intento agregar un movimiento a una lista no creada\n");
		return;
	}
	tFlight toAdd;
    tAirportNode aux;

    for ( toAdd=readFlight(f, year); toAdd; toAdd = readFlight( f, year ))
    {

        if(cmpYear(toAdd->date, year)==0)
        {
			addAirlines(airlines, toAdd->airline);
            if (toAdd -> type == -1 && toAdd -> mov == 1)
            	(airportList -> query7[0])++;
            else if ( toAdd -> type == 1 && toAdd -> mov == 1)
            	(airportList -> query7[1])++;
            else if ( toAdd -> type == -1)
            	(airportList -> query7[2])++;
            else (airportList -> query7[3])++;

            airportList->days[dateToDayOfWeek(toAdd->date)]++;

            for( aux = airportList -> first ; aux ; aux = aux -> next )
            {
				if ( strcmp( aux -> airport -> oaci , toAdd -> orOaci ) == 0 ){
                    ( aux -> airport -> takeOffs )++;
										aux->airport->destinations= addDestination( aux -> airport -> destinations, toAdd-> orOaci,-1);
                }
                if ( strcmp( aux -> airport -> oaci , toAdd -> dstOaci ) == 0 ){
                    ( aux -> airport -> landings)++;
										aux->airport->destinations= addDestination( aux -> airport -> destinations, toAdd-> orOaci,1);

                }
            }
        }
		free(toAdd);
    }
	return;
}

void query7Vector(airportADT airport, unsigned int v[4])
{
	int i;
	for (i =0; i<4; i++ )
	{
		v[i] =airport->query7[i];
	}
}
void vectorDias (airportADT airport, unsigned int v[7])
{
	int i;
	for ( i = 0; i < 7; i++)
		v[i] = airport-> days[i];
}

void freeInter(internationalADT inter){

	tInterNode aux1;
	tInterNode aux2;

	for ( aux1 = inter->first; aux1; )
	{
		free (aux1->inter);
		aux2 = aux1;
		aux1 = aux1->next;
		free (aux2);
	}
	free (inter);
}

void freeAirport ( airportADT airport)
{
	tAirportNode aux1;
	tAirportNode aux2;
	for ( aux1 = airport-> first; aux1;)
	{
		free (aux1->airport->oaci);
		free (aux1->airport->name);
		freeDestination (aux1->airport->destinations);
		aux2 = aux1;
		aux1 = aux1->next;
		free (aux2);
	}
	free (airport);
}
