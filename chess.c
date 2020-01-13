#include "chess.h"

struct chessboard clearBoard(struct chessboard c) {
	//Clears board and sets each empty position to '_';
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			c.board[x][y] = '_';
	//		printf("|%c|",c.board[x][y]);
		}	
	//	printf("\n");
	}
	
	return c;
}

struct chessboard setupBoard(struct chessboard c) {
	c = clearBoard(c);
	//Place pieces:
	//pawns
	for(int pawns = 0; pawns < 8; pawns++) {
		//white
		c.board[1][pawns] = WPAWN;
		//black
		c.board[6][pawns] = BPAWN;
	}

	//Setting up white field
	c.board[0][0] = WROOK;
	c.board[0][1] = WKNIGHT;
	c.board[0][2] = WBISHOP;
	c.board[0][3] = WQUEEN;
	c.board[0][4] = WKING;
	c.board[0][5] = WBISHOP;
	c.board[0][6] = WKNIGHT;
	c.board[0][7] = WROOK;	

	//Setting up black field
	c.board[7][0] = BROOK;
	c.board[7][1] = BKNIGHT;
	c.board[7][2] = BBISHOP;
	c.board[7][3] = BQUEEN;
	c.board[7][4] = BKING;
	c.board[7][5] = BBISHOP;
	c.board[7][6] = BKNIGHT;
	c.board[7][7] = BROOK;	


	return c;
}

void renderBoard(struct chessboard c) {
	printf("\n Note: [!] Black is lowercase, White is uppercase");
	printf("\n\n    a b c d e f g h\n\n");
	int counter = 8;
	for(int x = 7; x > -1; x--) {
		printf("%d  ", counter);
		counter--;
		for(int y = 7; y > -1; y--) {
			printf("|%c",c.board[x][y]);
		}
		printf("|\n");
	}
	printf("\n\n");
}

//Method used to deal with input.
int execute(char * input) {
	if(!strcmp(input, "help")) {
		printf("\n-------------------------------\n");
		printf("Instructions:");
		printf("-------------------------------\n");
		printf("Welcome to C-hess. Here are the commands you can input.\n");
		printf("help: Brings this information up.\n");
		printf("localGame: Lets you play a game of chess locally with 2 players.\n");
		printf("networkGame: Lets you play online with another player. More options will be provided.\n");
		printf("exit: Exits the program.\n");
	}
	else if(!strcmp(input, "localGame")) {
		playLocalGame();
	}
	else if(!strcmp(input, "networkGame")) {
		printf("Sorry this hasn't been implemented yet!\n");
	}
	else if(!strcmp(input, "exit")) {
		printf("Exited the program!\n");
		return 1;
	}
	else {
		printf("Command is not valid!\n");
	}
	return 0;
}

void playLocalGame() {
	struct chessboard c;
	c = setupBoard(c);
	renderBoard(c);
}

int main() {
	while(1) {
		printf("Input command: ");
		char input[1024];
		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';
		if(execute(input)) {
			break;
		}
	}
}
