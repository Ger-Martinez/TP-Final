#ifndef _AIRPORTSADT_H_
#define _AIRPORTSADT_H_

#include <stdio.h>

typedef struct airportCDT * airportADT;
typedef struct airlineQueryCDT * airlineQueryADT;
typedef struct destinationCDT * destinationADT;
typedef struct internationalCDT * internationalADT;

typedef struct airline * tAirline;
typedef struct airport * tAirport;
typedef struct destination * tDestination;
typedef struct inter * tInter;

struct airport
{
  char * oaci;
	char local[4];
	char * name;
	char iata[4];
	int type;
	int condition;
	int isInternational;
	unsigned int takeOffs;
	unsigned int landings;
	destinationADT destinations;	/* Lista de struct destination */
};

struct destination
{
	char * oaci; /* debo poner char * por los codigos del tipo AR-XXXX sino seria char dest[5]*/
	unsigned int landings;
	unsigned int takeOffs;
};

struct airline
{
	char * name;
	unsigned int movs;
};

struct inter
{
	char iata[4];
	unsigned int takeOffs;
	unsigned int landings;
};

//Functions... (HACER DESCRIPCIONES)
airportADT newAirportList(void);
destinationADT newDestinationsList(void);
internationalADT newInternationalList(void);
void addAirports ( airportADT ap , FILE * a );
void addMovement( airportADT airportList , FILE * f );
/*BORRAR*/
void showMeAirpots ( airportADT ap );

airlineQueryADT newAirlineList(void);
void addAirlines ( airlineQueryADT airl , const char * airline );
/*BORRAR*/
void showMeAirlines ( airlineQueryADT a );
void toBeginAirport(airportADT airport);
int hasNextAirport(airportADT airport);
tAirport nextAirport(airportADT airport);
void toBeginDestination(destinationADT destination);
int hasNextDestination(destinationADT destination);
tDestination nextDestination(destinationADT destination);
void toBeginAirline(airlineQueryADT airline);
int hasNextAirline(airlineQueryADT airline);
tAirline nextAirline(airlineQueryADT airline);
#endif
