#ifndef _FUNCIONES_C_

#define _FUNCIONES_C_

#include <stdio.h>

#include "airportsADT.h"



/* Lee los campos de una linea del csv. Los campos vacios hacen

**  que devuelva el string vac�o. El puntero pos indica desde que

** posici�n del string line se empieza a leer. Si line es NULL

** retorna NULL

*/

char * readField(char * line, char delimit, int *pos);



/* Saltea "fields" cantidad de campos del csv. Si fields es 0, no hace nada.

** Si line es NULL o fields es 0 no hace nada, se asume que pos es v�lido.

 */

void skipFields(char * line, char delimit, int * pos, size_t fields);



/* Almacena una linea del csv en una estructura de vueloo, retorna NULL si no hay mas lineas que leer */

tFlight readFlight(FILE * flights);



/* Almacena una linea del csv en una estructura de aeropuerto, retorna NULL si no hay mas lineas que leer */

tAirport readAirport(FILE * airports);



/* Compara 2 strings en formato DD/MM/YYYY y retorna positivo si el a�o del primero

** es mayor que el segundo, negativo si el a�o del segundo es mayor que el primero

** y 0 (cero) si los a�os son iguales

*/

int cmpYear(char * date1, char * date2);



/* Convierte una fecha en formato DD/MM/YYYY en un d�a de la semana, siendo

** 0 el domingo y 6 el sabado

*/

int dateToDayOfWeek(char * date);



#endif
