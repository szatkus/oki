#include "SDL.h"
#include "SDL_image.h"
#include "SDL_thread.h"
#ifdef SOUND
#include "SDL_mixer.h"
#endif

#include "global.h"
#include "event.h"
#include "font.h"
#include "map.h"
#include "argc.h"
#include "objects.h"
#include "menu.h"
#include "data.h"
#include "conf.h"
#include "sound.h"
#include "fps.h"
#include "image.h"
#include "okiGL.h"

int main(int *args,
         char **argc)
{
    char i;
    
    mapset = 0;
    #ifdef SOUND
    atexit(Mix_CloseAudio);
    #endif
    atexit(SDL_Quit);
    atexit(save_cfg);
    load_cfg();
    check_argc(args, argc);
    SDL_Init(SDL_INIT_VIDEO);
    #ifdef SOUND
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    #endif
    #ifndef OPENGL
    screen = SDL_SetVideoMode(RES_X, RES_Y, 8, SDL_SWSURFACE | SDL_FULLSCREEN*fs);
    #else
    SDL_SetVideoMode(800, 600, 24, SDL_OPENGL | SDL_FULLSCREEN*fs);
    screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 256, 128, 24, 0, 0, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &screenGL);
    glBindTexture(GL_TEXTURE_2D, screenGL);
    #endif
    if (fs) SDL_ShowCursor(SDL_DISABLE);
    SDL_WM_SetCaption("Oki", "Oki");
    SDL_WM_SetIcon(IMG_Load(getdata("gfx/oki10.png")), 0);
    strcpy(text[0], "game saved!");
    oki = &obj[255];
    oki->img = IMG_Load(getdata("gfx/oki.png"));
    oki->pos.w = BLOCK_WIDTH;
    oki->pos.h = BLOCK_HEIGHT;
    oki->anim.x = 0;
    oki->anim.y = 0;
    oki->anim.w = oki->pos.w;
    oki->anim.h = oki->pos.h;
    #ifdef SOUND
    jump = Mix_LoadWAV(getdata("snd/jump.wav"));
    bonus = Mix_LoadWAV(getdata("snd/bonus.wav"));
    death = Mix_LoadWAV(getdata("snd/death.wav"));
    cursor = Mix_LoadWAV(getdata("snd/cursor.wav"));
    click = Mix_LoadWAV(getdata("snd/click.wav"));
    slap = Mix_LoadWAV(getdata("snd/hit.wav"));
    boom = Mix_LoadWAV(getdata("snd/boom.wav"));
    #endif
    load_images();
    load_maplist();
    camera.x = 0;
    camera.y = 0;
    camera.w = RES_X;
    camera.h = RES_Y;
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_IGNORE);
    SDL_EventState(SDL_MOUSEBUTTONUP, SDL_IGNORE);
    SDL_FillRect(screen, &camera, WHITE);
    show_screen();
    if (enable_fps) SDL_CreateThread(&count_fps, NULL);
    start_menu();
    return 0;
}
