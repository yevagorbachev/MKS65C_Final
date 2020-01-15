#include "game.h"

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


#define BOARD(pos) board->state[pos.rank - '1'][pos.file - 'a']
#define MOVES(pos) moves->moves[pos.rank - '1'][pos.file - 'a']
#define PINS(pos) moves->pins[pos.rank - '1'][pos.file - 'a']
#define CHARGS(pos) pos.file, pos.rank
struct coordinate {
    char rank;
    char file;
};

struct moves {
    struct coordinate moves[8][8][17]; // for each board spot, a list of at most 16 coordinates from which that spot can be moved to
    char pins[8][8][2]; // for each board spot, the direction from which the piece in question is being pinned
};


/*
Initializes a moves struct with everything set to '\0'.
Allocates heap memory.
*/
struct moves * init_moves();
struct coordinate coord(char * coord);
void add_move(struct moves * moves, struct coordinate origin, struct coordinate move);

char chk_color(struct board * board, struct coordinate pos);
char on_board(struct coordinate pos);
// checks color of piece, returns 'w' or 'b'

void moves (
    struct board * board, 
    struct moves * moves, 
    struct coordinate origin, 
    int ** diagonals
    );
void king_moves (
    struct board * board, 
    struct moves * moves, 
    struct coordinate origin
);
void knight_moves(
    struct board * board, 
    struct moves * moves, 
    struct coordinate origin
);
void pawn_moves (
    struct board * board,
    struct moves * moves,
    struct coordinate origin
);
/*
Behavior identical to int pin(...)
PRECONDITION: Piece is not a pawn, knight, or king.
Uses the identity of the piece at `origin' to determine diagonals.
*/
int pins (
    struct board * board, 
    struct moves * moves, 
    struct coordinate origin
);

/* 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Pin the enemy pieces.
Arguments:
board: pointer to game board
moves: pointer to moves struct
origin: position from which you are pinning
diagonal: direction in which you are pinning
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Behavior:
if nothing interesting:
returns 0
if pin:
modifies contents of moves
returns 0
if check:
returns 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
int pin(
    struct board * board,
    struct moves * moves,
    struct coordinate origin,
    int * diagonal
);
// pin from a single diagonal
// sets the check flag and returns 1 if king in check