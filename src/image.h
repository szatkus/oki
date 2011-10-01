#include "SDL.h"

SDL_Surface *tileset,  *events, *monster[20], *killed, *text_bg, *man, *oke_img,
            *torch, *rock, *glass, *computer;

void cut_image(SDL_Surface *image, SDL_Surface *dest, int tile, int size, 
               int x, int y, int width, int height);
void load_images();
