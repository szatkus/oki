#include "SDL.h"

#define OBJ_ENEMY 1
#define OBJ_COIN 2
#define OBJ_LIFE 3
#define OBJ_STRENGTH 4
#define OBJ_DEATH 5
#define OBJ_EXIT 6
#define OBJ_JUMP 7
#define OBJ_SPEED 8
#define OBJ_WATER 9
#define OBJ_WATER_STOP 10
#define OBJ_WATER_UP 11
#define OBJ_RUN 12
#define OBJ_UP 13
#define OBJ_TEXT 14
#define OBJ_KEY 15
#define OBJ_JUMP_TIME 16
#define OBJ_CHECKPOINT 17
#define OBJ_DARKER 18
#define OBJ_LIGHTER 19
#define OBJ_CLONE 20
#define OBJ_HP 21
#define OBJ_HEALTH 22
#define OBJ_BOMB 23
#define OBJ_TRAP 24
#define OBJ_SHOOT 25
#define OBJ_ONE_DEATH 26
#define OBJ_FALL 27
#define OBJ_GO 28

#define STATE_STAY 0
#define STATE_WALK 1
#define STATE_FALL 2
#define STATE_JUMP 3

#define DIR_LEFT 0
#define DIR_ZERO 1
#define DIR_RIGHT 2

typedef struct
{
    char vis, state, dir, AI, type, mass, strength, run, fall, blink,
         damage, HP, ghost;
    Uint8 shoot;
    Uint16 speed;
    struct
    {
        char power, frame, time;
    } jump;
    SDL_Surface *img;
    SDL_Rect pos, anim, old_pos, old_anim;
} Obj;

Obj obj[256];
Obj *oki, *oke;
Uint8 last_obj, last_text, last_door, last_key;
char text[256][256];
SDL_Rect door[256];


void touch_oki(Uint8 id);

