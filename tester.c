#include "lib/chess.h"

int main() {
	struct moves * moves = init_moves();
	struct board board = init_board();
	char setup[8][8] = {
		//a       b       c       d       e       f       g       h
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 8
		{BROOK  ,'\0'   ,BBISHOP,'\0'   ,'\0'   ,BPAWN  ,'\0'   ,'\0'   ,}, // 7
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 6
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 5
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 4
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,BPAWN  ,'\0'   ,'\0'   ,'\0'   ,}, // 3
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,WPAWN  ,'\0'   ,'\0'   ,}, // 2
		{WKING  ,WBISHOP,BROOK  ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 1
	};

	for (int i = 7; i > 0; i--) {
		memcpy(&(board.state[7-i]), setup[i], 8);
	}
	pawn_moves(&board, moves, coord("f2"));
	pawn_moves(&board, moves, coord("f7"));
	print_moves_from(moves, coord("f2"));
	print_moves_from(moves, coord("f7"));
	free(moves);
}