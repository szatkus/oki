#ifdef SOUND
#include "SDL_mixer.h"
#endif

#ifndef SOUND
typedef int Mix_Chunk;
#endif

Mix_Chunk *jump, *bonus, *death, *cursor, *click, *slap, *boom;

void play_snd(Mix_Chunk *sample);
