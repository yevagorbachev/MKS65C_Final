#include "chess.h"

void move(struct board * game, char player) {
    // print board, prompt move
    render_board(game);
    char buffer[10] = "\0";
    while (1) {
        memset(buffer, 0, 10);
        printf("Move (%c): ", player);
        fgets(buffer, 10, stdin);
        if (validate_move(game, buffer)) {
            break;
        } else {
            printf("%s is an illegal move\n", buffer);
        }
    }
    // while (validate_move(game,buffer)){
    //   printf("Invalid");
    //   printf("Move (%c): ", player);
    //   fgets(buffer, 10, stdin);
    // }
    // printf("Valid");
    // switch(player) {
    //     case WHITE:
    //         game->state[buffer[0] - 'a'][buffer[1] - '1'] = 'm';
    //         // printf("server end1\n");
    //         break;
    //     case BLACK: // black to move
    //         game->state[buffer[0] - 'a'][buffer[1] - '1'] = 'M';
    //         // printf("client end1\n");
    //         break;
    // }
}

void run(int path, char color) {
    struct board game;
    switch(color) {
        case WHITE:
            game = init_board();
            while(1) {
                move(&game, WHITE);
                write(path, &game, sizeof(struct board));
                read(path, &game, sizeof(struct board));
                // printf("server end2\n");
            }
            break;
        case BLACK:
            while(read(path, &game, sizeof(struct board))) {
                move(&game, BLACK);
                write(path, &game, sizeof(struct board));
                // printf("client end2\n");
            }
            break;
    }

}

void runlocal(char * myfifo, char color) {
    struct board game;
    int fd;

    switch(color) {
        case WHITE:
            game = init_board();
            while(1) {
                //printf("white waiting\n");
                fd = open(myfifo, O_WRONLY);
                move(&game, WHITE);
                write(fd, &game, sizeof(struct board));
                close(fd);

                fd = open(myfifo, O_RDONLY);
                read(fd, &game, sizeof(struct board));
                close(fd);
                // printf("server end2\n");
            }
            break;
        case BLACK:
            while(1) {
                //printf("black waiting\n");
                fd = open(myfifo,O_RDONLY);
                read(fd, &game, sizeof(struct board));
                close(fd);

                fd = open(myfifo,O_WRONLY);
                move(&game, BLACK);
                write(fd, &game, sizeof(struct board));
                close(fd);
                // printf("client end2\n");
            }
            break;
    }

}

struct board init_board() {
    struct board board;
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
    return board;
}

void render_board(struct board * board) {
    printf("  ");
    for (int i = 0; i < 8; i++) {
        printf(" %c ", 'a' + i);
    }
    printf("\n");
    struct coordinate current;
    char piece;
    for (current.rank = '8'; current.rank >= '1'; current.rank--) {
        printf("%c ", current.rank);
        for (current.file = 'a'; current.file <= 'h'; current.file++) {
            if (piece = BOARD(current)) {
                printf("|%c|", piece);
            } else {
                printf("|_|");
            }
        }
        printf("\n");
    }
}
