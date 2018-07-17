#ifndef _AIRPORTADT_H_
#define _AIRPORTADT_H_

#include <stdio.h>
#include "destinationADT.h"

typedef struct airportCDT * airportADT;
typedef struct internationalCDT * internationalADT;
typedef struct airport * tAirport;
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

void addMovements(airportADT airportList, internationalADT interList, FILE * f);
#endif