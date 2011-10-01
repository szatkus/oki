#include "SDL.h"
#ifdef OPENGL
#include <GL/gl.h>
#endif

#include "global.h"
#include "map.h"
#include "move.h"
#include "timer.h"
#include "objects.h"
#include "game.h"
#include "menu.h"
#include "anim.h"
#include "event.h"
#include "font.h"
#include "fps.h"
#include "image.h"

int timer()
{
    SDL_Rect rect, rect2;
    Uint16 i, t;
    SDL_Event event;
    
    rect.x = 0;
    rect.y = 0;
    rect.w = RES_X;
    rect.h = RES_Y;
    SDL_FillRect(screen, &rect, 0);
    for (i=0;i<=255;i++)
    {
        if (obj[i].vis)
        {
            if (obj[i].img != events)
            {
              if (obj[i].dir == DIR_LEFT) obj[i].anim.y = obj[i].pos.h;
              if (obj[i].dir == DIR_RIGHT) obj[i].anim.y = 0;
            }
            if (obj[i].ghost > 0) obj[i].ghost++;
            if (obj[i].ghost > 80) obj[i].ghost = 1;
            switch (obj[i].type)
            {
                case OBJ_WATER: 
                    obj[i].pos.y-=obj[i].speed;
                    obj[i].pos.h+=obj[i].speed;
                    obj[i].anim.h+=obj[i].speed;
                break;
                case OBJ_TRAP: 
                    obj[i].strength++;
                    if (obj[i].strength >= 11 && obj[i].strength <= 15) 
                        obj[i].pos.y += 2;
                    if (obj[i].strength >= 16 && obj[i].strength <= 20) 
                        obj[i].pos.y -= 2;
                    if (obj[i].strength == 20) obj[i].strength = 0;
                break;
            }
            move(i);
        }
    }
    camera.x = oki->pos.x-RES_X/2;
    if (camera.x < 0) camera.x = 0;
    if (camera.x > game->w-RES_X) camera.x = game->w-RES_X;
    camera.y = oki->pos.y-RES_Y/2;
    camera.y+=camera_modifier;
    if (camera.y < 0) camera.y = 0;
    if (camera.y > game->h-RES_Y) camera.y = game->h-RES_Y; 
    SDL_BlitSurface(statics, &camera, game, &camera);
    for (i=0;i<=255;i++)
    {
        if (anim[i].vis)
        {
            if (anim[i].wait == anim[i].delay)
            {
                anim[i].anim.x+=anim[i].anim.w;
                if (anim[i].anim.x == anim[i].frames*anim[i].anim.w) 
                    anim[i].anim.x = 0;
                if (anim[i].loop == 1) anim[i].vis = 0;
                if (anim[i].loop > 0) anim[i].loop--;
                anim[i].wait = 0;
            } else anim[i].wait++;
            SDL_BlitSurface(anim[i].img, &anim[i].anim, game, &anim[i].pos);
        }
    }
    for (i=0;i<=255;i++)
    {
        if (obj[i].vis && obj[i].ghost < 40)
        {
            touch_oki(i);
            if (obj[i].blink) obj[i].blink--;
            if (obj[i].blink-((obj[i].blink/2)*2)) obj[i].anim.x+=100;
            else 
            {
                if (obj[i].anim.x >= 100) obj[i].anim.x-=100;
            }
            if (obj[i].speed >= 10) SDL_BlitSurface(obj[i].img, &obj[i].old_anim, 
                                                    game, &obj[i].old_pos);
            if (die && i == 255) oki->anim.x = 40;
            
            if (obj[i].pos.x > camera.x-obj[i].pos.w &&
                obj[i].pos.x < camera.x+camera.w+obj[i].pos.w &&
                obj[i].pos.y > camera.y-obj[i].pos.h &&
                obj[i].pos.y < camera.y+camera.h+obj[i].pos.h)
              SDL_BlitSurface(obj[i].img, &obj[i].anim, game, &obj[i].pos);
            obj[i].pos.w = obj[i].anim.w;
            obj[i].pos.h = obj[i].anim.h;
        }
    }
    SDL_BlitSurface(game, &camera, screen, NULL);
    if (mask) 
    {
        SDL_FillRect(screen, NULL, WHITE);
        mask--;
    }
    rect2.y = 0;
    if (show_time > 0)
    {
        rect.x = 0;
        if (oki->pos.y-camera.y >= RES_Y/2) 
        {
            rect.y = 0;
            rect2.y = RES_Y-BLOCK_HEIGHT;
        } else rect.y = RES_Y-text_bg->h;
        SDL_BlitSurface(text_bg, NULL, screen, &rect);
        draw_text_br(text[show_text], 5, rect.y+5);
        show_time--;
    }
    rect.x = 0;
    rect.y = 0;
    rect.w = BLOCK_WIDTH;
    rect.h = BLOCK_HEIGHT;
    rect2.x = 0;
    rect2.w = rect.w;
    rect2.h = rect.h;
    SDL_BlitSurface(events, &rect, screen, &rect2);
    sprintf(temp, "%d", coins);
    draw_text(temp, 11, rect2.y+2);
    rect.x = 10;
    rect.y = 0;
    rect.w = BLOCK_WIDTH;
    rect.h = BLOCK_HEIGHT;
    rect2.x = RES_X-22;
    rect2.w = rect.w;
    rect2.h = rect.h;
    SDL_BlitSurface(events, &rect, screen, &rect2);
    sprintf(temp, "%d", lifes);
    draw_text(temp, RES_X-11, rect2.y+2);
    if (enable_fps)
    {
        sprintf(temp, "%d", fps);
        draw_text(temp, RES_X-11, RES_Y-11);
        temp_fps++;
    }
    show_screen();
    SDL_Delay(limit);
    if (die) 
    {
        die = 0;
        lifes--;
        SDL_Delay(1000);
        oki->pos = start_pos;
        oki->anim.x = 0;
        oki->anim.y = 0;
        for (i=0;i<=255;i++)
        {
            switch (obj[i].type)
            {
                case OBJ_WATER:
                    obj[i].pos.y = game->h-BLOCK_HEIGHT;
                    obj[i].pos.h = BLOCK_HEIGHT;
                    obj[i].anim.h = BLOCK_HEIGHT;
                    obj[i].vis = 1;
                    obj[i].speed = 1;
                break;
                case OBJ_WATER_STOP:
                case OBJ_WATER_UP:
                    obj[i].vis = 1;
                break;
            }
        }
        oki->blink = 30;
        oki->damage = 0;
        if (lifes < 0) 
        {
            select_level = 0;
            play = 0;
            rect.x = 0;
            rect.y = 0;
            rect.w = RES_X;
            rect.h = RES_Y;
            SDL_FillRect(screen, &rect, WHITE);
            center_text("game over", RES_Y/2);
            sprintf(temp, "score: %d", coins+progress*100);
            center_text(temp, RES_Y/2+LETTER_HEIGHT);
            show_screen();
            event.type = 0;
            while (event.type != SDL_KEYDOWN)
              SDL_PollEvent(&event);
        }
    }
    return 0;
}
