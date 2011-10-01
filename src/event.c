#include "SDL.h"

#include "global.h"
#include "timer.h"
#include "objects.h"
#include "game.h"
#include "conf.h"
#include "event.h"
#include "quit.h"
#include "font.h"
#include "image.h"

void check_event()
{
    SDL_Event event;
    
    play = 1;
    show_text = 0;
    show_time = 0;
    while (play)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == left) 
                    {
                        oki->dir = DIR_LEFT;
                        start = 1;
                    }
                    if (event.key.keysym.sym == right)
                    {
                        oki->dir = DIR_RIGHT;
                        start = 1;
                    }
                    if (event.key.keysym.sym == up) camera_modifier = -10;
                    if (event.key.keysym.sym == down) camera_modifier = 10;
                    if (event.key.keysym.sym == A && oki->state != STATE_FALL &&
                        !oki->jump.frame) 
                        oki->jump.frame = 1;
                    if (event.key.keysym.sym == B && oki->run)
                    {
                        oki->speed = oki->speed*2-1;
                        oki->run = 2;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) check_quit();
                break;
                case SDL_KEYUP:
                    if (oki->dir == DIR_LEFT && event.key.keysym.sym == left) 
                        oki->dir = DIR_ZERO;
                    if (oki->dir == DIR_RIGHT && event.key.keysym.sym == right) 
                        oki->dir = DIR_ZERO;
                    if (event.key.keysym.sym == up || event.key.keysym.sym == down)
                        camera_modifier = 0;
                    if (event.key.keysym.sym == A)
                    {
                        oki->jump.frame = 0;
                        oki->state = STATE_STAY;
                    }
                    if (event.key.keysym.sym == B && oki->run == 2)
                    {
                        oki->speed = oki->speed/2+1;
                        oki->run = 1;
                        if (oki->shoot)
                        {
                            obj[oki->shoot].vis = 1;
                            obj[oki->shoot].dir = DIR_ZERO;
                            obj[oki->shoot].pos = oki->pos;
                            obj[oki->shoot].anim = oki->anim;
                            obj[oki->shoot].anim.x = 7*BLOCK_WIDTH;
                            obj[oki->shoot].anim.y = 3*BLOCK_HEIGHT;
                            obj[oki->shoot].type = OBJ_ONE_DEATH;
                            obj[oki->shoot].img = events;
                        }
                    }
                    if (event.key.keysym.sym == SDLK_p) pause_game = !pause_game;
                    #ifdef DEVEL
                    if (event.key.keysym.sym == SDLK_1) lifes--;
                    if (event.key.keysym.sym == SDLK_2) lifes++;
                    #endif
                break;
                case SDL_QUIT:
                    exit(0);
                break;
            }
        }
        if (!pause_game) timer();
        else
        {
            center_text("PAUSE", RES_Y/2);
            sprintf(temp, "score: %d", 
                    coins+lifes*100+progress*100);
            center_text(temp, RES_Y/2+LETTER_HEIGHT);
            show_screen();
        }
    }
    show_select();
}

