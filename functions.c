#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "airportsADT.h"
#include "functions.h"

#define BLOQUE 5
#define MAX_LINE 400

char * readField(char * line, char delimit, int * pos)
{
	char * resp=NULL;
	int dim=0;
	while(line[*pos]!=delimit && line[*pos])
	{
		if(dim%BLOQUE==0)
            resp=realloc(resp, dim+BLOQUE);
		resp[dim++]=line[(*pos)++];
	}
	(*pos)++;					/*para que en la proxima invocacion se saltee*/
	resp=realloc(resp, dim+1);
	resp[dim]=0;
	return resp;
}

void skipFields(char * line, char delimit, int * pos, size_t fields)
{
	for(int i=0; i<fields && line[*pos] ;i++)
	{
		while(line[*pos]!=delimit && line[*pos])
			(*pos)++;
		(*pos)++;
	}
}

tFlight readFlight(FILE * flights)
{
	char line[MAX_LINE];
	char * aux;
	if(fgets(line, MAX_LINE, flights) && line[0]!='\n')
	{
		tFlight resp=malloc(sizeof(*resp));
		int pos=0;
		//FECHA
		aux=readField(line, ';', &pos);
    strcpy(resp->date, aux);
		free(aux);

		//HORA
		aux=readField(line, ';', &pos);
		strcpy(resp->time, aux);
		free(aux);

		//CLASE
		skipFields(line, ';', &pos, 1);

		//CLASIFICACION
		aux=readField(line, ';', &pos);
		resp->type=(aux[0]=='I')?1:((aux[0]=='C')?-1:0);
		free(aux);

		//TIPO DE MOVIMIENTO
		aux=readField(line, ';', &pos);
		resp->mov=(aux[0]=='A')?1:((aux[0]=='D')?-1:0);
		free(aux);

		//ORIGEN OACI
		/* SUGERENCIA:
		 para los 3 de abajo el aux del readfield y el nuevo malloc son iguales
		 tmbn par oaci y name de readAirport
		 se puede poner simplemente resp -> * = readfield(*,*,*);
		*/
    aux=readField(line, ';', &pos);
		resp -> orOaci = malloc( strlen ( aux ) + 1 );
		strcpy(resp->orOaci, aux);
		free(aux);

		//DESTINO OACI
		aux=readField(line, ';', &pos);
    resp -> dstOaci = malloc( strlen ( aux ) + 1 );
		strcpy(resp->dstOaci, aux);
		free(aux);

		//AEROLINEA
		aux=readField(line, ';', &pos);
		resp->airline=malloc(strlen(aux)+1);
		strcpy(resp->airline, aux);
		free(aux);

		return resp;
	}
	return NULL;
}

tAirport readAirport(FILE * airports)
{
	char line[MAX_LINE];
	char * aux;
	if(fgets(line, MAX_LINE, airports) && line[0]!='\n')
	{
		tAirport resp=malloc(sizeof(*resp));
		resp -> landings = 0;
		resp -> takeOffs = 0;
		int pos=0;

		//CODIGO LOCAL
		aux=readField(line, ';', &pos);
		strcpy(resp->local, aux);
		free(aux);

		//CODIGO OACI
		aux=readField(line, ';', &pos);
		resp -> oaci = malloc( strlen ( aux ) + 1 );
		strcpy(resp->oaci, aux);
		free(aux);

		//CODIGO IATA
		aux=readField(line, ';', &pos);
		strcpy(resp->iata, aux);
		free(aux);

		//TIPO
		aux=readField(line, ';', &pos);
		resp->type=(aux[0]=='A')?1:((aux[0]=='H')?-1:0);
		free(aux);

		//NOMBRE
    aux=readField(line, ';', &pos);
		resp->name=malloc(strlen(aux)+1);
		strcpy(resp->name, aux);
		free(aux);

		//COORDENADAS LATITUD LONGITUD ELEV UOM_ELEV REF DISTANCIA_REF DIRECCION_REF

		skipFields(line, ';', &pos, 8);

		//CONDICION
		aux=readField(line, ';', &pos);
		resp->condition=(aux[1]=='U')?1:((aux[1]=='R')?-1:0);
		free(aux);

		//CONTROL REGION FIR USO
		skipFields(line, ';', &pos, 4);

		//TRAFICO
		aux=readField(line, ';', &pos);
        resp->isInternational=(aux[0]=='N')?1:((aux[0]=='I')?-1:0);
		free(aux);

    return resp;
	}
	return NULL;
}



int cmpYear(char * date1, char * year)
{
	return strcmp(date1+6, year); /*+6 para saltear DD/MM/ */
}

int dateToDayOfWeek(char * date)
{
	int d, m, y;			// Sugerencia?:
  d = m = y = 0; // Hace falta setearlos en 0 si vas a asignarle un nuevo valor abajo?
	sscanf(date, "%2d/%2d/%4d", &d, &m, &y);
	int monthDay[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	if(m<3)
		y--;
	return (y+y/4 -y/100 +y/400 +monthDay[m-1]+d)%7;
}

/* si m=1 o m=2 entonces y=y-1 sino y=y, asi los "a�os" se tomaran desde
** marzo y los dias extras de los a�os bisiestos se consideran al final
** para asi poder armar un unico vector monthDay.
*/

/* Explicaci�n de monthDay:
** distancia de dias de la semana desde el 1� de cada mes hasta el
** 1� de enero en un a�o no bisiesto.
** mesAct=(mesAnt+cantDiasAnt)%7
** Notese que en marzo se resta un dia a porque se usa el febrero del
** "a�o anterior".
** Ene:0
** Feb:(0+31)%7=3 Mar:(2+28)%7=2 Abr:(2+31)%7=5 May:(5+30)%7=0
** Jun:(0+31)%7=3 Jul:(3+30)%7=5 Ago:(5+31)%7=1 Sep:(1+31)%7=4
** Oct:(4+30)%7=6 Nov:(6+31)%7=2 Dic:(2+30)%7:4
*/

/* Explicaci�n de la f�rmula:
** +y porque 365%7=1 entonces se suma un dia por a�o que pasa.
** +y/4 porque se suma un dia extra por a�o bisiesto que pasa.
** -y/100 porque un a�o no es bisiesto si es multiplo de 100.
** +y/400 porque un a�o es bisiesto si es multiplo de 400.
** +t[m-1] porque son la cantidad de dias de la semana de
** diferencia entre el mes pedido y enero.
** +d para ver el dia de la semana dicho dia es.
** +0: probando con el 1/5/2018, que es Martes, entonces,
** (2018+504-20+5+0+1)%7=2508%7=2 como se quiere que el 0 sea domingo,
** entonces, se le "suma 0", para que este resultado sea coherente.
*/
