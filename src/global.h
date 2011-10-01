#include "SDL.h"

#define BLOCK_WIDTH 10
#define BLOCK_HEIGHT 10

#define RES_X 160
#define RES_Y 120

#define VERSION "0.1.5"

#define WHITE 255+255*256+255*65536

SDL_Surface *screen, *game;
SDL_Rect start_pos, camera;
Uint8 coins, limit, darkness, mask;
Sint8 lifes;
char temp[256], temp2[256], data[256];
int totalcoins, totallifes, tookcoins, tooklifes;
