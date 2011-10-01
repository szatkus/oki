#include "SDL.h"
#include "SDL_image.h"

#include "global.h"
#include "objects.h"
#include "game.h"
#include "data.h"
#include "conf.h"
#include "sound.h"
#include "map.h"
#include "okiGL.h"

#define MENU_START 70

#define MENU_MAIN 0
#define MENU_OPTIONS 1
#define MENU_KEYS 2

SDL_Surface *logo;
SDL_Rect menu_select;
char menu_mode, key, menu_end, menu_show;

void show_menu()
{
    SDL_Rect rect, rect2;
    
    rect.x = 0;
    rect.y = 0;
    rect.w = RES_X;
    rect.h = RES_Y;
    SDL_FillRect(screen, &rect, 255+255*256+255*65536);
    rect.x = 30;
    rect.y = 0;
    rect.w = logo->w;
    rect.h = logo->h;
    SDL_BlitSurface(logo, NULL, screen, &rect);
    oki->anim.x = 0;
    oki->anim.y = 0;
    if (menu_mode != MENU_KEYS)
        SDL_BlitSurface(oki->img, &oki->anim, screen, &menu_select);
    center_text("szatkus 2006", 50);
    switch (menu_mode)
    {
        case MENU_MAIN:
            center_text("start game", MENU_START);
            center_text("options", MENU_START+10);
            center_text("quit game", MENU_START+20);
        break;
        case MENU_OPTIONS:
            center_text("back", MENU_START);
            if (menu_select.y == MENU_START+10) 
                center_text("restart game to apply", MENU_START-10);
            if (fs) strcpy(temp, "yes");
            else strcpy(temp, "no");
            sprintf(temp2, "fullscreen %s", temp);
            center_text(temp2, MENU_START+10);
            center_text("redefine keys", MENU_START+20);
            center_text(maplist[mapset], MENU_START+30);
            center_text("clear save (!)", MENU_START+40);
        break;
        case MENU_KEYS:
            switch (key)
            {
                case 0: draw_text("left", 60, MENU_START); break;
                case 1: draw_text("up", 60, MENU_START); break;
                case 2: draw_text("right", 60, MENU_START); break;
                case 3: draw_text("down", 60, MENU_START); break;
                case 4: draw_text("jump", 60, MENU_START); break;
                case 5: draw_text("run", 60, MENU_START); break;
            }
        break;
    }
    show_screen();
}

void start_menu()
{
    SDL_Event event;
    
    menu_show = 0;
    menu_select.x = 30;
    menu_select.y = MENU_START;
    menu_select.w = oki->pos.w;
    menu_select.h = oki->pos.h;
    menu_end = 20;
    logo = IMG_Load(getdata("gfx/logo.png"));
    show_menu();
    while (SDL_WaitEvent(&event) >= 0)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (menu_mode != MENU_KEYS)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            play_snd(cursor);
                            menu_select.y-=10;
                            if (menu_select.y < MENU_START) 
                                menu_select.y = MENU_START+menu_end;
                        break;
                        case SDLK_DOWN:
                            play_snd(cursor);
                            menu_select.y+=10;
                            if (menu_select.y > MENU_START+menu_end) 
                                menu_select.y = MENU_START;
                        break;
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            play_snd(click);
                            if (!menu_mode)
                            {
                                switch (menu_select.y)
                                {
                                    case MENU_START: start_game(maplist[mapset]); break;
                                    case MENU_START+10: 
                                        menu_mode = MENU_OPTIONS;
                                        menu_select.y = MENU_START;
                                        menu_end = 40;
                                    break;
                                    case MENU_START+20: exit(0); break;
                                }
                            } else
                            {
                                switch (menu_select.y)
                                {
                                    case MENU_START:
                                        menu_mode = MENU_MAIN;
                                        menu_select.y = MENU_START;
                                        menu_end = 20;
                                    break;
                                    case MENU_START+10: 
                                         fs = !fs;
                                    break;
                                    case MENU_START+20: 
                                         menu_mode = MENU_KEYS;
                                         key = 0;
                                    break;
                                    case MENU_START+30: 
                                         mapset++;
                                         if (mapset == mapsets) mapset = 0;
                                    break;
                                    case MENU_START+40:
                                         progress = 0;
                                         coins = 0;
                                         lifes = 2;
                                         oki->speed = 3;
                                         oki->jump.power = 5;
                                         oki->jump.time = 5;
                                         oki->strength = 0;
                                         oki->run = 0;
                                         oki->HP = 0;
                                         oki->shoot = 0;
                                         sprintf(temp, "maps/%s/save", maplist[mapset]);
                                         save_game(temp);
                                    break;
                                }
                            }
                        break;
                    }
                    if (menu_select.y >= MENU_START+20 && menu_end >= 40)
                        menu_show = 20;
                    if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
                    oki->anim.x = 0;
                    oki->anim.y = 0;
                    show_menu();
                } else
                {
                    switch (key)
                    {
                        case 0: left = event.key.keysym.sym; break;
                        case 1: up = event.key.keysym.sym; break;
                        case 2: right = event.key.keysym.sym; break;
                        case 3: down = event.key.keysym.sym; break;
                        case 4: A = event.key.keysym.sym; break;
                        case 5: 
                            B = event.key.keysym.sym;
                            menu_mode = MENU_OPTIONS;
                        break;
                    }
                    key++;
                    show_menu();
                }
            break;
            case SDL_QUIT:
                exit(0);
            break;
        }
    }
}
