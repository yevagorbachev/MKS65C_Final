#include "lib/comms.h"
#include "lib/game.h"

int main(){
    char color[3] = "\0\0";

    char name[256];
    printf("Input name (or Anonymous) for move recording: ");
    fgets(name, 256, stdin);

    char * myfifo = "l";
	mkfifo(myfifo, 0666);

    while ((color[0] != WHITE) && (color[0] != BLACK)) {
        printf("Select color (black or white): ");
        fgets(color, 3, stdin);
        printf("Selected \'%c\'\n", color[0]);
    }

    write(path, color, 1);
    run(myfifo, color[0]);
}
