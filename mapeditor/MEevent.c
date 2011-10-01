#include "SDL.h"
#include "SDL_thread.h"

#include "global.h"
#include "MEmove.h"
#include "MEevent.h"
#include "MEmap.h"
#include "MErefresh.h"
#include "MEtext.h"

void check_event()
{
    SDL_Event event;
    SDL_Rect rect;
    int change;
    
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
              case SDL_ACTIVEEVENT:
                if (!event.active.gain)
                {
                  cursor.x = 8;
                  cursor.y = 6;
                }
              break;
              case SDL_KEYDOWN:
                if (text_mode.work)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_BACKSPACE:
                            text[text_mode.x][text_mode.y]
                                [strlen(text[text_mode.x][text_mode.y])-1] = 0;
                        break;
                        case SDLK_RETURN: text_mode.work = 0; break;
                        case SDLK_LSHIFT:
                        case SDLK_RSHIFT:
                          shift = 1;
                        break;
                    }
                    if (shift)
                    {
                      
                      switch (event.key.keysym.sym)
                      {
                        
                        case SDLK_QUOTE: event.key.keysym.sym = SDLK_QUOTEDBL; break;
                        case SDLK_1: event.key.keysym.sym = SDLK_EXCLAIM; break;
                        case SDLK_2: event.key.keysym.sym = SDLK_AT; break;
                        case SDLK_3: event.key.keysym.sym = SDLK_HASH; break;
                        case SDLK_4: event.key.keysym.sym = SDLK_DOLLAR; break;
                        case SDLK_5: event.key.keysym.sym = 37; break;
                        case SDLK_6: event.key.keysym.sym = SDLK_CARET; break;
                        case SDLK_7: event.key.keysym.sym = SDLK_AMPERSAND; break;
                        case SDLK_8: event.key.keysym.sym = SDLK_ASTERISK; break;
                        case SDLK_9: event.key.keysym.sym = SDLK_LEFTBRACKET; break;
                        case SDLK_0: event.key.keysym.sym = SDLK_RIGHTBRACKET; break;
                        case SDLK_COMMA: event.key.keysym.sym = SDLK_LESS; break;
                        case SDLK_EQUALS: event.key.keysym.sym = SDLK_PLUS; break;
                        case SDLK_PLUS: event.key.keysym.sym = SDLK_EQUALS; break;
                        case SDLK_PERIOD: event.key.keysym.sym = SDLK_GREATER; break;
                        case SDLK_SLASH: event.key.keysym.sym = SDLK_QUESTION; break;
                        case SDLK_SEMICOLON: event.key.keysym.sym = SDLK_COLON; break;
                      }
                    }
                    if (event.key.keysym.sym >= SDLK_SPACE &&
                        event.key.keysym.sym <= SDLK_z)
                    {
                        sprintf(temp, "%s%c", text[text_mode.x][text_mode.y],
                                event.key.keysym.sym);
                        strcpy(text[text_mode.x][text_mode.y], temp);
                    }
                    event.key.keysym.sym = 0;
                }
                switch (event.key.keysym.sym)
                {
                    case SDLK_RCTRL: fast = 1; break;
                    case SDLK_LSHIFT: shift = 1; break;
                    case SDLK_RSHIFT: shift = 1; break;
                    case SDLK_a:
                        tile--;
                        if (tile<0) tile = 63;
                    break;
                    case SDLK_d:
                        tile++;
                        if (tile>63) tile = 0;
                    break;
                    case SDLK_w:
                        type--;
                        if (type<0) type = 3;
                        if (!mode) refresh_static();
                    break;
                    case SDLK_x:
                        type++;
                        if (type>3) type = 0;
                        if (!mode) refresh_static();
                    break;
                    case SDLK_q:
                        mode = !mode;
                        refresh_static();
                    break;
                    case SDLK_l:
                        list = !list;
                    break;
                    case SDLK_t:
                        if (level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                     [camera.y/BLOCK_HEIGHT+cursor.y].type == 3 &&
                            (level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                      [camera.y/BLOCK_HEIGHT+cursor.y].tile == 17 ||
                             level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                      [camera.y/BLOCK_HEIGHT+cursor.y].tile == 25))                       {
                            text_mode.work = 1;
                            text_mode.x = camera.x/BLOCK_WIDTH+cursor.x;
                            text_mode.y = camera.y/BLOCK_HEIGHT+cursor.y;
                        }
                    break;
                }
                if (event.key.keysym.sym == SDLK_s) save_map(map);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                  event.type = SDL_QUIT;
                  SDL_PushEvent(&event);
                }
            break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_RCTRL: fast = 0; break;
                    case SDLK_LSHIFT: shift = 0; break;
                    case SDLK_RSHIFT: shift = 0; break;
                }
            break;
                case SDL_MOUSEMOTION:
                    #ifdef OPENGL
                    event.motion.x /= 5;
                    event.motion.y /= 5;
                    #endif
                    cursor.x = event.motion.x/BLOCK_WIDTH;
                    cursor.y = event.motion.y/BLOCK_HEIGHT;
                    if (event.motion.state == SDL_BUTTON_LEFT && (!list ||
                        cursor.x >= 8 || cursor.y >= 8))
                    {
                        level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                 [camera.y/BLOCK_HEIGHT+cursor.y].type = type;
                        level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                 [camera.y/BLOCK_HEIGHT+cursor.y].tile = tile;
                        draw_tile(camera.x/BLOCK_WIDTH+cursor.x, 
                                  camera.y/BLOCK_HEIGHT+cursor.y, type, tile, game);
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                      case SDL_BUTTON_LEFT:
                        
                        if (!list || cursor.x >= 8 || cursor.y >= 8)
                        {
                          level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                   [camera.y/BLOCK_HEIGHT+cursor.y].type = type;
                          level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                   [camera.y/BLOCK_HEIGHT+cursor.y].tile = tile;
                          draw_tile(camera.x/BLOCK_WIDTH+cursor.x, 
                                    camera.y/BLOCK_HEIGHT+cursor.y, type, tile, game);
                          refresh_static();
                          SDL_WM_SetCaption("Oki - map editor[Modifed]", 
                                            "Oki - map editor[Modifed]");
                         } else
                         {
                           tile = cursor.x+cursor.y*8;
                         }
                      break;
                      case SDL_BUTTON_MIDDLE:
                        if (cursor.x > 8 && cursor.y == 0)
                        {
                          if (cursor.x > 14)
                          {
                            list = !list;
                          } else
                          {
                            type++;
                            if (type > 3) type = 0;
                          }
                        } else
                        {
                          mode = !mode;
                          refresh_static();
                        }
                      break;
                      case SDL_BUTTON_RIGHT:
                        if (!list || cursor.x >= 8 || cursor.y >= 8)
                        {
                          change = type != level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                           [camera.y/BLOCK_HEIGHT+cursor.y].type;
                          type = level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                          [camera.y/BLOCK_HEIGHT+cursor.y].type;
                          tile = level.map[camera.x/BLOCK_WIDTH+cursor.x]
                                          [camera.y/BLOCK_HEIGHT+cursor.y].tile;
                          if (change) refresh_static();
                        } else
                         {
                           tile = cursor.x+cursor.y*8;
                         }
                      break;
                      case SDL_BUTTON_WHEELDOWN:
                        tile--;
                        if (tile<0) tile = 63;
                      break;
                      case SDL_BUTTON_WHEELUP:
                        tile++;
                        if (tile>63) tile = 0;
                      break;
                    }
                break;
                case SDL_QUIT:
                    show_quit = 1;
                    event.type = 0;
                    refresh();
                    while (event.type != SDL_KEYDOWN)
                    {
                        SDL_WaitEvent(&event);
                        if (event.type == SDL_KEYDOWN) 
                        {
                            if (event.key.keysym.sym == SDLK_y) save_map(map);
                            if (event.key.keysym.sym == SDLK_y || 
                                event.key.keysym.sym == SDLK_n)
                            {
                                exit(0);
                            }
                        }
                    }
                    show_quit = 0;
                break;
            } 
        }
        move();
    }
}

