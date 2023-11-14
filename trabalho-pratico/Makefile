CC=gcc

CFLAGS=-Wall -Iinclude `pkg-config --cflags glib-2.0`

LDFLAGS=`pkg-config --libs glib-2.0` -lm

main-program: src/main.o src/parser.o src/users.o src/flights.o src/passengers.o src/reservations.o src/validation.o src/handle.o src/queries.o src/utils.o src/stats.o src/user_stats.o src/flight_stats.o src/hotel_stats.o src/airport_stats.o
	$(CC) $^ $(LDFLAGS) -o programa-principal

clean:
	rm -f programa-principal src/main.o src/parser.o src/users.o src/flights.o src/passengers.o src/reservations.o src/validation.o src/handle.o src/queries.o src/utils.o src/stats.o src/user_stats.o src/flight_stats.o src/hotel_stats.o src/airport_stats.o