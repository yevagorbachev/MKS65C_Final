#include "chess.h"

void setupBoard(struct chessboard c) {
	for(int pawns = 0; pawns < 8; pawns++) {
		c.board[7][pawns] = 'P';
		c.board[1][pawns] = 'p';
	}	
}

void renderBoard(struct chessboard c) {
	char boardStr[128];
	int counter = 0;
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			boardStr[counter] = c.board[x][y];
			counter++;
		}
		boardStr[counter] = '\n';
		counter++;
	}
	printf("\n%s\n",boardStr);
}

int main() {
	struct chessboard c;
	setupBoard(c);
	renderBoard(c);
}
