#include <ncurses.h>
#include "comms.h"

#define WHITE 'w'
#define BLACK 'b'

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

struct board { char state[8][8]; char wcas; char blcas;};

int isValid(char m[3]);
int movePiece(char m[3]);
void renderBoard(struct board * c, char player);
struct board setupBoard(struct board c);
struct board clearBoard(struct board c);
void run(int path, char color);
void cmove(struct board * game, char player);
struct board init_board();
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
