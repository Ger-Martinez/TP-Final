#include <stdlib.h>

// Flight Structs ...

typedef flight * TFlight;

typedef struct flight {

    char date [ 11 ];

    char time [ 6 ];

    int type; // ( 1 = Internacional / 0 = N/A / -1 = Cabotaje )

    int mv; // ( 1 = Aterrizaje / 0 = Despegue )

    int or_oaci; // No puede estar en blanco

    int dst_oaci; // No puede estar en blanco y puede contener codigos que no sean aeropuertos conocidos

    char * belongs_to; // Nombre de la aerolinea

    char * model; // Modelo del avion

    char APC; // Letra mayuscula

    struct flight *  next; // Siguiente vuelo

} flight;

// Airport Structs ...

typedef airportCDT * airportADT;

typedef struct airportCDT {

    char local_code [ 4 ]; // No puede estar vacio

    char OACI [ 5 ]; // Puede estar en blanco

    char IATA [ 4 ]; // Puede estar en blanco

    int type; // ( 1 = Aerodromo / 0 = Helipuerto )

    char * name; // debe ser <= 70 y acepta enies y acentos

    int condition; // ( 1 = Privado / 0 = Publico )

    int traffic; // ( 1 = Internacional / 0 = Nacional )

    TFlight flights; // Vuelos hacia o desde este aeropuerto

    struct airportCDT * next; // Siguiente aeropuerto

} airportCDT;

// Functions ...

