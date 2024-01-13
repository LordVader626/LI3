CC=gcc

CFLAGS=-Wall -g -O0 -Iinclude `pkg-config --cflags glib-2.0`

LDFLAGS=`pkg-config --libs glib-2.0` -lm -lncurses

all: main-program tests-program

main-program: src/main.o src/parser.o src/users.o src/flights.o src/passengers.o src/reservations.o src/validation.o src/handle.o src/queries.o src/utils.o src/stats.o src/user_stats.o src/hotel_stats.o src/airport_stats.o src/catalogo_user.o src/catalogo_flights.o src/catalogo_passenger.o src/catalogo_reservations.o src/catalogo_invalids.o src/batch.o src/teste.o src/interativo.o
	$(CC) $^ $(LDFLAGS) -o programa-principal


tests-program: src/parser.o src/users.o src/flights.o src/passengers.o src/reservations.o src/validation.o src/handle.o src/queries.o src/utils.o src/stats.o src/user_stats.o src/hotel_stats.o src/airport_stats.o src/catalogo_user.o src/catalogo_flights.o src/catalogo_passenger.o src/catalogo_reservations.o src/catalogo_invalids.o src/teste.o testes/src/main.o testes/src/tests.o
	$(CC) $^ $(LDFLAGS) -o programa-testes

clean:
	rm -f src/*.o