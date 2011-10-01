#include "MEtext.h"
#include "../src/image.h"
#include "../src/global.h"

void show_text()
{
  SDL_BlitSurface(text_bg, NULL, screen, NULL);
  draw_text_br(text[text_mode.x][text_mode.y], 5, 5);
}
