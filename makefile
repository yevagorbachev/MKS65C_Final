ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

objects = client.o server.o comms.o game.o

all: $(objects)
	$(CC) -o client client.o comms.o game.o
	$(CC) -o server server.o comms.o game.o

client.o: client.c
	$(CC) -c client.c

server.o: server.c
	$(CC) -c server.c

game.o: lib/game.c
	$(CC) -c lib/game.c

comms.o: lib/comms.c
	$(CC) -c lib/comms.c

leak:
	valgrind --leak-check=yes ./program

run:
	./program

clean:
	rm *.o
	rm server
	rm client
