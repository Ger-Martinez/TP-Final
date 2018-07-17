#ifndef _AIRPORTADT_H_
#define _AIRPORTADT_H_

#include <stdio.h>
#include "destinationADT.h"
#include "airlineADT.h"

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
	int type;				/* 1 = Aeropuerto / 0 = N/A / -1 = Helipuerto */
	int condition;			/* 1 = PUBLICO / 0 = N/A / -1 = PRIVADO */
	int isInternational;	/* 1 = Internacional / 0 = No */
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
    char * orOaci;			/* No puede estar en blanco */
    char * dstOaci;			/* No puede estar en blanco y puede contener codigos que no sean aeropuertos conocidos */
    char * airline;
};

struct inter
{
	char iata[4];
	unsigned int takeOffs;
	unsigned int landings;
};

/* Crea una nueva lista de aeropuertos */
airportADT newAirportList(void);

/* Agrega aeropuertos ordenados por OACI */ 
void addAirports(airportADT ap , FILE * a);

void toBeginAirport(airportADT airport);
int hasNextAirport(airportADT airport);
tAirport nextAirport(airportADT airport);

/* Crea una nueva lista de aeropuertos con movimientos internacionales */
internationalADT newInternationalList(void);

/* Llena la lista de manera tal que tenga todos los datos para el query */
void fillInter(internationalADT inter, airportADT airports);

/* Retorna la cantidad total de movimientos internacionales */
unsigned int getTotal(internationalADT interList);

void toBeginInter(internationalADT interList);
int hasNextInter(internationalADT interList);
tInter nextInter(internationalADT interList);

void showMeInternational( internationalADT international );

/* Procesa los datos del archivo de vuelos y los guarda en las
** estructuras correspondientes.
*/
void addMovements(airportADT airportList, internationalADT interList, airlineADT airlines, FILE * f, const char * year);

/* Copia en v los datos necesarios para el query 7 en 
** el orden del ejemplo
*/
void query7Vector(airportADT airport, unsigned int v[4]);

/* Copia en v los movimientos por dia de semana, en la posicion
** 0 la del domingo */
void vectorDias(airportADT airport, unsigned int v[7]);

/* Libera los recursos ocupados por una lista de aeropuertos */
void freeAirport ( airportADT airport);

/* Libera los recursos ocupados por la lista de aeropuertos
** con movimientos internacionales */
void freeInter(internationalADT inter);
#endif
