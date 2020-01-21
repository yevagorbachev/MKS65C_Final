ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

objects = tester.o game.o chess.o

all: $(objects)
	$(CC) -o tester $(objects)

tester.o: tester.c lib/game.c lib/game.h lib/chess.c lib/chess.h
	$(CC) -c tester.c

game.o: lib/game.c lib/game.h lib/chess.c lib/chess.h
	$(CC) -c lib/game.c

chess.o: lib/chess.c lib/chess.h
	$(CC) -c lib/chess.c

leak:
	valgrind --leak-check=yes ./program

run:
	./tester

clean:
	rm *.o
	rm server
	rm client
