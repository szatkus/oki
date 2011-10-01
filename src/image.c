#include "SDL.h"
#include "SDL_image.h"

#include "global.h"
#include "data.h"
#include "image.h"
#include "font.h"

void cut_image(SDL_Surface *image, SDL_Surface *dest, int tile, int size, 
               int x, int y, int width, int height)
{
    SDL_Rect rect, rect2;

    rect.x = ((tile-((tile/size))*size))*width;
    
    rect.y = (tile/size)*height;
    rect.w = width;
    rect.h = height;
    rect2.x = x;
    rect2.y = y;
    rect2.w = width;
    rect2.h = height;
    SDL_BlitSurface(image, &rect, dest, &rect2);
}

void load_images()
{
    char i;
    
    font = IMG_Load(getdata("gfx/font.png"));
    events = IMG_Load(getdata("gfx/events.png"));
    for (i=0;i<=14;i++)
    {
        sprintf(temp, "gfx/monster%d.png", i+1);
        monster[i] = IMG_Load(getdata(temp));
    }
    tileset = IMG_Load(getdata("gfx/tileset.png"));
    killed = IMG_Load(getdata("gfx/killed.png"));
    text_bg = IMG_Load(getdata("gfx/text.png"));
    man = IMG_Load(getdata("gfx/man.png"));
    oke_img = IMG_Load(getdata("gfx/oke.png"));
    torch = IMG_Load(getdata("gfx/torch.png"));
    rock = IMG_Load(getdata("gfx/rock.png"));
    glass = IMG_Load(getdata("gfx/glass.png"));
    computer = IMG_Load(getdata("gfx/comp.png"));
}
