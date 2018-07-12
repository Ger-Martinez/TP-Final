#include "airportsCDT.h"

typedef struct airlineNode * tAirlineNode;
typedef struct airportNode * tAirportNode;
typedef struct destinationsNode * tDestinationNode;
typedef struct flightNode * tFlightNode;

// Flights structs...

struct flightNode
{
	tFlight flight;
	struct flightNode * next;
}

struct flightCDT
{
	tFlightNode first;
};

// Airports structs...

struct internationalCDT
{
	tAirportNode first;
	tAirportNode last; /*para agregar uno nuevo mas rapido*/
	unsigned int totalMoves;
	tAirportNode iterator;
}

struct airportNode
{
	tAirport airport;
	struct airportNode * next;
};

struct airportCDT
{
	tAirportNode first;
	tAirportNode iterator;
	unsigned int totalMoves;
};

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

airportADT newAirportList(void)
{
	return calloc(1, sizeof(struct airportCDT));
}

internationalADT newInternationalList(void)
{
	return calloc(1, sizeof(struct internationalCDT));
}

static tAirportNode addMovementRec(tAirportNode first, tAirportNode internationalFirst, tFlight flight, FILE * airportFile, int * added)
{
	int c;
	if(first==NULL || (c=strcmp(first->oaci, flight->oaci)>0))
	{
		tAirportNode aux=malloc(sizeof(*aux));
		if(aux==NULL)
		{
			fprintf(stderr, "Error: no se pudo reservar memoria en el heap para un aeropuerto\n");
			return 0;
		}
		copyAirport(aux->airport, flight->oaci, airportFile);
		/*if(aux->airport->international.isInternat)
			addInterList(aux, internationalFirst, added);
		if(!added)
		{
			fprintf(stderr, "Error: No se pudo agregar a la lista intercional\n");
			return 0;
		}*/

		aux->next=first;
		*added=1;
		return aux;
	}
	if(c==0)
	{

	}
}

int addMovement(airportADT airportList, internationalADT internationalList, tFlight flight, FILE * airportFile)
{
	if(airportList==NULL || internationalList==NULL)
	{
		fprintf(stderr, "Error: Se intento agregar un aeropuerto a una lista no creada\n");
		return 0;
	}
	int added;
	airportList->first=addMovementRec(list->first, internationalList, flight, &added);
	if(!added)
		fprintf(stderr, "Error: No se pudo agregar un aeropuerto a la lista comun\n");
	(list->totalMoves)+=added;
	return added;
}
