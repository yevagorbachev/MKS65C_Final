#include "game.h"

void move(struct board * game, char player) {
    // print board, prompt move
    render_board(game);
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

struct board init_board() {
    struct board game;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game.state[i][j] = '_';
        }
    }
    return game;
}

void render_board(struct board * game) {
    printf("  ");
    for (int i = 0; i < 8; i++) {
        printf(" %c ", 'a' + i);
    }
    printf("\n");
    for(int i = 0; i < 8; i++) {
        printf("%d ", 8 - i);
        for(int j = 0; j < 8; j++) {
            printf(" %c ", game->state[i][j]);
        }
        printf("\n");
    }
}
