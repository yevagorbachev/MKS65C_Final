#include "chess.h"

void move(struct board * game, char player) {
    // print board, prompt move
    render_board(game);
    char buffer[3];
    printf("Move (%c): ", player);
    scanf("%c%c", buffer, &buffer[1]);
    
    switch(player) {
        case WHITE:
            game->state[buffer[0] - 'a'][buffer[1] - '1'] = 'm';
            break;
        case BLACK: // black to move
            game->state[buffer[0] - 'a'][buffer[1] - '1'] = 'M';
            break;
    }
}

void run(int path, char color) {
    struct board game;
    switch(color) {
        case WHITE:
            game = init_board();
            while(1) {
                move(&game, WHITE);
                write(path, &game, sizeof(struct board));
                read(path, &game,  sizeof(struct board));
            }
            break;
        case BLACK:
            while(read(path, &game, sizeof(struct board))) {
                move(&game, BLACK);
                write(path, &game, sizeof(struct board));
            }
            break;
    }

}

struct board init_board() {
    struct board game;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game.state[i][j] = '\0';
        }
    }
    return game;
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
                printf(" %c ", piece);
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}