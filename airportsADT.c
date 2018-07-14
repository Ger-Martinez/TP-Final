#include "airportsADT.h"
#include <stdio.h>

typedef struct airlineNode * tAirlineNode;
typedef struct airportNode * tAirportNode;
typedef struct destinationsNode * tDestinationNode;
typedef struct flightNode * tFlightNode;

// Flights structs...

struct flightNode
{
	tFlight flight;
	struct flightNode * next;
};

struct flightCDT // First List ...
{
    unsigned int howMany;
	tFlightNode first;
};

// Flight Functions ...

flightADT newFlightList(void)
{
	return calloc(1, sizeof(struct flightCDT));
};

tFlightNode addFlightsRec ( tFlightNode fghtN , tFlight toAdd , const char * year ){
    if ( fghtN == NULL ){
        tFlightNode temp = malloc( sizeof ( struct flightNode ) );
        temp -> flight = toAdd;
        temp -> next = NULL;
        return temp;
    } else {
        fghtN -> next = addFlightsRec( fghtN -> next , toAdd , year );
        return fghtN;
    }
}

void addFlights ( airportADT ap , airlineQueryADT ar , flightADT fght , const char * year , FILE * f ){
    tFlight toAdd = readFlight( f );
    int pos = 100;
    while ( toAdd && pos ){

        if ( cmpYear( toAdd -> date , year ) == 0){
            fght -> first = addFlightsRec ( fght -> first , toAdd , year );
            addMovement ( ap , toAdd );
            addAirlines ( ar , toAdd -> airline );
            ( fght -> howMany )++;
        }
        pos--;
        toAdd = readFlight( f );
    }
    printf("( There have been %d flights in %s ) \n" , fght -> howMany , year );
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

tAirportNode addAirportRec ( tAirportNode airpN , tAirport a ){

    if ( airpN == NULL ){
        tAirportNode temp = malloc( sizeof ( struct airportNode ) );
        temp -> airport = a;
        temp -> next = NULL;
        return temp;
    } else {
        int n = strcasecmp( airpN -> airport -> local , a -> local );
        if ( n < 0 ){
            airpN -> next = addAirportRec( airpN , a );
            return airpN;
        } else {
            tAirportNode temp = malloc( sizeof ( struct airportNode ) );
            temp -> airport = a;
            temp -> next = airpN;
            return temp;
        }
        airpN -> next = addAirportRec( airpN -> next , a );
    }
}

void addAirports ( airportADT ap , FILE * f ){
    tAirport toAdd = readAirport( f );
    while ( toAdd ){
        if ( strlen( toAdd -> oaci ) != 0 ){
            ap -> first = addAirportRec ( ap -> first , toAdd );
            ( ap -> howMany )++;
        }
        toAdd = readAirport( f );
    }
    printf("( There are %d airports ) \n" , ap -> howMany );
}

static void addMovementRec( tAirportNode airpN , tFlight flight ){
    if ( airpN != NULL ){
        if ( strcasecmp( airpN -> airport -> oaci , flight -> orOaci ) == 0 )
            ( airpN -> airport -> takeOffs )++;
        else if ( strcasecmp( airpN -> airport -> oaci , flight -> dstOaci ) == 0 )
            ( airpN -> airport -> landings )++;
        addMovementRec( airpN -> next , flight );
    }
}

void addMovement( airportADT airportList , tFlight flight )
{
	if( airportList==NULL )
	{
		fprintf(stderr, "Error: Se intento agregar un movimiento a una lista no creada\n");
		return 0;
	}
	addMovementRec( airportList -> first , flight );
	return 0;
}

tAirportNode showMeAirpotsRec ( tAirportNode airpN ){
    if ( airpN != NULL ){
        printf("Local: %s\n", airpN-> airport ->local);
		printf("OACI: %s\n", airpN-> airport ->oaci);
		printf("IATA: %s\n", airpN-> airport -> iata);
		printf("Tipo: %s\n", (airpN-> airport -> type==1)?"Aeródromo":((airpN-> airport ->type==-1)?"Helipuerto":""));
		printf("Nombre: %s\n", airpN-> airport ->name);
		printf("Aterrizajes: %d\n", airpN -> airport -> landings );
		printf("Despegues: %d\n", airpN-> airport -> takeOffs);
		printf("Condicion: %s\n", (airpN-> airport ->condition==1)?"Publico":((airpN-> airport ->condition==-1)?"Privado":""));
		printf("Trafico: %s\n", (airpN-> airport ->isInternational==1)?"Nacional":((airpN-> airport ->isInternational==-1)?"Internacional":""));
		printf("\n");
		showMeAirpotsRec( airpN -> next );
    }
}

void showMeAirpots ( airportADT ap ){
    showMeAirpotsRec ( ap -> first );
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

tAirlineNode addAirlineRec ( tAirlineNode a , const char * airlineName ){
    if ( a == NULL ){
        tAirline temp = malloc ( sizeof ( struct airline ) );
        temp -> name = malloc ( strlen( airlineName ) + 1 );
        temp -> movs = 0;
        if ( strcmp ( airlineName , "N/A") == 0 ){
            strcpy( temp -> name , "N/A" );
        }else{
            strcpy( temp -> name , airlineName );
        }
        ( temp -> movs ) ++;
        tAirlineNode newNode = malloc ( sizeof ( struct airlineNode ) );
        newNode -> airline = temp;
        newNode -> next = NULL;
        return newNode;
    } else if ( strcasecmp( a -> airline -> name , airlineName ) == 0 ) {
       ( a -> airline -> movs ) ++;
    } else {
        a -> next = addAirlineRec ( a -> next , airlineName );
    }
    return a;
}

void addAirlines ( airlineQueryADT airl , const char * airline ){

    airl -> first = addAirlineRec ( airl -> first , airline );
    return 0;
}

tAirportNode showMeAirlinesRec ( tAirlineNode airN ){
    if ( airN != NULL ){
        printf("Airline: %s\n", airN-> airline -> name );
		printf("Movements: %d\n", airN-> airline -> movs );
		printf("\n");
		showMeAirlinesRec( airN -> next );
    }
}

void showMeAirlines ( airlineQueryADT a ){
    showMeAirlinesRec ( a -> first );
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


