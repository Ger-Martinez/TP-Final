#include "airportsADT.h"
#include <stdio.h>

typedef struct airlineNode * tAirlineNode;
typedef struct airportNode * tAirportNode;
typedef struct destinationsNode * tDestinationNode;

// Destination Structs ...

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
};

tDestinationNode addDestination ( tDestinationNode first , char * oaci , int mov ){
    if( first == NULL   )
    {
        tDestination temp = calloc( 1 , sizeof( struct destination ) );
        temp -> oaci = malloc( sizeof ( strlen( oaci ) ) + 1 );
        strcpy( temp -> oaci , oaci );
        if ( mov == -1 ){
            ( temp -> takeOffs )++;
        }else if ( mov == 1 ){
            ( temp -> landings )++;
        }
        tDestinationNode tDest = malloc( sizeof ( struct destinationsNode ) );
        tDest -> destination = temp;
        tDest -> next = first;
        return tDest;
    } else if ( strcmp ( first -> destination -> oaci , oaci ) == 0 ) {
        if ( mov == -1 )
            ( first -> destination -> takeOffs )++;
        else if ( mov = 1 )
            ( first -> destination -> landings )++;
        return first;
    }
    first -> next = addDestination( first -> next , oaci , mov );
    return first;
}

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
    int pos = 100;
    while(toAdd && pos )
    {
        if(toAdd -> oaci[0])
        {
            ap -> first = addAirportRec ( ap -> first , toAdd );
            (ap -> howMany)++;  /*BORRAR JUNTO CON {}*/
        }
        toAdd = readAirport( a );
        pos -- ;
    }
}

void addMovements( airportADT airportList , FILE * f )
{
	if( airportList==NULL )
	{
		fprintf(stderr, "Error: Se intento agregar un movimiento a una lista no creada\n");
		return 0;
	}
	tFlight toAdd = readFlight( f );
    tAirportNode aux;
    while ( toAdd )
    {
        for( aux = airportList -> first ; aux ; aux = aux -> next )
        {
            if ( strcmp( aux -> airport -> oaci , toAdd -> orOaci ) == 0 ){
                ( aux -> airport -> takeOffs )++;
                aux -> airport -> destinations -> first = addDestination( aux -> airport -> destinations -> first , toAdd -> dstOaci , -1 );
            }
            if ( strcmp( aux -> airport -> oaci , toAdd -> dstOaci ) == 0 ){
                ( aux -> airport -> landings)++;
                aux -> airport -> destinations -> first = addDestination( aux -> airport -> destinations -> first , toAdd -> orOaci , 1 );
            }
        }
        toAdd = readFlight( f );
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

void addAirlines ( airlineQueryADT airl , const char * airline )
{
    airl -> first = addAirlineRec ( airl -> first , airline );
    return 0;
}

/*BORRAR*/
void showMeAirlines ( airlineQueryADT a )
{
    tAirlineNode aux;
    for( aux = a-> first ; aux ; aux = aux -> next)
    {
        printf("Airline: %s\n", aux -> airline -> name );
        printf("Movements: %d\n", aux -> airline -> movs );
        putchar('\n');
    }
}

//Functions...

internationalADT newInternationalList(void)
{
	return calloc(1, sizeof(struct internationalCDT));
};


