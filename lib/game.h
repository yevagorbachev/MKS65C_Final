#include "comms.h"

#define WHITE 'w'
#define BLACK 'b'

struct board {
    char state[8][8];
    char check;
    char wcas, blcas;
};


void run(int path, char color);
void move(struct board * game, char player);
struct board init_board();
void render_board(struct board * state);