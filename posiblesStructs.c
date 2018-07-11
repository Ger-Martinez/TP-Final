typedef struct listCDT * listADT;
typedef struct airline * tAirline;
typedef struct airport * tAirport;
typedef struct destination * tDestination;
enum days {SUN=0, MON, TUE, WED, THU, FRI, SAT};

struct listCDT
{
	tAirport first;
	tAirport iterator;
	size_t totalMoves;
};

struct query6
{
	tAirline first;
	tAirline iterator;
};

struct airline
{
	char * name;
	size_t movs;
	struct airline * next;
};

struct airport
{
	char oaci[5];
	char local[4];
	char * name;
	char IATA[4];
	tInternational internat;
	size_t takeOffs;
	size_t landings;
	enum days day;
	tDestination destinations;
	struct airport * next;
};

typedef struct international
{
	int isInternat;
	tAirport nextInternat;
}tInternational;

struct destinations
{
	char * dest; /* debo poner char * por los codigos del tipo AR-XXXX sino seria char dest[5]*/
	size_t landings;
	size_t takeOffs;
	struct destinations * next;
};