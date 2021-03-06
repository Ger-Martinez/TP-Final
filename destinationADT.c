#include <stdlib.h>
#include <string.h>
#include "destinationADT.h"


struct destinationsNode
{
	tDestination destination;
	struct destinationsNode * next;
};

struct destinationCDT
{
	tDestinationNode first;
	tDestinationNode iterator;
};

destinationADT newDestinationsList(void)
{
	return calloc(1, sizeof(struct destinationCDT));
}

static tDestinationNode addDestinationRec ( tDestinationNode first , char * oaci , int mov ){
    if( first == NULL   || strcmp(first->destination->oaci, oaci) > 0)
    {
        tDestination temp = calloc( 1 , sizeof( *temp ) );
        temp -> oaci = malloc( strlen( oaci ) + 1 );
        strcpy( temp -> oaci , oaci );
        if ( mov == -1 ){
            ( temp -> takeOffs )++;
        }else if ( mov == 1 ){
            ( temp -> landings )++;
        }
        tDestinationNode dest = malloc( sizeof ( *dest ) );
        dest -> destination = temp;
        dest -> next = first;
        return dest;
    } else if ( strcmp ( first -> destination -> oaci , oaci ) == 0 ) {
        if ( mov == -1 )
            ( first -> destination -> takeOffs )++;
        else if ( mov = 1 )
            ( first -> destination -> landings )++;
        return first;
    }
    first -> next = addDestinationRec( first -> next , oaci , mov );
    return first;
}

destinationADT addDestination(destinationADT destList, char * oaci , int mov)
{
	destList->first=addDestinationRec(destList->first, oaci, mov);
	return destList;
}

void toBeginDestination(destinationADT destination)
{
    destination->iterator=destination->first;
}

int hasNextDestination(destinationADT destination)
{
    return destination->iterator != NULL;
}

tDestination nextDestination(destinationADT destination)
{
    if(hasNextDestination(destination))
    {
        tDestination aux=destination->iterator->destination;
        destination->iterator=destination->iterator->next;
        return aux;
    }
    return NULL;
}

void freeDestination( destinationADT destinations ){

	tDestinationNode aux1;
	tDestinationNode aux2;

	for ( aux1 = destinations->first;aux1;)
	{
		free(aux1->destination->oaci);
		free(aux1->destination);
		aux2 = aux1;
		aux1 = aux1->next;
		free(aux2);
	}
	free(destinations);
}
