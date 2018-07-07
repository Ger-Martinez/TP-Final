struct airportCDT
{
	tAirport * first;
}

airportADT newList(void)
{
	return calloc(1, sizeof(struct airportCDT));
}

static tAirport fillRec(FILE * aeropuertos, int * llena)
{

	tAirport aux;
	if(aux=readAirport(aeropuertos, llena)) //readAirport devuelve NULL si no hay mas que leer
	{
		aux->next=fillRec(aeropuertos, llena);
		if(*llena==0)	// si no se llena completa libera todo
		{
			free(aux);
			return NULL;
		}
		return aux;
	}
	*llena=1;
	return NULL;
}

int fillList(airportADT l, FILE * aeropuertos)
{
	if(l==NULL || l->first)
		return 0;
	int llena=0;
	l->first=fillRec(aeropuertos, &llena);
	return llena;
}