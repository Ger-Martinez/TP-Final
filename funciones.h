/* Compara 2 strings en formato DD/MM/YYYY y retorna positivo si el año del primero
** es mayor que el segundo, negativo si el año del segundo es mayor que el primero
** y 0 (cero) si los años son iguales
*/
int cmpYear(char * date1, char * date2);
/* Convierte una fecha en formato DD/MM/YYYY en un día de la semana, siendo
** 0 el domingo y 6 el sabado
*/
int dateToDayOfWeek(char * date);
/* Realiza los queries pedidos*/
void doQueries(FILE * aeropuertos, FILE * movimientos, short year);