#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airlineADT.h"

typedef struct airlineNode * tAirlineNode;

struct airlineNode
{
	tAirline airline;
	struct airlineNode * next;
};

struct airlineCDT
{
	tAirlineNode first;
	tAirlineNode iterator;
};

airlineADT newAirlineList(void)
{
	return calloc(1, sizeof( struct airlineCDT ) );
}

static tAirlineNode addAirlineRec ( tAirlineNode a , const char * airlineName )
{
    if ( a == NULL )
    {
        tAirline temp = malloc(sizeof(*temp));
        temp -> name = malloc(strlen( airlineName ) +1);
        strcpy( temp -> name , airlineName );
        temp -> movs = 1;
        tAirlineNode newNode = malloc(sizeof(*newNode));
        newNode -> airline = temp;
        newNode -> next = NULL;
        return newNode;
    }
    else if ( strcmp( a -> airline -> name , airlineName) == 0 )
       ( a -> airline -> movs ) ++;
    else
        a -> next = addAirlineRec ( a -> next , airlineName );
    return a;
}

void addAirlines ( airlineADT airl , const char * airline )
{
    airl -> first = addAirlineRec ( airl -> first , airline );

}

/*BORRAR*/
void showMeAirlines ( airlineADT a )
{
    tAirlineNode aux;
    for( aux = a-> first ; aux ; aux = aux -> next)
    {
        printf("Airline: %s\n", aux -> airline -> name );
        printf("Movements: %d\n", aux -> airline -> movs );
        putchar('\n');
    }
}

void toBeginAirline(airlineADT airline)
{
    airline->iterator=airline->first;
}

int hasNextAirline(airlineADT airline)
{
    return airline->iterator != NULL;
}

tAirline nextAirline(airlineADT airline)
{
    if(hasNextAirline(airline))
    {
        tAirline aux=airline->iterator->airline;
        airline->iterator=airline->iterator->next;
        return aux;
    }
    return NULL;
}
