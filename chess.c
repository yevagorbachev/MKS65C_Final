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
	//a       b       c       d       e       f       g       h  
	char setup[8][8] = {
	{BROOK  ,BKNIGHT,BBISHOP,BKING  , BQUEEN,BBISHOP,BKNIGHT,BROOK,}, // 8
	{BPAWN  , BPAWN ,BPAWN , BPAWN ,BPAWN  , BPAWN  ,BPAWN  ,BPAWN   ,}, // 7
	{'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,}, // 6
	{'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,}, // 5
	{'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,}, // 4
	{'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,'_'   ,}, // 3
	{WPAWN  , WPAWN ,WPAWN , WPAWN ,WPAWN  , WPAWN  ,WPAWN  ,WPAWN,}, // 2
	{WROOK  ,WKNIGHT,WBISHOP,WQUEEN  , WKING,WBISHOP,WKNIGHT,WROOK,}, // 1
	};


	for (int i = 7; i > -1; i--) {
		memcpy(c.board[7-i], setup[i], 8);
	}

	return c;
}

void renderBoard(struct chessboard c, char player) {
	//If the char inputted is w, render board with y perspective. (vice versa)
	if(player == 'w') {
		printf("\n Note: [!] Black is uppercase, White is lowercase");
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
	else if(player == 'b') {
		printf("\n Note: [!] Black is uppercase, White is lowercase");
		printf("\n\n    h g f e d c b a\n\n");
		int counter = 1;
		for(int x = 0; x < 8; x++) {
			printf("%d  ", counter);
			counter++;
			for(int y = 0; y < 8; y++) {
				printf("|%c",c.board[x][y]);
			}
			printf("|\n");
		}
		printf("\n\n");
	}
}

//Method used to deal with input.
int execute(char * input) {
	if(!strcmp(input, "help")) {
		printf("\n-------------------------------\n");
		printf("Commands:");
		printf("\n-------------------------------\n");
		printf("help: Lists the commands and inputs available.\n");
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
	renderBoard(c,'w');
}

int main() {
	printf("Welcome to C-hess, type \"help\" if you are new.\n");
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
