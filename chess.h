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

#define WPAWN 'f'
#define WROOK 'r'
#define WKNIGHT 'n'
#define WBISHOP 'b'
#define WKING 'k'
#define WQUEEN 'q'
#define BPAWN 'F'
#define BROOK 'R'
#define BKNIGHT 'N'
#define BBISHOP 'B'
#define BKING 'K'
#define BQUEEN 'Q'

struct chessboard { char board[8][8]; char whitecastle; char blackcastle;};

int isValid(char m[3]);
int movePiece(char m[3]);
void renderBoard(struct chessboard c);
struct chessboard setupBoard(struct chessboard c);
struct chessboard clearBoard(struct chessboard c);
int execute(char* input);
void playLocalGame();
