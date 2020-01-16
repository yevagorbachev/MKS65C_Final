#include "chess.h"

// HELPER FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char chk_color(struct board * board, struct coordinate pos) {
    char piece = BOARD(pos);
    if (piece == '\0') {
        return '\0';
    }
    if (piece < 'Z') {
        return BLACK;
    } else {
        return WHITE;
    }
}
char on_board(struct coordinate pos) {
    return (('1' <= pos.rank) && (pos.rank <= '8') && ('a' <= pos.file) && (pos.file <= 'h'));
}
void add_move(struct moves * moves, struct coordinate origin, struct coordinate move) {
    int i = 0;
    while (MOVES(move)[i++].file != '\0'); // go to end
    MOVES(move)[i - 1] = origin;
}
void print_moves(struct moves * moves, struct coordinate move) {
    int i = 0;        
    printf("Possible coordinates to move to %c%c from:\n", CHARGS(move));
    while (MOVES(move)[i].file != '\0') {
        printf("\t%c%c\n", CHARGS(MOVES(move)[i]));
        i++;
    }
}
struct moves * init_moves() {
    return calloc(sizeof(struct moves), 1);
}
struct coordinate coord(char * coord) {
	struct coordinate square;
	square.file = coord[0];
	square.rank = coord[1];
	return square;
}

// LOGIC ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int pin(struct board * board, struct moves * moves, struct coordinate origin, int * diagonal) {
    char own_color = chk_color(board, origin);
    struct coordinate last_target;
    last_target.file = 0;
    last_target.rank = 0;
    char target = 0;

    struct coordinate current;
    current.file = origin.file + diagonal[0];
    current.rank = origin.rank + diagonal[1];

    while ((chk_color(board, current) != own_color) && on_board(current)) {
        target = BOARD(current);
        if (target) {
            if (last_target.rank) {
                // printf("Second piece found along diagonal at %c%c: %c\n", CHARGS(current), target);
                if ((target == WKING) | (target == BKING)) {
                    // printf("Second piece is king, pin piece at %c%c\n", CHARGS(last_target));
                    PINS(last_target)[0] = diagonal[0];
                    PINS(last_target)[1] = diagonal[1];
                }
                // printf("exiting pin checking\n");
                return 0;
            } 
            else {
                // printf("Piece found at %c%c: %c\n", CHARGS(current), target);
                // printf("Adding square %c%c to moves (to %c%c)\n", CHARGS(origin), CHARGS(current));
                add_move(moves, origin, current);
                if ((target == WKING) | (target == BKING)) {
                    // printf("Piece is king, is in check\n");
                    return 1;
                } 
                else {
                    last_target.file = current.file;
                    last_target.rank = current.rank;
                }
            }
        } 
        else {
            if (!last_target.rank) {
                // printf("Adding empty square %c%c to moves (to %c%c) before first piece found\n", CHARGS(origin), CHARGS(current));
                add_move(moves, origin, current);
            }
        }
        // advance looking position
        current.file += diagonal[0];
        current.rank += diagonal[1];
    }
    // printf("exited pin\n");

}

int pins(struct board * board, struct moves * moves, struct coordinate origin) {
    int diagonals[4][2] = {
        {0,0},
        {0,0},
        {0,0},
        {0,0},
    };
    char piece = BOARD(origin);
    // set relevant diagonals according to piece
    if ((piece == WROOK) | (piece == BROOK)) {
        diagonals[0][0] = 1;
        diagonals[1][1] = 1;
    }
    else if ((piece == WBISHOP) | (piece == BBISHOP)) {
        diagonals[0][0] = 1;
        diagonals[0][1] = 1;
        diagonals[1][0] = 1;
        diagonals[1][0] = -1;
    }
    else if ((piece == WQUEEN) | (piece == BQUEEN)) {
        diagonals[0][0] = 1;
        diagonals[1][1] = 1;
        diagonals[2][0] = 1;
        diagonals[2][1] = 1;
        diagonals[3][0] = 1;
        diagonals[3][0] = -1;
    }
    int checks;

    for (int i = 0; i < 4 && (diagonals[i][0] + diagonals[i][1]); i++) {
    }
}