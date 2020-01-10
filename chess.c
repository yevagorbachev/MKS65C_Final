#include "chess.h"

struct chessboard setupBoard(struct chessboard c) {
	//Clears board and sets each empty position to '_';
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			c.board[x][y] = '_';
	//		printf("|%c|",c.board[x][y]);
		}	
	//	printf("\n");
	}

	//Place pieces:
	//NOTE: white is Uppercase while black is lowercase.
	//pawns
	for(int pawns = 0; pawns < 8; pawns++) {
		//white
		c.board[6][pawns] = 'p';
		//black
		c.board[1][pawns] = 'P';
	}

	//Setting up white field
	c.board[7][0] = WROOK;
	c.board[7][1] = WKNIGHT;
	c.board[7][2] = WBISHOP;
	c.board[7][3] = WQUEEN;
	c.board[7][4] = WKING;
	c.board[7][5] = WBISHOP;
	c.board[7][6] = WKNIGHT;
	c.board[7][7] = WROOK;	

	//Setting up black field
	c.board[0][0] = BROOK;
	c.board[0][1] = BKNIGHT;
	c.board[0][2] = BBISHOP;
	c.board[0][3] = BQUEEN;
	c.board[0][4] = BKING;
	c.board[0][5] = BBISHOP;
	c.board[0][6] = BKNIGHT;
	c.board[0][7] = BROOK;	


	return c;
}

void renderBoard(struct chessboard c) {
	printf("\n\n\n\n    a b c d e f g h\n\n");
	int counter = 8;
	for(int x = 0; x < 8; x++) {
		printf("%d  ", counter);
		counter--;
		for(int y = 0; y < 8; y++) {
			printf("|%c",c.board[x][y]);
		}
		printf("|\n");
	}
	printf("\n\n\n\n");
}

int main() {
	struct chessboard c;
	c = setupBoard(c);
	renderBoard(c);
}
