#include "lib/comms.h"
#include "lib/game.h"


int game_connect(char mode, char * channel) {
	int path;
	switch (mode) {
		case MODE_NET:
			path = server_connect(server_setup());
			break;
		case MODE_LOC:
			// path = pipe_setup();
			break;
		default:
			printf("Invalid connection mode\n");
			exit(1);
	}
	return path;
}

int main(int argc, char * argv[]) {
	char color = '\0';

	char name[256];
	printf("Input name (or leave empty for Anonymous) for move recording: ");
	fgets(name, 256, stdin);

	int path;
	char * myfifo = "l";
	if(argc > 1){
		path = game_connect(MODE_NET, LOCALHOST);
		read(path, &color, 1);
	} else {
	  mkfifo(myfifo, 0666);
	  path = open(myfifo, O_RDONLY);
		read(path, &color, 1);
  }

	switch(color) {
		case BLACK: color = WHITE;
			break;
		case WHITE: color = BLACK;
			break;
	}

	if(argc > 1){
		run(path, color);
	}else{
		runlocal(myfifo, color);
	}
}
