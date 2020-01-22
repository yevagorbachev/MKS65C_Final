ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

objects = client.o server.o comms.o game.o chess.o

all: $(objects)
	$(CC) -o client client.o comms.o game.o chess.o
	$(CC) -o server server.o comms.o game.o chess.o

client.o: client.c chess.o comms.o
	$(CC) -c client.c

server.o: server.c chess.o comms.o
	$(CC) -c server.c

game.o: lib/game.c lib/game.h lib/chess.c lib/chess.h
	$(CC) -c lib/game.c

chess.o: lib/chess.c lib/chess.h lib/game.h
	$(CC) -c lib/chess.c

comms.o: lib/comms.c
	$(CC) -c lib/comms.c

leak:
	valgrind --leak-check=yes ./program

run:
	./program

clean:
	rm *.o
	rm server client
