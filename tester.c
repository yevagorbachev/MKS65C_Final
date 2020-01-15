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
		{WKING  ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 1
	};
	
	for (int i = 7; i > 0; i--) {
		memcpy(&(board.state[7-i]), setup[i], 8);
	}

	struct coordinate test_positions[] = {
		coord("a1"),
		coord("a3"),
		coord("a7"),
		coord("c7"),
		coord("h2"),
	};
	char color;
	struct coordinate current;
	render_board(&board);
	int diagonal[] = {0, -1};
	pin(&board, moves, coord("a7"), diagonal);

	for (char i = '2'; i < '7'; i++) {
		struct coordinate square;
		square.file = 'a';
		square.rank = i;
		print_moves(moves, square);
	}
	
	free(moves);
}