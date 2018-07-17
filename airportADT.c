#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airportsADT.h"
#include "destinationADT.h"
#include "functions.h"

static tAirportNode addAirportRec (tAirportNode first , tAirport newAp);
static tInterNode addInter(tInterNode first, char iata [4], unsigned int landings, unsigned int takeOffs);

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
};

struct interNode
{
    tInter inter;
    struct interNode * next;
};

struct internationalCDT
{
	tInterNode first;
	unsigned int totalMoves;
};


airportADT newAirportList(void)
{
	return calloc(1, sizeof(struct airportCDT));
};

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
    int pos = 100; /*BORRAR*/
    while(toAdd && pos )
    {
        if(toAdd -> oaci[0])
        {
            ap -> first = addAirportRec ( ap -> first , toAdd );
        }
        toAdd = readAirport( a );
        pos -- ;
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
        airport->iterator=airport->iterator->next;
        return airport->iterator->airport;
    }
    return NULL;
}

void showMeAirports ( airportADT ap )
{
    tAirportNode aux;
    for(aux=ap->first; aux; aux=aux->next)
    {
        printf("Local: %s\n", aux-> airport ->local);
        printf("OACI: %s\n", aux-> airport ->oaci);
        printf("IATA: %s\n", aux-> airport -> iata);
        printf("Tipo: %s\n", (aux-> airport -> type==1)?"Aeródromo":((aux-> airport ->type==-1)?"Helipuerto":""));
        printf("Nombre: %s\n", aux-> airport ->name);
        printf("Aterrizajes: %d\n", aux -> airport -> landings );
        printf("Despegues: %d\n", aux-> airport -> takeOffs);
        printf("Condicion: %s\n", (aux-> airport ->condition==1)?"Publico":((aux-> airport ->condition==-1)?"Privado":""));
        printf("Trafico: %s\n", (aux-> airport ->isInternational==1)?"Nacional":((aux-> airport ->isInternational==-1)?"Internacional":""));
        printf("Destinations: \n");
        tDestinationNode dst;
        for ( dst = aux -> airport -> destinations -> first ; dst ; dst = dst -> next ){
            printf("    -OACI: %s\n", dst -> destination -> oaci);
            printf("    -Aterrizajes: %d\n", dst -> destination -> landings );
            printf("    -Despegues: %d\n", dst -> destination -> takeOffs);
        }
        putchar('\n');
    }
}

internationalADT newInternationalList(void)
{
	return calloc(1, sizeof(struct internationalCDT));
};

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
        interList->iterator=interList->iterator->next;
        return interList->iterator->interList;
    }
    return NULL;
}

void showMeInternational( internationalADT international )
{
    tInterNode aux;
    for( aux = international -> first ; aux ; aux = aux -> next)
    {
        printf("IATA: %s\n", aux -> inter -> iata );
        printf("Landings: %d\n", aux -> inter -> landings );
        printf("Take Offs: %d\n", aux -> inter -> takeOffs );
        putchar('\n');
    }
}

void addMovements( airportADT airportList , internationalADT interList, FILE * f )
{
	if( airportList==NULL )
	{
		fprintf(stderr, "Error: Se intento agregar un movimiento a una lista no creada\n");
		return;
	}
	tFlight toAdd;
    tAirportNode aux;

    for ( toAdd=readFlight(f); toAdd; toAdd = readFlight( f ))
    {
        for( aux = airportList -> first ; aux ; aux = aux -> next )
        {
            if ( strcmp( aux -> airport -> oaci , toAdd -> orOaci ) == 0 ){
                ( aux -> airport -> takeOffs )++;
                aux -> airport -> destinations= addDestination( aux -> airport -> destinations, toAdd -> dstOaci , -1 );
                (airportList -> days [dateToDayOfWeek(toAdd->date)])++;
            }
            if ( strcmp( aux -> airport -> oaci , toAdd -> dstOaci ) == 0 ){
                ( aux -> airport -> landings)++;
                aux -> airport -> destinations = addDestination( aux -> airport -> destinations, toAdd -> orOaci , 1 );
                (airportList -> days [dateToDayOfWeek(toAdd->date)])++;
            }
        }
    }
	return;
}