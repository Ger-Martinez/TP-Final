#ifndef _AIRLINEADT_H_
#define _AIRLINEADT_H_

typedef struct airlineCDT * airlineADT;
typedef struct airline * tAirline;

struct airline
{
	char * name;
	unsigned int movs;
};

/* Creo una nueva lista de aerolineas. Retorna NULL si no hay memoria */
airlineADT newAirlineList(void);

/* Agrega un movimiento a la aerolinea. Si no había un vuelo con esa
** aerolinea, agrega el nodo.
*/
void addAirlines ( airlineADT airl , const char * airline );

/* Ordena la lista de aerolineas por cantidad de movimientos */
void orderAirlines(airlineADT airl);


void toBeginAirline(airlineADT airline);
int hasNextAirline(airlineADT airline);
tAirline nextAirline(airlineADT airline);

/* Libera todos los recursos ocupados por el TAD */
void freeAirline( airlineADT airline );
#endif
