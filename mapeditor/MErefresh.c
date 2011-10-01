#include "SDL.h"

#include "global.h"
#include "font.h"
#include "image.h"
#include "okiGL.h"
#include "MErefresh.h"
#include "MEevent.h"
#include "MEmap.h"
#include "MEtext.h"
#include "MEmove.h"

void refresh_static()
{
    SDL_Rect rect;
    
    rect.x = 0;
    rect.y = 0;
    rect.w = game->w;
    rect.h = game->h;
    if (mode) SDL_FillRect(game, &rect, 255+255*256+255*65536);
    else SDL_FillRect(game, &rect, 255+255*65536);
    show_map();
}

void refresh()
{
    SDL_Rect rect;
    int i;
    
    SDL_BlitSurface(game, &camera, screen, NULL);
    if (type != 3)
    {
        draw_tile(cursor.x, cursor.y, type, tile, screen);
        cut_image(events, screen, 21, 8, cursor.x*BLOCK_WIDTH, 
                  cursor.y*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);
    }
    else
      draw_tile(cursor.x, cursor.y, type, tile, screen);
    if (list)
    {
      for (i=0;i<=63;i++)
      {
        if (i != tile)
          draw_tile(i-(i/8)*8, i/8, type, i, screen);
        else
          draw_tile(i-(i/8)*8, i/8, 1, 63, screen);
      }
    }
    if (!text_mode.work) 
    {
        sprintf(temp, "%d/%d, %d/%d", camera.x/BLOCK_WIDTH+cursor.x, 
                level.width, camera.y/BLOCK_HEIGHT+cursor.y, level.height);
        draw_text(temp, 0, 0);
        switch (type)
        {
          case 0: draw_text("background", RES_X-66, 0); break;
          case 1: draw_text("still", RES_X-40, 0); break;
          case 2: draw_text("crush", RES_X-40, 0); break;
          case 3: draw_text("event", RES_X-40, 0); break;
        }
        sprintf(temp, "%d", tile+1);
        draw_text(temp, RES_X-10, 0);
    } else show_text();
    if (show_quit)
    {
        center_text("save map? (y)es/(n)o/(c)ancel", RES_Y/2);
        show_screen();
    }
    show_screen();
}
