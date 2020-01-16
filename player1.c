#include "lib/comms.h"
#include "lib/game.h"

int main(){
    char color = '\0';

	char name[256];
	printf("Input name (or leave empty for Anonymous) for move recording: ");
	fgets(name, 256, stdin);

	read(path, &color, 1);
	switch(color) {
		case BLACK: color = WHITE;
			break;
		case WHITE: color = BLACK;
			break;
	}

    char * myfifo = "l";
	mkfifo(myfifo, 0666);

	run(myfifo, color);
}
