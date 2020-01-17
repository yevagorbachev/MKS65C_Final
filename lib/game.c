#include "game.h"

void cmove(struct board * game, char player) {
    // print board, prompt move
    renderBoard(game,player);
    char buffer[3];
    printf("Move (%c): ", player);
    // printf("waiting");
    fgets(buffer, 3, stdin);
    // printf("buffer%c",buffer[0]);
    // scanf("%c%c", buffer, &buffer[1]);
    // printf("read move\n");

    switch(player) {
        case WHITE:
            game->state[buffer[0] - 'a'][buffer[1] - '1'] = 'm';
            // printf("server end1\n");
            break;
        case BLACK: // black to move
            game->state[buffer[0] - 'a'][buffer[1] - '1'] = 'M';
            // printf("client end1\n");
            break;
    }
}

void run(int path, char color) {
    struct board game;
    //Ncurses Variables:
    WINDOW *my_win;
    int ch;
    int height,width,startx,starty;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    height = 3;
  	width = 10;
  	starty = (LINES - height) / 2;	/* Calculating for a center placement */
  	startx = (COLS - width) / 2;	/* of the window		*/
    refresh();
    my_win = create_newwin(height,width,starty,startx);

    switch(color) {
        case WHITE:
            game = init_board();
	    game = setupBoard(game);
            while(1) {
                cmove(&game, WHITE);
                write(path, &game, sizeof(struct board));
                read(path, &game, sizeof(struct board));
                // printf("server end2\n");
            }
            break;
        case BLACK:
            while(read(path, &game, sizeof(struct board))) {
                cmove(&game, BLACK);
                write(path, &game, sizeof(struct board));
                // printf("client end2\n");
            }
            break;
    }

    while((ch = getch()) != KEY_F(1))
    	{	switch(ch)
    		{	case KEY_LEFT:
    				destroy_win(my_win);
    				my_win = create_newwin(height, width, starty,--startx);
    				break;
    			case KEY_RIGHT:
    				destroy_win(my_win);
    				my_win = create_newwin(height, width, starty,++startx);
    				break;
    			case KEY_UP:
    				destroy_win(my_win);
    				my_win = create_newwin(height, width, --starty,startx);
    				break;
    			case KEY_DOWN:
    				destroy_win(my_win);
    				my_win = create_newwin(height, width, ++starty,startx);
    				break;
    		}
    	}

    	endwin();			/* End curses mode		  */
}

struct board clearBoard(struct board c) {
	//Clears board and sets each empty position to '_';
	for(int x = 0; x < 8; x++) {
		for(int y = 0; y < 8; y++) {
			c.state[x][y] = '_';
	//		printf("|%c|",c.board[x][y]);
		}
	//	printf("\n");
	}

	return c;
}

struct board setupBoard(struct board c) {
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
		memcpy(c.state[7-i], setup[i], 8);
	}

	return c;
}

void renderBoard(struct board * c, char player) {
	//If the char inputted is w, render board with y perspective. (vice versa)
	if(player == 'w') {
		printf("\n\n\n Note: [!] Black is uppercase, White is lowercase\n\n");
		int counter = 8;
		for(int x = 7; x > -1; x--) {
			printf("%d  ", counter);
			counter--;
			for(int y = 7; y > -1; y--) {
				printf("|%c",c->state[x][y]);
			}
			printf("|\n");
		}
		printf("\n    a b c d e f g h\n\n");

	}
	else if(player == 'b') {
		printf("\n\n\n Note: [!] Black is uppercase, White is lowercase\n\n");
		int counter = 1;
		for(int x = 0; x < 8; x++) {
			printf("%d  ", counter);
			counter++;
			for(int y = 0; y < 8; y++) {
				printf("|%c",c->state[x][y]);
			}
			printf("|\n");
		}
		printf("\n    h g f e d c b a\n\n");
	}
}

struct board init_board() {
    struct board game;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game.state[i][j] = '_';
        }
    }
    return game;
}


//NCURSES (MANAGING WINDOWS)

WINDOW *create_newwin(int height, int width, int starty, int startx) {
  WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/
	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners
	 * and so an ugly remnant of window.
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window
	 * 3. rs: character to be used for the right side of the window
	 * 4. ts: character to be used for the top side of the window
	 * 5. bs: character to be used for the bottom side of the window
	 * 6. tl: character to be used for the top left corner of the window
	 * 7. tr: character to be used for the top right corner of the window
	 * 8. bl: character to be used for the bottom left corner of the window
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
