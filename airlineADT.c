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

static tAirlineNode orderRec(tAirlineNode first, int * changed)
{
    if(first==NULL || first->next==NULL)
        return first;
    if(first->movs < first->next->movs)
    {
        tAirlineNode aux=first->next->next;
        first->next->next=first;
        tAirlineNode aux2=first->next;
        first->next=aux;
        *changed=1;
        return aux2;
    }
    first->next=orderRec(first->next, changed);
}

void orderAirlines(airlineADT airl)
{
    int changed=1;
    while(changed)
    {
        changed=0;
        airl->first=orderRec(airl->first, &changed);
    }
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

void freeAirline( airlineADT airline )
{

	tAirlineNode aux1;
	tAirlineNode aux2;

	for (aux1 = airline->first; aux1;)
	{
		free(aux1->airline->name);
		free(aux1->airline);
		aux2 = aux1;
		aux1 = aux1->next;
		free(aux2);
	}

	free(airline);
}
