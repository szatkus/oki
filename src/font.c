#include "font.h"
#include "global.h"
#include "image.h"

void draw_text(char *text, Uint16 x, Uint16 y)
{
    SDL_Rect rect, rect2;
    Uint8 pos;
    
    pos = 0;
    while(text[pos] != 0)
    {
        cut_image(font, screen, text[pos], 16, x+pos*LETTER_WIDTH, y,
                  LETTER_WIDTH, LETTER_HEIGHT);
        pos++;
    }
}

void draw_text_br(char *text, Uint16 x, Uint16 y)
{
    SDL_Rect rect, rect2;
    Uint8 pos, i, line;
    
    pos = 0;
    i = 0;
    line = 0;
    while(text[pos] != 0)
    {
        if (x+i*LETTER_WIDTH+10 > RES_X)
        {
            i = 0;
            line++;
        }
        cut_image(font, screen, text[pos], 16, x+i*LETTER_WIDTH, 
                  y+line*LETTER_HEIGHT, LETTER_WIDTH, LETTER_HEIGHT);
        i++;
        pos++;
    }
}

void center_text(char *text, Uint16 y)
{
    SDL_Rect rect, rect2;
    Uint8 pos;
    Uint16 x;
    
    pos = 0;
    x = (RES_X-(strlen(text)*LETTER_WIDTH))/2;
    draw_text(text, x, y);
}
