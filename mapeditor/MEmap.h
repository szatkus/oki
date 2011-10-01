#define MAP_EMPTY 0
#define MAP_WALL 1


struct
{
    struct
    {
        short int type, tile;
    } map[256][256];
    int width, height;
} level;

short int new_map;
char map[256];

void draw_tile(int x, int y, int tiletype, int tile, SDL_Surface *target);
void load_map(char *filename);
