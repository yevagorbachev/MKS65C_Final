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

void add_move(struct moves * moves, struct coordinate origin, struct coordinate destination) {
	int i = 0;
	while (MOVES(destination)[i++].file != '\0');
	MOVES(destination)[i - 1] = origin;
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

int get_moves_count(struct board * board, struct moves * moves, struct coordinate destination, char color) {
	int c = 0;
	for (int i = 0; MOVES(destination)[i].file != '\0'; i++) {
		c += chk_color(board, MOVES(destination)[i]) == color;
	}
	return c;
}

char opp_color(char color) {
	switch(color) {
		case BLACK:
			return WHITE;
			break;
		case WHITE:
			return BLACK;
			break;
	}
}

char pinfilter(char * delta, char * pin) {
	if (!pin[0] && !pin[1]) {
		return 1;
	} else {
		return (delta[0] == pin[0] && delta[1] == pin[1]) || (delta[0] == -pin[0] && delta[1] == -pin[1]);
	}
}
// DEBUGGING FUNCTIONS ////////////////////////////////////////////////////////

void print_all_moves(struct moves * moves) {
	int i = 0;
	struct coordinate current;
	printf("Possible moves (ordered by rank ascending, then file ascending)\n");
	for (current.file = 'a'; current.file <= 'h'; current.file++) {
		for (current.rank = '1'; current.rank <= '8'; current.rank++) {
			for (int i = 0; MOVES(current)[i].file; i++) {
				printf("\t%c%c->%c%c\n", CHARGS(MOVES(current)[i]), CHARGS(current));
			}
		}
	}
}

void print_moves_from(struct moves * moves, struct coordinate origin) {
	int i = 0;
	struct coordinate current;
	printf("Possible moves from %c%c:\n", CHARGS(origin));
	for (current.file = 'a'; current.file <= 'h'; current.file++) {
		for (current.rank = '1'; current.rank <= '8'; current.rank++) {
			for (int i = 0; MOVES(current)[i].file; i++) {
				if (MOVES(current)[i].file == origin.file && MOVES(current)[i].rank == origin.rank) {
					printf("\t%c%c\n",CHARGS(current));
				}
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
	struct coordinate last_target = coord("\0");
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

int attacks(struct board * board, struct moves * moves, struct coordinate origin) {

	char diagonals[4][2] = {
		{0,0},
		{0,0},
		{0,0},
		{0,0},
	};
	char piece = BOARD(origin);
	// set relevant diagonals according to piece
	if (piece == WROOK || piece == BROOK) {
		diagonals[0][0] = 1;
		diagonals[1][1] = 1;
	}
	else if (piece == WBISHOP || piece == BBISHOP) {
		diagonals[0][0] = 1;
		diagonals[0][1] = 1;
		diagonals[1][0] = 1;
		diagonals[1][0] = -1;
	}
	else if (piece == WQUEEN || piece == BQUEEN) {
		diagonals[0][0] = 1;
		diagonals[1][1] = 1;

		diagonals[2][0] = 1;
		diagonals[2][1] = 1;
		diagonals[3][0] = 1;
		diagonals[3][0] = -1;
	}
	// else { // piece is a king, knight, or pawn
	// 	SET_COLS(origin)
	// 	if (piece == WKING || piece == BKING) {
	// 		king_moves(board, moves, origin);
	// 	} else if (piece == WKNIGHT || piece == WKNIGHT) {
	// 		if (!PINS(origin)[0] && !PINS(origin)[1]) {
	// 			knight_moves(board, moves, origin);
	// 		}
	// 	} else if (piece == WPAWN || piece == BPAWN) {

	// 	}
	// 	return 0;
	// }
	for (int i = 0; i < 4 && (diagonals[i][0] || diagonals[i][1]); i++) {
		if (pinfilter(diagonals[i], PINS(origin))) {
			pin(board, moves, origin, diagonals[i]);
			char negative[] = {-diagonals[i][0], -diagonals[i][1]};
			pin(board, moves, origin, negative);
		}
	}
}

void king_moves(struct board * board, struct moves * moves, struct coordinate king_pos) {

	SET_COLS(king_pos)

	char deltas[8][2] = {
		{-1,-1},
		{-1,0},
		{-1,1},
		{0,-1},
		{0,1},
		{1,-1},
		{1,0},
		{1,1}
	};

	for (int i = 0; i < 8; i++) {

		struct coordinate new_move = king_pos;
		new_move.file += deltas[i][0];
		new_move.rank += deltas[i][1];

		if (on_board(new_move) &&
			get_moves_count(board, moves, new_move, opp) == 0 &&
			chk_color(board, new_move) != own_color)
		{
			add_move(moves, king_pos, new_move);
		}
	}
}

void pawn_moves(struct board * board, struct moves * moves, struct coordinate pawn_pos) {
	SET_COLS(pawn_pos)



}

void knight_moves(struct board * board, struct moves * moves, struct coordinate knight_pos) {
	SET_COLS(knight_pos)


}

void generate_moves(struct board * board, struct moves * moves, char color) {
	char king;
	struct coordinate king_pos;
	switch(color) {
		case WHITE:
			king = WKING;
			break;
		case BLACK:
			king = BKING;
			break;
	}

	// search for king position, simultaneously calculate attacks
	struct coordinate current;
	char opp = opp_color(color);
	for (current.file = 'a'; current.file <= 'h'; current.file++) {
		for (current.rank = '1'; current.rank <= '8'; current.rank++) {
			if (BOARD(current) == king) {
				king_pos = current;
			} else if (chk_color(board, current) == opp) {
				attacks(board, moves, current);
			}
		}
	}


}