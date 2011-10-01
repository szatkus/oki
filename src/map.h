#include "SDL.h"

#define MAP_EMPTY 0
#define MAP_WALL 1
#define MAP_CRASH 2

SDL_Surface *statics;
char *maplist[128], mapsets, mapset;


struct
{
    struct
    {
        Uint8 type, tile;
    } map[256][256];
    Uint8 width, height;
} level;

void load_map(char *filename);
