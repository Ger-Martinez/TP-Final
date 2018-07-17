#ifndef _AIRLINEADT_H_
#define _AIRLINEADT_H_

typedef struct airlineCDT * airlineADT;
typedef struct airline * tAirline;

struct airline
{
	char * name;
	unsigned int movs;
};

airlineADT newAirlineList(void);
void addAirlines ( airlineADT airl , const char * airline );

void toBeginAirline(airlineADT airline);
int hasNextAirline(airlineADT airline);
tAirline nextAirline(airlineADT airline);

void freeAirline( airlineADT airline );
#endif
