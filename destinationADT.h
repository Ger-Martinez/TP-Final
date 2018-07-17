#ifndef _DESTINATIONADT_H_
#define _DESTINATIONADT_H_

typedef struct destinationCDT * destinationADT;
typedef struct destination * tDestination;

typedef struct destinationsNode * tDestinationNode;

struct destination
{
	char * oaci; /* debo poner char * por los codigos del tipo AR-XXXX sino seria char dest[5]*/
	unsigned int landings;
	unsigned int takeOffs;
};

/* Crea una nueva lista de destinos */
destinationADT newDestinationsList(void);

/* Agrega un destino a la lista */
destinationADT addDestination(destinationADT destList, char * oaci , int mov);

void toBeginDestination(destinationADT destination);
int hasNextDestination(destinationADT destination);
tDestination nextDestination(destinationADT destination);

/* Libera los recursos ocupados por la lista de destinos */
void freeDestination( destinationADT destinations );
#endif
