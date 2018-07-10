/* se puede usar una de comunes y una de internacionales (2 en total) */
struct list 
{
	struct queries * first;
	struct queries * iterator;
	size_t total; /* total mvs para comunes, total de internats para internat */
}

/*PARA QUERY 5 USAR UN VEC, dias[7]; donde cada pos contenga la cantidad de movs*/


struct query6
{
	struct airline * first;
	struct airline * iterator
}

struct airline /*para query 6, PENSAR POSIBILIDAD DE VECTOR DINAMICO INSTEAD*/
{
	char * name;
	size_t movs;
	struct airline * next;
}

/* PARA QUERY 7 HACER UN VECTOR DE DIM 4*/

struct airports
{
	char OACI[5];
	char local[4];
	char * name;
	char IATA[4];
	struct internacional internat;
	size_t desp;
	size_t aterr;
	enum dias dia; /* Ver si no es mejor hacerlo directamente sobre el vector dia*/
	struct destinos * dests;
}

struct international
{
	int isInter;
	struct queries * nextInter;
}

struct destinos
{
	char * destino;
	size_t aterr;
	size_t desp;
}