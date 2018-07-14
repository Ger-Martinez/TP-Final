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

void addFlights ( airlineQueryADT ar , flightADT fght , const char * year , FILE * f ){
    tFlight toAdd = readFlight( f );
    int pos = 5000;
    while ( toAdd && pos ){

        if ( cmpYear( toAdd -> date , year ) == 0){
            fght -> first = addFlightsRec ( fght -> first , toAdd , year );
            addAirlines ( ar , toAdd -> airline );
            ( fght -> howMany )++;
        }
        pos--;
        toAdd = readFlight( f );
    }
    printf("( There have been %d flights in %s ) \n" , fght -> howMany , year );
}


tAirportNode showMeFlightsRec ( tFlightNode flightN ){
    if ( flightN != NULL ){
        printf("Airline: %s \n", flightN -> flight -> airline );
        printf("Date: %s \n", flightN -> flight -> date );
		printf("Time: %s \n", flightN -> flight -> time );
		printf("Tipo: %s \n", ( flightN -> flight -> type == 1 ) ? "Internacional" : ( ( flightN -> flight -> type == -1 ) ? "Cabotaje" : ""));
		printf("Is %s \n", ( flightN -> flight -> mov ) ? "taking off" : ( ( flightN -> flight -> type == -1 ) ? "landing" : "") );
		printf("Or. Oaci: %s \n", flightN -> flight -> orOaci );
		printf("Dst. Oaci: %s \n", flightN -> flight -> dstOaci );
		printf("\n");
		showMeFlightsRec( flightN -> next );
    }
}

void showMeFlights ( flightADT fght ){
    showMeFlightsRec ( fght -> first );
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

void complete ( tAirportNode  airpN , FILE * f ){
    tAirportNode aux = airpN;
    tAirport ap = readAirport( f );
    while ( ap ){
        while ( aux ){
            if ( strcmp ( ap -> oaci , airpN -> airport -> oaci ) == 0 ){
                strcpy ( airpN -> airport -> local , ap -> local );
                airpN -> airport -> name = malloc ( sizeof ( strlen ( ap -> name ) + 1 ) );
                strcpy ( airpN -> airport -> name , ap -> name );
                strcpy ( airpN -> airport -> iata , ap -> iata );
                airpN -> airport -> type = ap -> type;
                airpN -> airport -> condition = ap -> condition;

            }
            aux = aux -> next;
        }
        aux = airpN;
        ap = readAirport( f );
    }
}

tAirportNode addAirportRec ( tAirportNode airpN , tFlight fght  ){
    if ( airpN == NULL ){
        // Primero creo el aeropuerto como estructura ...
        tAirport newAdd = malloc ( sizeof ( struct airport ) );
        newAdd -> takeOffs = 0;
        newAdd -> landings = 0;
        newAdd -> type = 0;
        newAdd -> condition = 0;
        newAdd -> name = NULL;
        newAdd -> oaci = malloc ( sizeof ( strlen ( fght -> orOaci ) + 1 ) ); // copio OACI

        strcpy ( newAdd -> oaci , fght -> orOaci );
        newAdd -> isInternational = fght -> type;  // copio isInternational
        if ( fght -> mov = 1 )
            ( newAdd -> landings ) ++;
        else
            ( newAdd -> takeOffs ) ++;
        // Ahora creo el nodo de un aeropuerto y agrego newAdd a la lista ...
        tAirportNode temp = malloc( sizeof ( struct airportNode ) );
        temp -> airport = newAdd;
        temp -> next = NULL;
        return temp;
    } else {
        int n = strcasecmp( airpN -> airport -> oaci , fght -> orOaci );
        if ( n < 0 ){
            airpN -> next = addAirportRec( airpN -> next , fght );
            return airpN;
        } else if ( n > 0) {
            // Primero creo el aeropuerto como estructura ...
            tAirport newAdd = malloc ( sizeof ( struct airport ) );
            newAdd -> takeOffs = 0;
            newAdd -> landings = 0;
            newAdd -> type = 0;
            newAdd -> condition = 0;
            newAdd -> name = NULL;
            newAdd -> oaci = malloc ( sizeof ( strlen ( fght -> orOaci ) + 1 ) ); // copio OACI
            strcpy ( newAdd -> oaci , fght -> orOaci );
            newAdd -> isInternational = fght -> type; // copio isInternational
            if ( fght -> mov = 1 )
                ( newAdd -> landings ) ++;
            else
                ( newAdd -> takeOffs ) ++;
            // Ahora creo el nodo de un aeropuerto y agrego newAdd a la lista ...
            tAirportNode temp = malloc( sizeof ( struct airportNode ) );
            temp -> airport = newAdd;
            temp -> next = airpN;
            return temp;
        } else {
            if ( fght -> mov = 1 )
                ( airpN -> airport -> landings ) ++;
            else
                ( airpN -> airport -> takeOffs ) ++;
            return airpN;
        }
        airpN -> next = addAirportRec( airpN -> next , fght );
    }
    return airpN;
}

void addAirports ( airportADT ap , FILE * a , FILE * f ){
    tFlight fght = readFlight ( f );
    int printLimit = 100;
    while ( fght && printLimit ){
        ap -> first = addAirportRec ( ap -> first , fght );
        fght = readFlight ( f );
        printLimit --;
    }
    //complete ( ap -> first , a );
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

		printf("OACI: %s\n", airpN -> airport ->oaci);
        printf("Local: %s\n", airpN-> airport ->local);
		printf("IATA: %s\n", airpN-> airport -> iata);
		printf("Tipo: %s\n", (airpN-> airport -> type==1)?"Aeródromo":((airpN-> airport ->type==-1)?"Helipuerto":""));
		printf("Nombre: %s\n", airpN-> airport ->name);
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


