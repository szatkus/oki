#include "SDL.h"
#include "SDL_image.h"

#include "global.h"
#include "data.h"
#include "conf.h"
#include "font.h"
#include "image.h"
#include "okiGL.h"
#include "MEargc.h"
#include "MEevent.h"
#include "MErefresh.h"
#include "MEmap.h"
#include "MEtext.h"

int main(int *args,
         char **argc)
{
    char i;
    
    atexit(SDL_Quit);
    load_cfg();
    check_argc(args, argc);
    SDL_Init(SDL_INIT_VIDEO);
    #ifndef OPENGL
    screen = SDL_SetVideoMode(RES_X, RES_Y, 8, SDL_SWSURFACE | SDL_FULLSCREEN*fs);
    #else
    SDL_SetVideoMode(800, 600, 24, SDL_OPENGL | SDL_FULLSCREEN*fs);
    screen = SDL_CreateRGBSurface(SDL_SWSURFACE, 256, 128, 24, 0, 0, 0, 0);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &screenGL);
    glBindTexture(GL_TEXTURE_2D, screenGL);
    glClearColor(1, 1, 1, 1);
    #endif
    SDL_ShowCursor(SDL_ENABLE);
    SDL_WM_SetCaption("Oki - map editor", "Oki - map editor");
    SDL_WM_SetIcon(IMG_Load(getdata("gfx/oki10.png")), 0);
    load_images();
    tile = 0;
    type = 0;
    mode = 1;
    camera.x = 0;
    camera.y = 0;
    camera.w = RES_X;
    camera.h = RES_Y;
    cursor.x = 0;
    cursor.y = 0;
    cursor.w = 10;
    cursor.h = 10;
    game = SDL_CreateRGBSurface(SDL_HWSURFACE, 256*BLOCK_WIDTH, 
                                256*BLOCK_HEIGHT, 24, 0, 0, 0, 0);
    if (new_map) 
    {
       level.width = 15;
       level.height = 11;
    }
    else load_map(map);
    refresh_static();
    check_event();
    return 0;
}
