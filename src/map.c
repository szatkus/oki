#include "SDL_image.h"

#include "global.h"
#include "objects.h"
#include "map.h"
#include "anim.h"
#include "data.h"
#include "image.h"

void load_maplist()
{
    FILE *file;
    
    file = fopen("maps/maps", "r");
    mapsets = 0;
    do {
        if (maplist[mapsets] != NULL) free(maplist[mapsets]);
        maplist[mapsets] = (char*)malloc(256);
        fgets(maplist[mapsets], 256, file);
        maplist[mapsets][strlen(maplist[mapsets])-1] = 0;
        mapsets++;
    } while (!feof(file) && mapsets < 127);
    mapsets--;
    fclose(file);
}

void load_map(char filename[256])
{
    FILE *file;
    char ch;
    unsigned char width, height, x, y;
    short int i, t;
    char header[3];
    SDL_Rect rect;
    
    last_obj = 0;
    last_anim = 0;
    last_text = 0;
    last_door = 0;
    last_key = 0;
    darkness = 0;
    tookcoins = 0;
    totalcoins = 0;
    tooklifes = 0;
    totallifes = 0;
    oke = &obj[254];
    for (i=0;i<=255;i++) obj[i].type = 0;
    for (y=0;y<255;y++)
    {
        for (x=0;x<255;x++)
        {
            level.map[x][y].tile = 0;
            level.map[x][y].type = 0;
        }
    }
    file = fopen(filename, "rb");
    fread(header, sizeof(header), 1, file);
    width = fgetc(file);
    height = fgetc(file);
    level.height = height-1;
    level.width = width-1;
    SDL_FreeSurface(game);
    SDL_FreeSurface(statics);
    game = SDL_CreateRGBSurface(SDL_HWSURFACE, (level.width+1)*BLOCK_WIDTH, 
                                (level.height+1)*BLOCK_HEIGHT, 24, 0, 0, 0, 0);
    statics = SDL_CreateRGBSurface(SDL_HWSURFACE, (level.width+1)*BLOCK_WIDTH, 
                                   (level.height+1)*BLOCK_HEIGHT, 24, 0, 0, 0, 
                                   0);
    fseek(file, 11, 1);
    for (y=0;y<=level.height;y++)
    {
        for (x=0;x<=level.width;x++)
        {
            level.map[x][y].tile = fgetc(file);
            level.map[x][y].type = 0;
            if (level.map[x][y].tile >= 192)
            {
                level.map[x][y].tile-=192;
                obj[last_obj].pos.x = x*BLOCK_WIDTH;
                obj[last_obj].pos.y = y*BLOCK_HEIGHT;
                obj[last_obj].pos.w = BLOCK_WIDTH;
                obj[last_obj].pos.h = BLOCK_HEIGHT;
                obj[last_obj].vis = 1;
                obj[last_obj].state = STATE_STAY;
                obj[last_obj].dir = DIR_LEFT;
                if (last_obj >= 255) last_obj = 0;
                obj[last_obj].speed = 0;
                obj[last_obj].AI = 0;
                obj[last_obj].type = OBJ_ENEMY;
                obj[last_obj].mass = 0;
                obj[last_obj].damage = 0;
                obj[last_obj].HP = 0;
                obj[last_obj].blink = 0;
                obj[last_obj].strength = 0;
                obj[last_obj].ghost = 0;
                obj[last_obj].shoot = 0;
                obj[last_obj].jump.power = 0;
                obj[last_obj].jump.frame = 0;
                obj[last_obj].jump.time = 0;
                obj[last_obj].img = events;
                obj[last_obj].anim.x = 0;
                obj[last_obj].anim.y = 0;
                obj[last_obj].anim.w = BLOCK_WIDTH;
                obj[last_obj].anim.h = BLOCK_HEIGHT;
                switch (level.map[x][y].tile)
                {
                    case 0:
                        obj[last_obj].speed = 1;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 5;
                        obj[last_obj].img = monster[0];
                    break;
                    case 1:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_COIN;
                        totalcoins++;
                    break;
                    case 2:
                        obj[last_obj].dir = DIR_ZERO;   
                        obj[last_obj].type = OBJ_LIFE;
                        obj[last_obj].anim.x = BLOCK_WIDTH;
                        totallifes++;
                    break;
                    case 3:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_STRENGTH;
                        obj[last_obj].anim.x = 3*BLOCK_WIDTH;
                    break;
                    case 4:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_DEATH;
                        obj[last_obj].anim.y = BLOCK_HEIGHT;
                    break;
                    case 5:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_JUMP;
                        obj[last_obj].anim.x = BLOCK_WIDTH;
                        obj[last_obj].anim.y = BLOCK_HEIGHT;
                    break;
                    case 6:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_SPEED;
                        obj[last_obj].anim.x = 2*BLOCK_WIDTH;
                        obj[last_obj].anim.y = BLOCK_HEIGHT;
                    break;
                    case 7:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 1;
                        obj[last_obj].type = OBJ_ENEMY;
                        obj[last_obj].mass = 7;
                        obj[last_obj].img = monster[1];
                    break;
                    case 8:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = 1;
                        obj[last_obj].type = OBJ_WATER;
                        obj[last_obj].img = 
                        SDL_CreateRGBSurface(SDL_HWSURFACE, game->w, game->h,
                                             24, 0, 0, 0, 0);
                        for (i=0;i<=level.width;i++)
                        {
                            cut_image(tileset, obj[last_obj].img, 5, 8, 
                                      i*BLOCK_WIDTH, 0, BLOCK_WIDTH, 
                                      BLOCK_HEIGHT);
                            for (t=1;t<=level.height;t++)
                            {
                            cut_image(tileset, obj[last_obj].img, 6, 8, 
                                      i*BLOCK_WIDTH, t*BLOCK_HEIGHT, BLOCK_WIDTH, 
                                      BLOCK_HEIGHT);
                            }
                        }
                        obj[last_obj].anim.w = game->w;
                        obj[last_obj].anim.h = BLOCK_HEIGHT;
                        obj[last_obj].pos.x = 0;
                        obj[last_obj].pos.w = game->w;
                    break;
                    case 9:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_WATER_STOP;
                        obj[last_obj].img = NULL;
                    break;
                    case 10:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_WATER_UP;
                        obj[last_obj].img = NULL;
                    break;
                    case 11:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_RUN;
                        obj[last_obj].anim.x = 3*BLOCK_WIDTH;
                        obj[last_obj].anim.y = BLOCK_HEIGHT;
                    break;
                    case 12:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = 2*BLOCK_HEIGHT;
                        obj[last_obj].type = OBJ_UP;
                        obj[last_obj].anim.y = 2*BLOCK_HEIGHT;
                    break;
                    case 13:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_DEATH;
                        obj[last_obj].anim.x = BLOCK_HEIGHT;
                        obj[last_obj].anim.y = 2*BLOCK_HEIGHT;
                    break;
                    case 14:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_DEATH;
                        obj[last_obj].anim.x = 2*BLOCK_HEIGHT;
                        obj[last_obj].anim.y = 2*BLOCK_HEIGHT;
                    break;
                    case 15:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_DEATH;
                        obj[last_obj].anim.x = 3*BLOCK_HEIGHT;
                        obj[last_obj].anim.y = 2*BLOCK_HEIGHT;
                    break;
                    case 16:
                        obj[last_obj].speed = 3;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 9;
                        obj[last_obj].strength = 1;
                        obj[last_obj].img = monster[2];
                        obj[last_obj].anim.w = 2*BLOCK_WIDTH;
                        obj[last_obj].anim.h = 2*BLOCK_HEIGHT;
                        obj[last_obj].pos.w = 2*BLOCK_WIDTH;
                        obj[last_obj].pos.h = 2*BLOCK_HEIGHT;
                    break;
                    case 17:
                        obj[last_obj].speed = 0;
                        obj[last_obj].strength = last_text;
                        obj[last_obj].type = OBJ_TEXT;
                        obj[last_obj].img = NULL;
                        fgets(text[last_text], fgetc(file), file);
                        last_text++;
                    break;
                    case 18:
                        obj[last_obj].speed = 6;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 3;
                        obj[last_obj].strength = 2;
                        obj[last_obj].jump.power = 5;
                        obj[last_obj].jump.time = 6;
                        obj[last_obj].img = monster[3];
                    break;
                    case 19:
                        obj[last_obj].speed = 11;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 5;
                        obj[last_obj].strength = 3;
                        obj[last_obj].jump.power = 7;
                        obj[last_obj].jump.time = 8;
                        obj[last_obj].img = monster[4];
                    break;
                    case 21:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].AI = last_key;
                        obj[last_obj].type = OBJ_KEY;
                        obj[last_obj].img = events;
                        obj[last_obj].anim.x = 6*BLOCK_HEIGHT;
                        obj[last_obj].anim.y = 2*BLOCK_HEIGHT;
                        last_key++;
                    break;
                    case 22:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_JUMP_TIME;
                        obj[last_obj].anim.x = 7*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 2*BLOCK_HEIGHT;
                    break;
                    case 23:
                        obj[last_obj].speed = 3;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 3;
                        obj[last_obj].strength = 1;
                        obj[last_obj].HP = 1;
                        obj[last_obj].img = monster[5];
                        obj[last_obj].run = 1;
                    break;
                    case 24:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = 5*BLOCK_HEIGHT;
                        obj[last_obj].type = OBJ_UP;
                        obj[last_obj].anim.x = BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 25:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 5;
                        obj[last_obj].strength = last_text;
                        obj[last_obj].type = OBJ_TEXT;
                        obj[last_obj].img = man;
                        fgets(text[last_text], fgetc(file), file);
                        last_text++;
                    break;
                    case 26:
                        oke = &obj[last_obj];
                        oke->mass = 6;
                        oke->AI = 2;
                        oke->type = 0;
                        oke->img = oke_img;
                        oke->speed = oki->speed-1;
                        oke->strength = oki->strength+1;
                        oke->run = oki->run;
                        oke->jump.power = oki->jump.power;
                        oke->jump.time = oki->jump.time;
                    break;
                    case 27:
                        obj[last_obj].speed = 7;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 8;
                        obj[last_obj].strength = 3;
                        obj[last_obj].HP = 3;
                        obj[last_obj].img = monster[6];
                    break;
                    case 28:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = 100*BLOCK_HEIGHT;
                        obj[last_obj].type = OBJ_UP;
                        obj[last_obj].anim.x = 2*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 29:
                        obj[last_obj].type = OBJ_DEATH;
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 9;
                        obj[last_obj].img = monster[7];
                    break;
                    case 30:
                        obj[last_obj].type = OBJ_DARKER;
                        obj[last_obj].img = NULL;
                    break;
                    case 31:
                        obj[last_obj].type = OBJ_LIGHTER;
                        obj[last_obj].img = NULL;
                    break;
                    case 32:
                        obj[last_obj].speed = 3;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 5;
                        obj[last_obj].strength = 3;
                        obj[last_obj].img = monster[8];
                    break;
                    case 33:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 1;
                        obj[last_obj].strength = 5;
                        obj[last_obj].img = monster[9];
                        obj[last_obj].anim.w = 4*BLOCK_WIDTH;
                        obj[last_obj].anim.h = 4*BLOCK_HEIGHT;
                        obj[last_obj].pos.w = 4*BLOCK_WIDTH;
                        obj[last_obj].pos.h = 4*BLOCK_HEIGHT;
                    break;
                    case 34:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = 0;
                        obj[last_obj].img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 3;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 2;
                        anim[last_anim].img = torch;
                        anim[last_anim].pos = obj[last_obj].pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                    break;
                    case 35:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 5;
                        obj[last_obj].type = OBJ_CLONE;
                        obj[last_obj].img = man;
                    break;
                    case 36:
                        obj[last_obj].speed = 3;
                        obj[last_obj].jump.time = 5;
                        obj[last_obj].jump.power = 5;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 5;
                        obj[last_obj].type = OBJ_CLONE;
                        obj[last_obj].img = monster[10];
                    break;
                    case 37:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_HP;
                        obj[last_obj].anim.x = 5*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 38:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_HEALTH;
                        obj[last_obj].anim.x = 6*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 39:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_DEATH;
                        obj[last_obj].img = rock;
                        obj[last_obj].mass = 15;
                        obj[last_obj].anim.w = 3*BLOCK_WIDTH;
                        obj[last_obj].anim.h = 3*BLOCK_HEIGHT;
                        obj[last_obj].pos.w = 3*BLOCK_WIDTH;
                        obj[last_obj].pos.h = 3*BLOCK_HEIGHT;
                    break;
                    case 40:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_BOMB;
                        obj[last_obj].strength = 3;
                        obj[last_obj].anim.x = 7*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 41:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_TRAP;
                        obj[last_obj].anim.x = 0;
                        obj[last_obj].anim.y = 4*BLOCK_HEIGHT;
                        obj[last_obj].anim.h = 2*BLOCK_HEIGHT;
                        obj[last_obj].pos.y -= BLOCK_HEIGHT;
                        obj[last_obj].pos.h = 2*BLOCK_HEIGHT;
                    break;
                    case 42:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_SHOOT;
                        obj[last_obj].anim.x = BLOCK_WIDTH;
                        obj[last_obj].anim.y = 4*BLOCK_HEIGHT;
                    break;
                    case 43:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_FALL;
                        obj[last_obj].strength = 5;
                        obj[last_obj].anim.x = 2*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 4*BLOCK_HEIGHT;
                    break;
                    case 44:
                        obj[last_obj].speed = 1;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 0;
                        obj[last_obj].img = monster[12];
                        obj[last_obj].strength = 99;
                    break;
                    case 45:
                        obj[last_obj].mass = 0;
                        obj[last_obj].dir = DIR_RIGHT;
                        obj[last_obj].img = monster[12];
                        obj[last_obj].strength = 99;
                        obj[last_obj].ghost = 1;
                    break;
                    case 46:
                        obj[last_obj].mass = 0;
                        obj[last_obj].speed = 1;
                        obj[last_obj].AI = 1;
                        obj[last_obj].img = monster[12];
                        obj[last_obj].strength = 99;
                        obj[last_obj].ghost = 1;
                    break;
                    case 47:
                        obj[last_obj].speed = 1;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 0;
                        obj[last_obj].img = monster[12];
                        obj[last_obj].strength = 99;
                    break;
                    case 48:
                        obj[last_obj].speed = 3;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 3;
                        obj[last_obj].strength = 1;
                        obj[last_obj].HP = 1;
                        obj[last_obj].img = monster[5];
                    break;
                    case 49:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = 0;
                        obj[last_obj].img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 5;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 2;
                        anim[last_anim].img = glass;
                        anim[last_anim].pos = obj[last_obj].pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH*2;
                        anim[last_anim].anim.h = BLOCK_HEIGHT*4;
                        last_anim++;
                    break;
                    case 50:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = 0;
                        obj[last_obj].img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 5;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 2;
                        anim[last_anim].img = computer;
                        anim[last_anim].pos = obj[last_obj].pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                    break;
                    case 51:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 1;
                        obj[last_obj].strength = 1;
                        obj[last_obj].jump.power = 5;
                        obj[last_obj].jump.time = 3;
                        obj[last_obj].img = monster[13];
                    break;
                    case 52:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 1;
                        obj[last_obj].strength = 1;
                        obj[last_obj].jump.power = 5;
                        obj[last_obj].jump.time = 3;
                        obj[last_obj].img = monster[13];
                    break;
                    case 53:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 1;
                        obj[last_obj].mass = 9;
                        obj[last_obj].img = monster[14];
                        obj[last_obj].anim.w = 2*BLOCK_WIDTH;
                        obj[last_obj].anim.h = 2*BLOCK_HEIGHT;
                        obj[last_obj].pos.w = 2*BLOCK_WIDTH;
                        obj[last_obj].pos.h = 2*BLOCK_HEIGHT;
                        obj[last_obj].type = OBJ_BOMB;
                        obj[last_obj].strength = 6;
                    break;
                    case 54:
                        obj[last_obj].speed = 2;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 9;
                        obj[last_obj].img = monster[14];
                        obj[last_obj].anim.w = 2*BLOCK_WIDTH;
                        obj[last_obj].anim.h = 2*BLOCK_HEIGHT;
                        obj[last_obj].pos.w = 2*BLOCK_WIDTH;
                        obj[last_obj].pos.h = 2*BLOCK_HEIGHT;
                        obj[last_obj].type = OBJ_BOMB;
                        obj[last_obj].strength = 6;
                    break;
                    case 55:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_BOMB;
                        obj[last_obj].strength = 9;
                        obj[last_obj].anim.x = 7*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 56:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_BOMB;
                        obj[last_obj].strength = 27;
                        obj[last_obj].anim.x = 7*BLOCK_WIDTH;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 57:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = -2*BLOCK_HEIGHT;
                        obj[last_obj].type = OBJ_UP;
                        obj[last_obj].anim.y = 4*BLOCK_HEIGHT;
                        obj[last_obj].anim.x = 3*BLOCK_WIDTH;
                    break;
                    case 58:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = -2*BLOCK_WIDTH;
                        obj[last_obj].type = OBJ_GO;
                        obj[last_obj].anim.y = 4*BLOCK_HEIGHT;
                        obj[last_obj].anim.x = 4*BLOCK_WIDTH;
                    break;
                    case 59:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].speed = 2*BLOCK_WIDTH;
                        obj[last_obj].type = OBJ_GO;
                        obj[last_obj].anim.y = 4*BLOCK_HEIGHT;
                        obj[last_obj].anim.x = 5*BLOCK_WIDTH;
                    break;
                    case 60:
                        obj[last_obj].speed = 3;
                        obj[last_obj].AI = 2;
                        obj[last_obj].mass = 3;
                        obj[last_obj].strength = 0;
                        obj[last_obj].HP = 1;
                        obj[last_obj].img = monster[11];
                        obj[last_obj].run = 1;
                        obj[last_obj].anim.h = BLOCK_HEIGHT+5;
                    break;
                    case 61:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_CHECKPOINT;
                        obj[last_obj].img = events;
                        obj[last_obj].anim.y = 3*BLOCK_HEIGHT;
                    break;
                    case 62:
                        obj[last_obj].dir = DIR_ZERO;
                        obj[last_obj].type = OBJ_EXIT;
                        obj[last_obj].img = NULL;
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 4;
                        anim[last_anim].loop = 0;
                        anim[last_anim].delay = 0;
                        anim[last_anim].img = IMG_Load(getdata("gfx/exit.png"));
                        anim[last_anim].pos = obj[last_obj].pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                    break;
                    case 63:
                        obj[last_obj].vis = 0;
                        last_obj--;
                        oki->pos.x = x*BLOCK_WIDTH;
                        oki->pos.y = y*BLOCK_HEIGHT;
                        start_pos = oki->pos;
                    break;
                }
                if (level.map[x][y].tile == 20)
                {
                    level.map[x][y].tile = 20;
                    level.map[x][y].type = MAP_WALL;
                    if (!(obj[last_obj].pos.x > door[last_door-1].x &&
                          obj[last_obj].pos.x < 
                          door[last_door-1].x+door[last_door-1].w &&
                          obj[last_obj].pos.y > door[last_door-1].y &&
                          obj[last_obj].pos.y < 
                          door[last_door-1].y+door[last_door-1].h))
                    {
                        if (door[last_door-1].x+door[last_door-1].w == 
                            obj[last_obj].pos.x && door[last_door-1].y == 
                            obj[last_obj].pos.y)
                            door[last_door-1].w+=BLOCK_WIDTH;
                        else
                        {
                            if (door[last_door-1].y+door[last_door-1].h == 
                                obj[last_obj].pos.y && door[last_door-1].x == 
                                obj[last_obj].pos.x)
                                door[last_door-1].h+=BLOCK_HEIGHT;
                            else
                            {
                                door[last_door] = obj[last_obj].pos;
                                last_door++;
                            }
                        }
                    }
                    last_obj--;
                } else level.map[x][y].tile = 0;
                last_obj++;
            }
            while (level.map[x][y].tile >= 64)
            {
                level.map[x][y].type++;
                level.map[x][y].tile-=64;
            }
        }
    }
    fclose(file);
    for (i=last_obj;i<255;i++) obj[i].vis = 0;
    for (i=last_anim;i<=255;i++) anim[i].vis = 0;
    if (oki->shoot) 
    {
        last_obj++;
        oki->shoot = last_obj;
    }
}

void show_map()
{
    int x, y;
    
    for (y=0;y<=level.height;y++)
    {
        for (x=0;x<=level.width;x++)
            cut_image(tileset, statics, level.map[x][y].tile, 8, x*BLOCK_WIDTH, 
                      y*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);
    }
}
