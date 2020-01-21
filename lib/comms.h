#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define PORT "2800"
#define LOCALHOST "127.0.0.1"
#define PIPE_DEFAULT "chesscomm"
#define MODE_NET 'n'
#define MODE_LOC 'l'

void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server);
char * pipe_setup();
