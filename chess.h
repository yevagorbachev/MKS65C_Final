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

#define WPAWN 'P'
#define WROOK 'R'
#define WKNIGHT 'N'
#define WBISHOP 'B'
#define WKING 'K'
#define WQUEEN 'Q'
#define BPAWN 'p'
#define BROOK 'r'
#define BKNIGHT 'n'
#define BBISHOP 'b'
#define BKING 'k'
#define BQUEEN 'q'

struct chessboard { char board[8][8]; char whitecastle; char blackcastle;};

int isValid(char m[3]);
int movePiece(char m[3]);
void renderBoard(struct chessboard c);
struct chessboard setupBoard(struct chessboard c);
