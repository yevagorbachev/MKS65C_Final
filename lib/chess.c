#include "chess.h"

// HELPER FUNCTIONS ///////////////////////////////////////////////////////////

struct moves * init_moves() {
	return calloc(sizeof(struct moves), 1);
}

struct coordinate coord(char * coord) {
	struct coordinate square;
	square.file = coord[0];
	square.rank = coord[1];
	return square;
}

void add_move(struct moves * moves, struct coordinate origin, struct coordinate move) {
	int i = 0;
	while (MOVES(move)[i++].file != '\0');
	MOVES(move)[i - 1] = origin;
}

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
	return ('1' <= pos.rank && pos.rank <= '8' && 'a' <= pos.file && pos.file <= 'h');
}

// DEBUGGING FUNCTIONS ////////////////////////////////////////////////////////

void print_moves(struct moves * moves) {
	int i = 0;
	struct coordinate current;
	printf("Possible moves (ordered by rank ascending, then file ascending)\n");
	for (current.file = 'a'; current.file <= 'h'; current.file++) {
		for (current.rank = '1'; current.rank <= '8'; current.rank++) {
			int i = 0;
			while (MOVES(current)[i].file != '\0') {
				printf("\t%c%c->%c%c\n", CHARGS(MOVES(current)[i]), CHARGS(current));
				i++;
			}
		}
	}
}

void print_pins(struct moves * moves) {
	int i = 0;
	struct coordinate current;
	printf("Locations and directions of pinned pieces (ordered by rank ascending, then file ascending)\n");
	for (current.file = 'a'; current.file <= 'h'; current.file++) {
		for (current.rank = '1'; current.rank <= '8'; current.rank++) {
			if (PINS(current)[0] != 0 || PINS(current)[1] != 0) {
				printf("\tat %c%c, along (%d, %d)\n", CHARGS(current), PINS(current)[0], PINS(current)[1]);
			}
		}
	}
}

// GAME LOGIC /////////////////////////////////////////////////////////////////

int pin (
	struct board * board, struct moves * moves,
	struct coordinate origin, char * diagonal
) {
	char own_color = chk_color(board, origin);
	struct coordinate last_target = coord("\0\0");
	char target = 0;

	struct coordinate current;
	current.file = origin.file + diagonal[0];
	current.rank = origin.rank + diagonal[1];

	while (chk_color(board, current) != own_color && on_board(current)) {
		target = BOARD(current);

		if (last_target.rank && target) {
			if (target == WKING || target == BKING) {
				PINS(last_target)[0] = diagonal[0];
				PINS(last_target)[1] = diagonal[1];
			}
			else {
				return 0;
			}
		}
		else if (!last_target.rank){
			add_move(moves, origin, current);
			if (target) {
				last_target.file = current.file;
				last_target.rank = current.rank;
			}
		}
		current.file += diagonal[0];
		current.rank += diagonal[1];
	}

}

int pins(struct board * board, struct moves * moves, struct coordinate origin) {
	char diagonals[4][2] = {
		{0,0},
		{0,0},
		{0,0},
		{0,0},
	};
	char piece = BOARD(origin);
	// set relevant diagonals according to piece
	if ((piece == WROOK) || (piece == BROOK)) {
		diagonals[0][0] = 1;
		diagonals[1][1] = 1;
	}
	else if ((piece == WBISHOP) || (piece == BBISHOP)) {
		diagonals[0][0] = 1;
		diagonals[0][1] = 1;
		diagonals[1][0] = 1;
		diagonals[1][0] = -1;
	}
	else if ((piece == WQUEEN) || (piece == BQUEEN)) {
		diagonals[0][0] = 1;
		diagonals[1][1] = 1;

		diagonals[2][0] = 1;
		diagonals[2][1] = 1;
		diagonals[3][0] = 1;
		diagonals[3][0] = -1;
	}
	int checks;
	for (int i = 0; i < 4 && (diagonals[i][0] || diagonals[i][1]); i++) {
		pin(board, moves, origin, diagonals[i]);
		char negative[] = {-diagonals[i][0], -diagonals[i][1]};
		pin(board, moves, origin, negative);
	}
}