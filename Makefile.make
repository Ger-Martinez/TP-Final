main: queries.o functions.o destinationADT.o airportADT.o airlineADT.o main.o
	gcc queries.o functions.o destinationADT.o airportADT.o airlineADT.o main.o -o main -pedantic -std=c99 -fsanitize=address

main.o:
	gcc main.c -c -pedantic -std=c99

functions.o:
	gcc functions.c -c -pedantic -std=c99

destinationADT.o:
	gcc destinationADT.c -c -pedantic -std=c99

airportADT.o:
	gcc airportADT.c -c -pedantic -std=c99

airlineADT.o:
	gcc airlineADT.c -c -pedantic -std=c99

queries.o:
	gcc queries.c -c -pedantic -std=c99

clean:
	rm main main.o functions.o destinationADT.o airportADT.o airlineADT.o queries.o movs_aeropuerto.csv movs_internacion5.csv movs_internacional.csv movimiento.csv semanal.csv aerop_detalle.csv aerolinea.csv