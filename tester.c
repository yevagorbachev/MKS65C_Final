#include "lib/chess.h"

int main() {
	struct moves * moves = init_moves();
	struct board board = init_board();
	char setup[8][8] = {
		//a       b       c       d       e       f       g       h
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 8
		{BROOK  ,'\0'   ,BBISHOP,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 7
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 6
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 5
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 4
		{WBISHOP,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 3
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 2
		{WKING  ,WBISHOP,BROOK  ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 1
	};

	for (int i = 7; i > 0; i--) {
		memcpy(&(board.state[7-i]), setup[i], 8);
	}
	char color;
	struct coordinate current;
	render_board(&board);
	pins(&board, moves, coord("a7"), 1);
	pins(&board, moves, coord("c1"), 1);
	print_moves(moves);
	print_pins(moves);
	free(moves);
}