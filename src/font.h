#include "SDL.h"

#define LETTER_WIDTH 5
#define LETTER_HEIGHT 7

SDL_Surface *font;

void draw_text(char *text, Uint16 x, Uint16 y);
void draw_text_br(char *text, Uint16 x, Uint16 y);
void center_text(char *text, Uint16 y);
