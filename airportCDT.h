#ifndef _airport_CDT_H_
#define _airport_CDT_H_

#include <stdlib.h>
#include <stdio.h>

// Flight Structs ...

typedef struct flight * TFlight;

struct flight {

    char date [ 11 ];       // Formato DD/MM/YYYY
    char time [ 6 ];        // Formato HH:MM
    int type;               // ( 1 = Internacional / 0 = N/A / -1 = Cabotaje )
    int mv;                 // ( 1 = Aterrizaje / 0 = N/A / -1 = Despegue )
    char or_oaci[ 5 ];      // No puede estar en blanco
    char dst_oaci[ 5 ];     // No puede estar en blanco y puede contener codigos que no sean aeropuertos conocidos
    char * airline;         // Nombre de la aerolinea
    struct flight *  next;  // Siguiente vuelo

};

// Airport Structs ...

typedef struct airportCDT * airportADT;

typedef struct airport * tAirport;

struct airport {

    char local_code [ 4 ];  // No puede estar vacio
    char OACI [ 5 ];        // Puede estar en blanco
    char IATA [ 4 ];        // Puede estar en blanco
    int type;               // ( 1 = Aerodromo / 2 = Helipuerto / 0 = En Blanco )
    char * name;            // debe ser <= 70 y acepta enies y acentos
    int condition;          // ( 1 = Publico / 2 = Privado / 0 = En Blanco )
    int traffic;            // ( 1 = Nacional / 2 = Internacional / 0 = En Blanco )
    TFlight flights;        // Vuelos hacia o desde este aeropuerto
    struct airport * next;  // Siguiente aeropuerto

};

// Functions ...

/* Crea una nueva lista, devuelve NULL si no hay espacio */
airportADT newList(void);

/* Llena la lista con los datos del archivo de aeropuertos, devuelve 1 si se pudo leer y guardar todo el archivo, 0 en caso contrario.
** Si retorna 0 libera toda la memoria que estaba ocupando en el proceso 
*/
int fillList(airportADT l, FILE * aeropuertos);
#endif