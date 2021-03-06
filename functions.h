#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include <stdio.h>
#include "airportADT.h"

/* Lee los campos de una linea del csv. Los campos vacios hacen
**  que devuelva el string vacío. El puntero pos indica desde que
** posición del string line se empieza a leer. Si line es NULL
** retorna NULL
*/
char * readField(char * line, char delimit, int *pos);

/* Saltea "fields" cantidad de campos del csv. Si fields es 0, no hace nada.
** Si line es NULL o fields es 0 no hace nada, se asume que pos es válido.
*/
void skipFields(char * line, char delimit, int * pos, unsigned int fields);

/* Almacena una linea del csv en una estructura de vuelo, retorna NULL si no hay mas lineas que leer */
tFlight readFlight(FILE * flights, const char * year);

/* Almacena una linea del csv en una estructura de aeropuerto, retorna NULL si no hay mas lineas que leer */
tAirport readAirport(FILE * airports);

/* Compara 2 strings en formato DD/MM/YYYY y retorna positivo si el a�o del primero
** es mayor que el segundo, negativo si el a�o del segundo es mayor que el primero
** y 0 (cero) si los a�os son iguales
*/
int cmpYear(const char * date1, const char * date2);

/* Convierte una fecha en formato DD/MM/YYYY en un d�a de la semana, siendo
** 0 el domingo y 6 el sabado
*/
int dateToDayOfWeek(const char * date);

#endif
