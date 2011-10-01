#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_image.h"

#include "global.h"
#include "objects.h"
#include "timer.h"
#include "game.h"
#include "data.h"
#include "conf.h"
#include "sound.h"
#include "save.h"
#include "event.h"
#include "font.h"
#include "quit.h"

SDL_Surface *background;
struct
{
    char name[256];
    short int x, y;
} map[16];

void show_select()
{
    SDL_Rect rect;
    
    rect.x = 0;
    rect.y = 0;
    rect.w = RES_X;
    rect.h = RES_Y;
    SDL_FillRect(screen, &rect, WHITE);
    SDL_BlitSurface(background, &rect, screen, &rect);
    oki->anim.x = 0;
    oki->anim.y = 0;
    SDL_BlitSurface(oki->img, &oki->anim, screen, &oki->pos);
    show_screen();
}

void load_mapset(char *name)
{
    FILE *file;
    
    sprintf(temp, "maps/%s/index", name);
    file = fopen(getdata(temp), "r");
    fgets(temp, 256, file);
    temp[strlen(temp)-1] = 0;
    sprintf(temp2, "maps/%s/%s", name, temp);
    background = IMG_Load(getdata(temp2));
    maps = 0;
    while (fgets(temp, 256, file) != NULL)
    {
        temp[strlen(temp)-1] = 0;
        if (strlen(data)) sprintf(map[maps].name, "%s/maps/%s/%s", data, name, 
                                  temp);
        else sprintf(map[maps].name, "maps/%s/%s", name, temp);
        fgets(temp, 256, file);
        temp[strlen(temp)-1] = 0;
        map[maps].x = atoi(temp);
        fgets(temp, 256, file);
        temp[strlen(temp)-1] = 0;
        map[maps].y = atoi(temp);
        maps++;
    }
    fclose(file);
    load_game();
}

void start_game(char *name)
{
    SDL_Event event;
    SDL_Rect rect;
    
    select_level = 1;
    progress = 0;
    mask = 0;
    oki->vis = 1;
    oki->state = STATE_STAY;
    oki->dir = DIR_ZERO;
    oki->speed = 3;
    oki->AI = 0;
    oki->type = 0;
    oki->mass = 6;
    oki->strength = 0;
    oki->blink= 0;
    oki->damage = 0;
    oki->HP = 0;
    oki->shoot = 0;
    oki->jump.power = 5;
    oki->jump.frame = 0;
    oki->jump.time = 5;
    coins = 0;
    lifes = 2;
    die = 0;
    pause_game = 0;
    darkness = 1;
    load_mapset(name);
    load_game();
    pos = progress;
    oki->pos.x = map[pos].x;
    oki->pos.y = map[pos].y;
    show_select();
    while (select_level)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == A ||
                    event.key.keysym.sym == SDLK_RETURN ||
                    event.key.keysym.sym == SDLK_KP_ENTER)
                {
                    play_snd(click);
                    load_map(map[pos].name);
                    show_map();
                    check_event();
                    if (lifes < 0) 
                    {
                        play = 0;
                        select_level = 0;
                    }
                    if (progress == maps)
                    {
                        rect.x = 0;
                        rect.y = 0;
                        rect.w = RES_X;
                        rect.h = RES_Y;
                        SDL_FillRect(screen, &rect, WHITE);
                        center_text("THE END", RES_Y/2);
                        sprintf(temp, "score: %d", 
                                coins+lifes*100+progress*100);
                        center_text(temp, RES_Y/2+LETTER_HEIGHT);
                        lifes = 0;
                        show_screen();
                        event.type = 0;
                        while (event.type != SDL_KEYDOWN)
                          SDL_PollEvent(&event);
                        select_level = 0;
                    }
                }
                #ifdef DEVEL
                if (event.key.keysym.sym == SDLK_1)
                {
                    progress--;
                    pos = progress;
                }
                if (event.key.keysym.sym == SDLK_2)
                {
                    progress++;
                    pos = progress;
                }
                #endif
                if (event.key.keysym.sym == SDLK_ESCAPE ||
					event.key.keysym.sym == SDLK_q) check_quit();
                oki->pos.x = map[pos].x;
                oki->pos.y = map[pos].y;
                if (lifes > 0) show_select();
            break;
            case SDL_QUIT:
                exit(0);
            break;
        }
    }
}
