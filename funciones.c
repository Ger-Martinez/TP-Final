int cmpYear(char * date1, char * date2)
{
	return strcmp(date1+6, date2+6); /*+6 para saltear DD/MM/ */
}

int dateToDayOfWeek(char * date)
{
	int d, m, y;
	sscanf(date, "%2d/%2d/%4d", d, m, y);
	int monthDay[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; 
	if(m<3)
		y--;
	return (y+y/4 -y/100 +y/400 +monthDay[m-1]+d)%7; 
}
/* si m=1 o m=2 entonces y=y-1 sino y=y, asi los "años" se tomaran desde 
** marzo y los dias extras de los años bisiestos se consideran al final
** para asi poder armar un unico vector monthDay.
*/

/* Explicación de monthDay:
** distancia de dias de la semana desde el 1° de cada mes hasta el
** 1° de enero en un año no bisiesto.
** mesAct=(mesAnt+cantDiasAnt)%7
** Notese que en marzo se resta un dia a porque se usa el febrero del
** "año anterior".
** Ene:0
** Feb:(0+31)%7=3 Mar:(2+28)%7=2 Abr:(2+31)%7=5 May:(5+30)%7=0 
** Jun:(0+31)%7=3 Jul:(3+30)%7=5 Ago:(5+31)%7=1 Sep:(1+31)%7=4
** Oct:(4+30)%7=6 Nov:(6+31)%7=2 Dic:(2+30)%7:4
*/ 

/* Explicación de la fórmula:
** +y porque 365%7=1 entonces se suma un dia por año que pasa.
** +y/4 porque se suma un dia extra por año bisiesto que pasa.
** -y/100 porque un año no es bisiesto si es multiplo de 100.
** +y/400 porque un año es bisiesto si es multiplo de 400.
** +t[m-1] porque son la cantidad de dias de la semana de 
** diferencia entre el mes pedido y enero.
** +d para ver el dia de la semana dicho dia es.
** +0: probando con el 1/5/2018, que es Martes, entonces,
** (2018+504-20+5+0+1)%7=2508%7=2 como se quiere que el 0 se domingo,
** entonces, se le "suma 0", para que este resultado sea coherente
*/

void doQueries(FILE * aeropuertos, FILE * movimientos, short year)
{
	FILE * movsAero=fopen("movs_aeropuerto.csv", "w");
	cantMovs(movsAero, aeropuertos, movimientos, year);
	FILE * movsInter=fopen("movs_internacional.csv", "w");
	cantInter(movsInter, aeropuertos, movimientos, year);
	FILE * semanal=fopen("semanal.csv", "w");
	porDiaDeSemana(semanal, aeropuertos, movimientos, year);
	FILE * movsPorAero=fopen("aerop_detalle.csv", "w");
	movsPorAerop(movsPorAero, aeropuertos, movimientos, year);
	FILE * movsInter5=fopen("movs_internacion5.csv", "w");
	porcentajeInter(movs_internacion5, aeropuertos, movimientos, year);
	FILE * aerolinea=fopen("aerolinea.csv", "w");
	movsAerolineas(aerolinea, aeropuertos, movimientos, year);
	FILE * AterrYDespeg=fopen("movimientos.csv", "w")
	movimientosTotales(AterrYDespeg, aeropuertos, movimientos, year);
}