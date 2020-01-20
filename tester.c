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
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 3
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 2
		{WKING  ,WBISHOP,BROOK  ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 1
	};

	for (int i = 7; i > 0; i--) {
		memcpy(&(board.state[7-i]), setup[i], 8);
	}
	char color;
	struct coordinate current;
	render_board(&board);
	attacks(&board, moves, coord("a7"));
	attacks(&board, moves, coord("c1"));
	attacks(&board, moves, coord("c7"));
	attacks(&board, moves, coord("b1"));
	// printf("%d black pieces can move to a1\n", get_moves_count(&board, moves, coord("a1"), BLACK));
	king_moves(&board, moves, coord("a1"));
	// print_moves_from(moves, coord("a1"));
	print_pins(moves);
	print_moves_from(moves, coord("b1"));
	// print_all_moves(moves);
	free(moves);
}