#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

struct chessboard { char board[8][8]; char whitecastle; char blackcastle};

int isValid(char m[3]);
int movePiece(char m[3]);
