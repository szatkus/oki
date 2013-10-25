#include "SDL.h"

#include "global.h"
#include "timer.h"
#include "objects.h"
#include "game.h"
#include "sound.h"
#include "save.h"
#include "anim.h"
#include "map.h"
#include "image.h"
#include "font.h"
#include "event.h"

void touch_oki(Uint8 id)
{
    SDL_Rect rect;
    Sint16 i, t, damage;
    Uint16 id2;
    SDL_Event event;
    char* great;
    
    if (obj[id].type > 0)
    {
        if (obj[id].type == OBJ_FALL)
        {
            if (oki->pos.x >= obj[id].pos.x-oki->pos.w &&
                oki->pos.x <= obj[id].pos.x+obj[id].pos.w &&
                oki->pos.y >= obj[id].pos.y &&
                oki->pos.y <= obj[id].pos.y+BLOCK_HEIGHT*10)
            {
                obj[id].mass = obj[id].strength;
                obj[id].type = OBJ_DEATH;
            }
        }
        for (id2=0;id2<=255;id2++)
        {
            if (obj[id2].vis && obj[id2].mass && touch(id2, id))
            {
                damage = 0;
                switch (obj[id].type)
                {
                    case OBJ_ENEMY:
                        if (obj[id2].type != OBJ_ENEMY)
                        {
                            if (!obj[id2].blink && obj[id].blink <= 20) damage = 1;
                            if ((obj[id2].state == STATE_FALL &&
                                 obj[id2].pos.y-obj[id2].pos.h < obj[id].pos.y &&
                                 obj[id2].strength-obj[id].strength > 0) ||
                               (obj[id2].run == 2 && obj[id2].state != STATE_STAY &&
                                obj[id2].strength-obj[id].strength > 1) ||
                               obj[id2].strength-obj[id].strength > 2)
                            {                    
                                damage = 0;
                                if (!obj[id].blink) 
                                {
                                    obj[id].damage+=obj[id2].strength-obj[id].strength;
                                    obj[id].blink = 30;
                                    play_snd(death);
                                }
                                if (obj[id].damage > obj[id].HP) 
                                {
                                    obj[id].vis = 0;
                                    coins+=obj[id].strength*obj[id].AI+1;
                                    anim[last_anim].vis = 1;
                                    anim[last_anim].frames = 2;
                                    anim[last_anim].loop = 10;
                                    anim[last_anim].img = killed;
                                    anim[last_anim].pos = obj[id].pos;
                                    anim[last_anim].anim.x = 0;
                                    anim[last_anim].anim.y = 0;
                                    anim[last_anim].anim.w = BLOCK_WIDTH;
                                    anim[last_anim].anim.h = BLOCK_HEIGHT;
                                    last_anim++;
                                    if (obj[id].img == monster[11])
                                    {
                                        SDL_Delay(500);
                                        play_snd(death);
                                        SDL_Delay(500);
                                        play_snd(slap);
                                        SDL_Delay(500);
                                        play_snd(bonus);
                                        SDL_Delay(500);
                                        obj[id].vis = 1;
                                        obj[id].type = OBJ_EXIT;
                                    }
                                }
                            }
                            if (damage) 
                            {
                                play_snd(death);
                                obj[id2].blink = 30;
                            }
                            obj[id2].damage+=damage;
                        }
                    break;
                    case OBJ_WATER:
                        play_snd(death);
                        obj[id2].damage = obj[id2].HP+1;
                    break;
                    case OBJ_DEATH:
                    case OBJ_TRAP:
                    case OBJ_ONE_DEATH:
                        if (obj[id2].type != OBJ_DEATH && 
                            !(obj[id].type == OBJ_ONE_DEATH && 
                              obj[id2].type == 0))
                        {
                            play_snd(death);
                            obj[id2].damage = obj[id2].HP+1;
                            if (obj[id].type == OBJ_ONE_DEATH) obj[id].vis = 0;
                        }
                    break;
                    case OBJ_UP:
                        obj[id2].pos.y-=obj[id].speed;
                        obj[id2].fall = 1;
                    break;
                    case OBJ_GO:
                        obj[id2].pos.x-=obj[id].speed;
                    break;
                }
                if (id2 == 255)
                {
                    switch (obj[id].type)
                    {     
                        case OBJ_COIN:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            coins++;
                            tookcoins++;
                        break;
                        case OBJ_LIFE:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            lifes++;
                            tooklifes++;
                        break;
                        case OBJ_STRENGTH:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->strength++;
                        break;
                        case OBJ_EXIT:
                            play_snd(click);
                            if (progress == pos)
                            {
                                progress++;
                                pos = progress;
                            }
                            oki->dir = DIR_ZERO;
                            if (oki->run == 2) oki->speed=oki->speed/2+1;
                            if (progress != maps) save_game();
                            play = 0;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = RES_X;
                            rect.h = RES_Y;
                            SDL_FillRect(screen, &rect, WHITE);
                            center_text("level finished!", RES_Y/2);
                            great = "";
                            if (tookcoins == totalcoins)
                            {
                              great = "+1 life";
                              lifes++;
                            }
                            sprintf(temp, "taken coins: %d/%d %s", tookcoins, totalcoins, great);
                            center_text(temp, RES_Y/2+LETTER_HEIGHT*2);
                            great = "";
                            if (tooklifes == totallifes)
                            {
                              great = "+1 life";
                              lifes++;
                            }
                            sprintf(temp, "taken lifes: %d/%d %s", tooklifes, totallifes, great);
                            center_text(temp, RES_Y/2+LETTER_HEIGHT*3);
                            show_screen();
                            event.type = 0;
                            while (event.type != SDL_KEYDOWN)
                              SDL_PollEvent(&event);
                        break;
                        case OBJ_JUMP:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->jump.power++;
                        break;
                        case OBJ_SPEED:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->speed++;
                        break;
                        case OBJ_WATER_STOP:
                            obj[id].vis = 0;
                            for (i=0;i<255;i++)
                            {
                                if (obj[i].type == OBJ_WATER) obj[i].speed = 0;
                            }
                        break;
                        case OBJ_WATER_UP:
                            obj[id].vis = 0;
                            for (i=0;i<255;i++)
                            {
                                if (obj[i].type == OBJ_WATER) obj[i].speed++;
                            }
                        break;
                        case OBJ_RUN:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->run = 1;
                        break;
                        case OBJ_TEXT:
                            show_text = obj[id].strength;
                            show_time = strlen(text[show_text])*2;
                            if (!obj[id].AI) obj[id].vis = 0;
                        break;
                        case OBJ_KEY:
                            obj[id].vis = 0;
                            id = obj[id].AI;
                            for (i=0;i<(door[id].w/BLOCK_WIDTH);i++)
                            {
                                for (t=0;t<(door[id].h/BLOCK_WIDTH);t++)
                                {
                                     level.map[(door[id].x/BLOCK_WIDTH)+i]
                                              [(door[id].y/BLOCK_HEIGHT)+t].type 
                                              = MAP_EMPTY;
                                     level.map[(door[id].x/BLOCK_WIDTH)+i]
                                              [(door[id].y/BLOCK_HEIGHT)+t].type
                                              = 0;
                                     cut_image(tileset, statics, 0, 8, 
                                               door[id].x+i*BLOCK_WIDTH, 
                                               door[id].y+t*BLOCK_HEIGHT, 
                                               BLOCK_WIDTH, BLOCK_HEIGHT);
                                }
                            }
                        break;
                        case OBJ_JUMP_TIME:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->jump.time++;
                        break;
                        case OBJ_CHECKPOINT:
                            play_snd(cursor);
                            obj[id].vis = 0;
                            start_pos = obj[id].pos;
                        break;
                        case OBJ_LIGHTER:
                            if (darkness < 1) darkness = 1;
                            darkness--;
                            obj[id].vis = 0;
                        break;
                        case OBJ_DARKER: 
                            darkness++;
                            if (darkness > 6) darkness = 6;
                            obj[id].vis = 0;
                        break;
                        case OBJ_CLONE:
                            play_snd(click);
                            obj[id] = *oki;
                            obj[id].AI = 2;
                            obj[id].type = OBJ_ENEMY;
                            obj[id].blink = 50;
                            anim[last_anim].vis = 1;
                            anim[last_anim].frames = 2;
                            anim[last_anim].loop = 20;
                            anim[last_anim].delay = 0;
                            anim[last_anim].img = killed;
                            anim[last_anim].pos = obj[id].pos;
                            anim[last_anim].anim.x = 0;
                            anim[last_anim].anim.y = 0;
                            anim[last_anim].anim.w = BLOCK_WIDTH;
                            anim[last_anim].anim.h = BLOCK_HEIGHT;
                            last_anim++;
                        break;
                        case OBJ_HP:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->HP++;
                        break;
                        case OBJ_HEALTH:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->damage = 0;
                        break;
                        case OBJ_BOMB:
                            play_snd(boom);
                            for (i=obj[id].pos.x/BLOCK_WIDTH-obj[id].strength;
                                 i<obj[id].pos.x/BLOCK_WIDTH+obj[id].strength+1;
                                 i++)
                            {
                                for (t=obj[id].pos.y/BLOCK_HEIGHT-obj[id].strength;
                                     t<obj[id].pos.y/BLOCK_HEIGHT+obj[id].strength+1;
                                     t++)
                                {
                                    if (i >= 0 && i < level.width && t >= 0 &&
                                        t < level.height)
                                    {
                                      level.map[i][t].type = 0;
                                      cut_image(tileset, statics, 0, 8, 
                                                i*BLOCK_WIDTH, t*BLOCK_HEIGHT, 
                                                BLOCK_WIDTH, BLOCK_HEIGHT);
                                    }
                                }
                            }
                            obj[id].vis = 0;
                            mask = obj[id].strength;
                        break;
                        case OBJ_SHOOT:
                            play_snd(bonus);
                            obj[id].vis = 0;
                            oki->shoot = 1;
                            oki->shoot = last_obj;
                            last_obj++;
                        break;
                    }
                }
                if (obj[id2].damage > obj[id2].HP) 
                {
                    if (id2 != 255)
                    {
                        anim[last_anim].vis = 1;
                        anim[last_anim].frames = 2;
                        anim[last_anim].loop = 10;
                        anim[last_anim].delay = 0;
                        anim[last_anim].img = killed;
                        anim[last_anim].pos = obj[id2].pos;
                        anim[last_anim].anim.x = 0;
                        anim[last_anim].anim.y = 0;
                        anim[last_anim].anim.w = BLOCK_WIDTH;
                        anim[last_anim].anim.h = BLOCK_HEIGHT;
                        last_anim++;
                        if (&obj[id2] != oke) obj[id2].vis = 0;
                        else 
                        {
                            oke->pos = start_pos;
                            oke->damage = 0;
                        }
                    } else die = 1;
                }
            }
        }
        if (coins >= 100)
        {
            play_snd(bonus);
            coins-=100;
            lifes++;
        }
        oke->speed = oki->speed-1;
        oke->strength = oki->strength+1;
        oke->run = oki->run;
        oke->jump.power = oki->jump.power;
        oke->jump.time = oki->jump.time;
    }
}
