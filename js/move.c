#include "global.h"
#include "map.h"
#include "collision.h"
#include "objects.h"
#include "timer.h"
#include "sound.h"
#include "event.h"
#include "image.h"

void rotate(Uint8 id)
{
    if (obj[id].AI)
    {
        if (!obj[id].jump.power || (obj[id].state == STATE_FALL && 
            !(obj[id].AI >= 2 && near(255, id, 50))))
            obj[id].dir = (obj[id].dir==DIR_LEFT)*2;
        if (obj[id].jump.power && obj[id].state != STATE_FALL &&
            !obj[id].jump.frame) obj[id].jump.frame = 1;
    }
}

Uint8 go(Uint8 id)
{
    if (!start || id != 255) obj[id].pos.x+=obj[id].speed*(obj[id].dir-1);
    else 
    {
        obj[id].pos.x+=(obj[id].dir-1);
        start = 0;
    }
    if (obj[id].dir != DIR_ZERO) 
    {
        if (walkon(id)) rotate(id);
    }
}

void move(Uint8 id)
{
    if (obj[id].AI >= 2)
    {
        if (near(255, id, 50))
        {
            if (obj[id].pos.x > oki->pos.x) obj[id].dir = DIR_LEFT;
            else obj[id].dir = DIR_RIGHT;
            
            if (obj[id].pos.x >= oki->pos.x-obj[id].speed &&
                obj[id].pos.x <= oki->pos.x+obj[id].speed)
            {    
                obj[id].dir = DIR_ZERO;
                if (obj[id].img != events) obj[id].anim.x = 0;
            }
            if (obj[id].strength+2 < oki->strength && obj[id].type == OBJ_ENEMY) 
                obj[id].dir = (obj[id].dir==DIR_LEFT)*2;
        } else
        {
            if (obj[id].dir == DIR_ZERO) obj[id].dir = DIR_LEFT;
        }
    }
    if (obj[id].jump.power && near(255, id, 50))
    {
        if (obj[id].pos.y > oki->pos.y && obj[id].state != STATE_FALL && 
            !obj[id].jump.frame) obj[id].jump.frame = 1;
            if (obj[id].strength+2 < oki->strength && obj[id].type == OBJ_ENEMY)
                obj[id].jump.frame = 0;
    }
    if (obj[id].run && id != 255)
    {
        if (near(255, id, 50))
        {
            if (obj[id].run == 1) 
            {
                obj[id].speed=obj[id].speed*2-1;
                obj[id].run = 2;
            }
        } else
        {
            if (obj[id].run == 2)
            {
                obj[id].speed=obj[id].speed/2+1;
                obj[id].run = 1;
            }
        }
    }
    if (obj[id].speed >= 10) 
    {
        obj[id].old_pos = obj[id].pos;
        obj[id].old_anim = obj[id].anim;
    }
    if (obj[id].mass != 0)
    {
      if (!press(id)) 
      {
          if  (obj[id].state != STATE_JUMP )
          {
              if (obj[id].img != events) obj[id].anim.x = 0;
              obj[id].pos.y+=obj[id].fall;
              obj[id].state = STATE_FALL;
              if (obj[id].fall != 0 && obj[id].fall <= 9) obj[id].fall++;
              if (obj[id].fall == 0) obj[id].fall = obj[id].mass;
              go(id);
          }
      }
      else 
      {
          if (obj[id].fall > 8) obj[id].fall = 0;
          if (obj[id].dir == DIR_ZERO && obj[id].img != events) obj[id].anim.x = 0;
          obj[id].state = STATE_STAY;
      }
    }
    if (obj[id].jump.frame > 0)
    {
        if (obj[id].jump.frame == 1 && id == 255) play_snd(jump);
        obj[id].state = STATE_JUMP;
        if (obj[id].img != events) obj[id].anim.x = 3*obj[id].pos.w;
        obj[id].pos.y-=obj[id].jump.power;
        obj[id].jump.frame++;
        if (hit(id)) obj[id].jump.frame = obj[id].jump.time;
        if (obj[id].jump.frame >= obj[id].jump.time) 
        {
            obj[id].state = STATE_FALL;
            if (obj[id].img != events) obj[id].anim.x = 0;
            obj[id].jump.frame = 0;
            obj[id].fall = 1;
        }
        go(id);
    }
    if (obj[id].mass == 0) obj[id].state = STATE_STAY;
    if (obj[id].state == STATE_STAY && obj[id].dir != DIR_ZERO)
    {
      
        obj[id].state = STATE_WALK;
        if (obj[id].img != events) obj[id].anim.x+=obj[id].anim.w;
        if (obj[id].anim.x > 2*BLOCK_WIDTH && obj[id].img != events) 
            obj[id].anim.x = 0;
        go(id);
    }
    if (obj[id].mass != 0) press(id);
    if (obj[id].pos.x < 0) 
    {
        obj[id].pos.x = 0;
        if (obj[id].AI) obj[id].dir = DIR_RIGHT;
    }
    if (obj[id].pos.y < 0) obj[id].pos.y = 0;
    if (obj[id].pos.x > game->w-obj[id].pos.w)
    { 
        obj[id].pos.x = game->w-obj[id].pos.w;
        if (obj[id].AI) obj[id].dir = DIR_LEFT;
    }
    if (obj[id].pos.y > game->h)
    { 
        if (id != 255) 
        {
            play_snd(click);
            obj[id].vis = 0;
            if (obj[id].type == OBJ_ENEMY) coins+=obj[id].strength*obj[id].AI+1;
        } else 
        {
            play_snd(slap);
            die = 1;
        }
    }
}
