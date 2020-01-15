#include "lib/comms.h"
#include "lib/game.h"


int game_connect(char mode, char * channel) {
  int path;
  switch (mode) {
    case MODE_NET:
      path = client_setup(channel);
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

int main() {
  int path = game_connect(MODE_NET, LOCALHOST);
  // int path = game_connect(MODE_LOC, LOCALHOST);
  char color[3] = "\0\0";

  char name[256];
  printf("Input name (or Anonymous) for move recording: ");
  fgets(name, 256, stdin);

  while ((color[0] != WHITE) && (color[0] != BLACK)) {
      printf("Select color (black or white): ");
      fgets(color, 3, stdin);
      printf("Selected \'%c\'\n", color[0]);
  }

  write(path, color, 1);
  run(path, color[0]);
}
