#include "SDL.h"

struct
{
    char frames, vis, loop, delay, wait;
    SDL_Surface *img;
    SDL_Rect anim, pos;
} anim[256];

char last_anim;
