#ifndef _AIRPORTADT_H_
#define _AIRPORTADT_H_

#include <stdio.h>
#include "destinationADT.h"

typedef struct airportCDT * airportADT;
typedef struct internationalCDT * internationalADT;
typedef struct airport * tAirport;
typedef struct flight * tFlight;
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


struct flight
{
    char date [ 11 ];		/* Formato DD/MM/YYYY */
    char time [ 6 ];		/* Formato HH:MM */
    int type;				/* ( 1 = Internacional / 0 = N/A / -1 = Cabotaje ) */
    int mov;				/* ( 1 = Aterrizaje / 0 = N/A / -1 = Despegue ) */
    char * orOaci;		/* No puede estar en blanco */
    char * dstOaci;		/* No puede estar en blanco y puede contener codigos que no sean aeropuertos conocidos */
    char * airline;
};

struct inter
{
	char iata[4];
	unsigned int takeOffs;
	unsigned int landings;
};

airportADT newAirportList(void);
void addAirports(airportADT ap , FILE * a);

void toBeginAirport(airportADT airport);
int hasNextAirport(airportADT airport);
tAirport nextAirport(airportADT airport);

void showMeAirports(airportADT ap);

internationalADT newInternationalList(void);
void fillInter(internationalADT inter, airportADT airports);
unsigned int getTotal(internationalADT interList);

void toBeginInter(internationalADT interList);
int hasNextInter(internationalADT interList);
tInter nextInter(internationalADT interList);

void showMeInternational( internationalADT international );

void addMovements(airportADT airportList, internationalADT interList, airlineADT airlines, FILE * f, const char * year);

void query7Vector(airportADT airport, unsigned int v[4]);
void vectorDias(airportADT airport, unsigned int v[7]);
#endif
