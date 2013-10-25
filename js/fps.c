#include "SDL.h"

#include "fps.h"

int count_fps()
{
    while (1)
    {
        SDL_Delay(1000);
        fps = temp_fps;
        temp_fps = 0;
    }
}
