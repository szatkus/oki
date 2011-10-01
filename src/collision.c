#include "global.h"
#include "map.h"
#include "objects.h"
#include "sound.h"
#include "image.h"

Uint8 touch(Uint8 id, Uint8 id2)
{ 
    return obj[id].pos.x > obj[id2].pos.x-obj[id].pos.w+1 && 
           obj[id].pos.y > obj[id2].pos.y-obj[id].pos.h+1 &&
           obj[id].pos.x < obj[id2].pos.x+obj[id2].pos.w-1 &&
           obj[id].pos.y < obj[id2].pos.y+obj[id2].pos.h-1;
}

Uint8 near(Uint8 id, Uint8 id2, Uint16 range)
{
    if (obj[id2].strength > obj[id].strength || &obj[id2] == oke)
        range*=obj[id2].strength-obj[id].strength;
    return obj[id].pos.x > obj[id2].pos.x-obj[id].pos.w+1-range && 
           obj[id].pos.y > obj[id2].pos.y-obj[id].pos.h+1-range &&
           obj[id].pos.x < obj[id2].pos.x+obj[id2].pos.w-1+range &&
           obj[id].pos.y < obj[id2].pos.y+obj[id2].pos.h-1+range;
}

void crash(Uint16 x, Uint16 y, Uint16 strength)
{
    SDL_Rect rect, rect2;
    
    if (level.map[x][y].type >= MAP_CRASH || strength > 10)
    {
        level.map[x][y].type+=strength;
        if (level.map[x][y].type > MAP_CRASH+16) 
            level.map[x][y].type = MAP_CRASH+16;
        rect.x = (3+(level.map[x][y].type-MAP_CRASH)/2)*BLOCK_HEIGHT;
        rect.y = 0;
        rect.w = BLOCK_WIDTH;
        rect.h = BLOCK_HEIGHT;
        rect2.x = x*BLOCK_WIDTH;
        rect2.y = y*BLOCK_HEIGHT;
        rect2.w = rect.w;
        rect2.h = rect.h;
        SDL_BlitSurface(events, &rect, statics, &rect2);
        if (level.map[x][y].type == MAP_CRASH+16) 
            level.map[x][y].type = MAP_EMPTY;
    }
}

Uint8 walkon(Uint8 id)
{
    Uint8 x, y, i;
    
    for (i=0;i<=obj[id].pos.h/BLOCK_HEIGHT-1;i++)
    {
        x = (obj[id].pos.x+(obj[id].dir==DIR_RIGHT)*obj[id].pos.w)/BLOCK_WIDTH;
        y = (obj[id].pos.y)/BLOCK_HEIGHT+i;
        if (level.map[x][y].type >= MAP_WALL)
        {
            if (obj[id].AI >= 3 && obj[id].state != STATE_FALL && 
                !obj[id].jump.frame) obj[id].jump.frame = 1;
            obj[id].pos.x = (obj[id].pos.x/BLOCK_WIDTH+(obj[id].dir==DIR_LEFT))
                             *BLOCK_WIDTH;
            if (obj[id].speed >= 6) crash(x, y, obj[id].strength*2);
            return 1;
        }
    }
    return 0;
}

Uint8 hit(Uint8 id)
{
    Uint8 x, y, i;
    
    for (i=0;i<=obj[id].pos.w/BLOCK_WIDTH;i++)
    {
        x = (obj[id].pos.x+(i==0)*2-(i!=0)*3)/BLOCK_WIDTH+i;
        y = obj[id].pos.y/BLOCK_HEIGHT;
        if (level.map[x][y].type >= MAP_WALL)
        {
            obj[id].pos.y = (y+1)*BLOCK_HEIGHT;
            return 1;
        }
    }
    return 0;
}

Uint8 press(Uint8 id)
{
    Uint8 x, y, i, result;
    
    result = 0;
    for (i=0;i<=obj[id].pos.w/BLOCK_WIDTH;i++)
    {
        x = (obj[id].pos.x+(i==0)*2-(i!=0)*3)/BLOCK_WIDTH+i;
        y = (obj[id].pos.y+obj[id].pos.h)/BLOCK_HEIGHT;
        if (level.map[x][y].type >= MAP_WALL)
        {
            obj[id].pos.y = y*BLOCK_HEIGHT-obj[id].pos.h;
            if (obj[id].mass > 0) crash(x, y, obj[id].mass);
            result = 1;
        }
    }
    return result;
}
