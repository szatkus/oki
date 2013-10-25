#include "SDL.h"

#include "global.h"
#include "font.h"
#include "objects.h"
#include "game.h"
#include "event.h"

void check_quit()
{
    SDL_Event event;
    
    pause_game = 1;
    center_text("press escape for quit", RES_Y/2-20);
    show_screen();
    while (event.type != SDL_KEYDOWN)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)) 
        {
            select_level = 0;
            play = 0;
        }
    }
    pause_game = 0;
}

