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
		{WKING  ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,'\0'   ,}, // 1
	};
	
	for (int i = 7; i > 0; i--) {
		memcpy(&(board.state[7-i]), setup[i], 8);
	}

	struct coordinate test_positions[] = {
		init_coord("a1"),
		init_coord("a3"),
		init_coord("a7"),
		init_coord("c7"),
		init_coord("h2"),
	};
	char color;
	struct coordinate current;
	for (int i = 0; i < 5; i++) {
		current = test_positions[i];
		color = chk_color(&board, current);
		if (color != '\0') {
			printf("Color at %c%c: %c\n", current.file, current.rank, color);
		} else {
			printf("No piece at %c%c\n", current.file, current.rank);
		}
	}
	render_board(&board);
	printf("\n\n");
	free(moves);
}