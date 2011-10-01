#ifdef SOUND
#include "SDL_mixer.h"
#endif

#include "sound.h"

void play_snd(Mix_Chunk *sample)
{
    #ifdef SOUND
    if (sample == NULL) printf("\n");
    Mix_PlayChannel(-1, sample, 0);
    #endif
}
