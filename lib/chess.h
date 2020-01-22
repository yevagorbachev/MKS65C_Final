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

#define CHARGS(pos) pos.file, pos.rank

#define SET_COLS(pos) char own_color = chk_color(board, pos); char opp = opp_color(own_color);

struct coordinate {
	char rank;
	char file;
};

struct moves {
	struct coordinate moves[8][8][17]; // for each board spot, a list of at most 16 coordinates from which that spot can be moved to
};


/* PROGRAM FLOW: //////////////////////////////////////////////////////////////
Recieve board
Calculate enemy moves for check
Calculate potentially legal moves
Alert if necessary

For an input move, determine legality (king in check after)
*/


// HELPER FUNCTIONS ///////////////////////////////////////////////////////////

struct moves * init_moves();
struct coordinate coord(char * coord);
void add_move(struct board * board, struct moves * moves, struct coordinate origin, struct coordinate destination);
int find_move(struct moves * moves, struct coordinate origin, struct coordinate destination);
char chk_color(struct board * board, struct coordinate pos);
char on_board(struct coordinate pos);
int get_moves_count(struct board * board, struct moves * moves, struct coordinate destination, char color);
char opp_color(char color);

// DEBUGGING FUNCTIONS ////////////////////////////////////////////////////////

void print_all_moves(struct moves * moves);
void print_moves_from(struct moves * moves, struct coordinate origin);

// GAME LOGIC /////////////////////////////////////////////////////////////////

int pin(
	struct board * board, struct moves * moves,
	struct coordinate origin, char * diagonal
);

int attacks (
	struct board * board, struct moves * moves,
	struct coordinate origin
);

void king_moves (struct board * board, struct moves * moves, struct coordinate origin);
void knight_moves(struct board * board, struct moves * moves, struct coordinate origin);
void pawn_moves (struct board * board, struct moves * moves, struct coordinate origin);
int generate_moves (struct board * board, struct moves * moves, char color);
int validate_move(struct board * board, char * move);
void make_move(struct board * board, char * move);