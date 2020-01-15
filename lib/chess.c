#include "chess.h"

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

int pin(struct board * board, struct moves * moves, struct coordinate origin, int * diagonal) {
    char own_color = chk_color(board, origin);
    struct coordinate last_target;
    last_target.file = 0;
    last_target.rank = 0;
    char target = 0;

    struct coordinate current;
    current.file = origin.file + diagonal[0];
    current.rank = origin.rank + diagonal[1];

    char last_color;
    char last_onboard;

    while (((last_color = chk_color(board, current)) != own_color) && (last_onboard = on_board(current))) {
        target = BOARD(current);
        if (target) {
            if (last_target.rank) {
                printf("Second piece found along diagonal at %c%c: %c\n", CHARGS(current), target);
                if ((target == WKING) | (target == BKING)) {
                    printf("Second piece is king, pin piece at %c%c\n", CHARGS(last_target));
                    PINS(last_target)[0] = diagonal[0];
                    PINS(last_target)[1] = diagonal[1];
                }
                printf("exiting pin checking\n");
                return 0;
            } 
            else {
                printf("Piece found at %c%c: %c\n", CHARGS(current), target);
                printf("Adding square %c%c to moves (to %c%c)\n", CHARGS(origin), CHARGS(current));
                add_move(moves, origin, current);
                if ((target == WKING) | (target == BKING)) {
                    printf("Piece is king, is in check\n");
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
                printf("Adding empty square %c%c to moves (to %c%c) before first piece found\n", CHARGS(origin), CHARGS(current));
                add_move(moves, origin, current);
            }
            else {
            }
        }
        // advance looking position
        current.file += diagonal[0];
        current.rank += diagonal[1];
    }
    printf("exited pin\n");

}