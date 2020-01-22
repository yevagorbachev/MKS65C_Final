#include "lib/chess.h"

int main(int argc, char * argv[]) {
	struct board board = init_board();
	char setup[8][8] = {
		//a       b       c       d       e       f       g       h
		{BROOK  ,BKNIGHT,BBISHOP,BQUEEN ,BKING  ,BKNIGHT,BBISHOP,BROOK  ,}, // 8
		{BPAWN  ,BPAWN  ,BPAWN  ,BPAWN  ,BPAWN  ,BPAWN  ,BPAWN  ,BPAWN  ,}, // 7
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 6
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 5
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 4
		{'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 3
		{WPAWN  ,WPAWN  ,WPAWN  ,WPAWN  ,WPAWN  ,WPAWN  ,WPAWN  ,WPAWN  ,}, // 2
		{WROOK  ,WKNIGHT,WBISHOP,WQUEEN ,WKING  ,WKNIGHT,WBISHOP,WROOK  ,}, // 1
	};

	for (int i = 7; i >= 0; i--) {
		memcpy(&(board.state[7-i]), setup[i], 8);
	}

	printf("Starting board state:\n");
	render_board(&board);

	if (argc == 1) {
		printf("No move given\n");
	} else {
		printf("Attempting move %s\n", argv[1]);
		int move = validate_move(&board, argv[1]);
		render_board(&board);
	}
}