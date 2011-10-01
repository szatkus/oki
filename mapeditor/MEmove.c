#include "SDL.h"

#include "global.h"
#include "MErefresh.h"
#include "MEevent.h"
#include "MEmap.h"
#include "MEmove.h"

int move()
{
    Uint8 *keys;
    
    goX = 0;
    goY = 0;
    keys = SDL_GetKeyState(NULL);
    if (cursor.x == 0 || keys[SDLK_LEFT]) goX = 1;
    if (cursor.x == 15 || keys[SDLK_RIGHT]) goX = 2;
    if (cursor.y == 0 || keys[SDLK_UP]) goY = 1;
    if (cursor.y == 11 || keys[SDLK_DOWN]) goY = 2;
    if (goX == 1 && shift && level.width > 1) level.width-=1+fast*10;
    if (goY == 1 && shift && level.height > 1) level.height-=1+fast*10;
    if (goX == 2 && shift) level.width+=1+fast*10;
    if (goY == 2 && shift) level.height+=1+fast*10;
    if (goX == 1) camera.x-=(1+fast*10)*10;
    if (goY == 1) camera.y-=(1+fast*10)*10;
    if (goX == 2) camera.x+=(1+fast*10)*10;
        if (goY == 2) camera.y+=(1+fast*10)*10;
    if (camera.x > (level.width+1)*BLOCK_WIDTH-RES_X) 
        camera.x = (level.width+1)*BLOCK_WIDTH-RES_X;
    if (camera.y > (level.height+1)*BLOCK_HEIGHT-RES_Y) 
        camera.y = (level.height+1)*BLOCK_HEIGHT-RES_Y;
    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    refresh();
    SDL_Delay(100);
}
