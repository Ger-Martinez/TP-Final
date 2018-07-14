#include "airportsADT.h"
#include <stdio.h>

typedef struct airlineNode * tAirlineNode;
typedef struct airportNode * tAirportNode;
typedef struct destinationsNode * tDestinationNode;

// Airports structs ...

struct internationalCDT
{
	tAirportNode first;
	tAirportNode last; /* para agregar uno nuevo mas rapido */
	tAirportNode iterator;
	size_t totalMoves;
};

struct airportNode
{
	tAirport airport;
	struct airportNode * next;
};

struct airportCDT
{
	tAirportNode first;
	tAirportNode iterator;
	unsigned int howMany;
	unsigned int totalMoves;
};

// Airport Functions...

airportADT newAirportList(void)
{
	return calloc(1, sizeof(struct airportCDT));
};

static tAirportNode addAirportRec ( tAirportNode first , tAirport a )
{
    if(first == NULL || (strcmp( first -> airport -> local , a -> local )>0))
    {
        tAirportNode temp = malloc(sizeof(*temp));
        temp -> airport = a;
        temp -> next = first;
        return temp;
    }
    /* Se asume que no hay 2 aeropuertos con mismo OACI */
    first -> next = addAirportRec( first , a );
    return first;
}

void addAirports ( airportADT ap , FILE * f )
{
    tAirport toAdd=readAirport( f );
    while(toAdd)
    {
        if(toAdd -> oaci[0])
        {
            ap -> first = addAirportRec ( ap -> first , toAdd );
            (ap -> howMany)++;  /*BORRAR JUNTO CON {}*/
        }
        toAdd = readAirport( f );
    }
    printf("( There are %d airports ) \n" , ap -> howMany ); /*BORRAR*/
}

void addMovement( airportADT airportList , tFlight flight )
{
	if( airportList==NULL )
	{
		fprintf(stderr, "Error: Se intento agregar un movimiento a una lista no creada\n");
		return 0;
	}
    tAirportNode aux;
    for(aux=airportList -> first; aux; aux=aux->next)
    {
        if (strcmp( first -> airport -> oaci , flight -> orOaci ) == 0)
            ( first -> airport -> takeOffs )++;
        else if (strcmp( first -> airport -> oaci , flight -> dstOaci ) == 0)
            (first -> airport -> landings)++;
    }
	return 0;
}

/* BORRAR */
void showMeAirpots ( airportADT ap )
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
        putchar('\n');
    }
}

// Airline structs...

struct airlineNode
{
	tAirline airline;
	struct airlineNode * next;
};

struct airlineQueryCDT
{
	tAirlineNode first;
	tAirlineNode iterator;
};

// Airline Functions ...

airlineQueryADT newAirlineList(void)
{
	return calloc(1, sizeof( struct airlineQueryCDT ) );
};

static tAirlineNode addAirlineRec ( tAirlineNode a , const char * airlineName )
{
    if ( a == NULL )
    {
        tAirline temp = malloc(sizeof(*temp));
        temp -> name = malloc(strlen( airlineName ) +1);
        strcpy( temp -> name , airlineName );
        temp -> movs = 0;
        ( temp -> movs ) ++;
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

void addAirlines ( airlineQueryADT airl , const char * airline )
{
    airl -> first = addAirlineRec ( airl -> first , airline );
    return 0;
}

/*BORRAR*/
void showMeAirlines ( airlineQueryADT a )
{
    tAirline aux;
    for(aux=a->first; aux; aux=aux->next)
    {
        printf("Airline: %s\n", first-> airline -> name );
        printf("Movements: %d\n", first-> airline -> movs );
        putchar('\n');
    }
}

// Destinations structs...

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

//Functions...

internationalADT newInternationalList(void)
{
	return calloc(1, sizeof(struct internationalCDT));
};


