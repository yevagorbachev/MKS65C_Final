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

struct coordinate init_coord(char * coord) {
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
    current.rank = origin.rank + diagonal[0];

    while ((chk_color(board, current) != own_color) && on_board(current)) {
        target == BOARD(current);
        // At this point, the square is empty or of an enemy color.
        if (!target) { // empty space
            if (!last_target.rank) { // piece not yet encountered
                add_move(moves, origin, current); // add to list of legal moves
            } // if piece already encountered, the only purpose is pin checking; no need to add
        } else { // enemy piece at position
            if (last_target.rank) { // piece encountered
                if ((target == WKING) | (target == BKING)) {
                    PINS(current)[0] = diagonal[0];
                    PINS(current)[1] = diagonal[1];
                }
                return 0; // optionally pin, quit always
            } else { // previous piece not encountered
                if ((target == WKING) | (target == BKING)) {
                    return 1; // their king is in check; exit loop.
                } else { // add as last target
                    last_target.file = current.file;
                    last_target.rank = current.rank;
                }
            }
        }
        // advance looking position
        current.file += diagonal[0];
        current.rank += diagonal[1];
    }

}