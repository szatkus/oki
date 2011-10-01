#include "SDL_image.h"

#include "global.h"
#include "image.h"
#include "MEmap.h"
#include "MErefresh.h"
#include "MEevent.h"
#include "MEtext.h"

void load_map(char *filename)
{
    FILE *file;
    char ch;
    int width, height, x, y;
    char header[3];
    
    file = fopen(filename, "rb");
    fread(header, sizeof(header), 1, file);
    width = fgetc(file);
    height = fgetc(file);
    level.height = height-1;
    level.width = width-1;
    fseek(file, 11, 1);
    for (y=0;y<=level.height;y++)
    {
        for (x=0;x<=level.width;x++)
        {
            level.map[x][y].tile = fgetc(file);
            while (level.map[x][y].tile >= 64)
            {
                level.map[x][y].type++;
                level.map[x][y].tile-=64;
            }
            if ((level.map[x][y].tile == 17 || level.map[x][y].tile == 25)
                 && level.map[x][y].type == 3)
            {
                ch = fgetc(file);
                fgets(text[x][y], ch, file);
            }
        }
    }
    fclose(file);
}

void save_map(char *filename)
{
    FILE *file;
    char ch;
    int width, height, x, y;
    char header[3];
    
    SDL_WM_SetCaption("Oki - map editor [Saving]", "Oki - map editor");
    file = fopen(filename, "wb");
    fputs("MAP", file);
    fputc(level.width+1, file);
    fputc(level.height+1, file);
    for (x=1;x<=11;x++) fputc(0, file);
    for (y=0;y<=level.height;y++)
    {
        for (x=0;x<=level.width;x++)
        {
            fputc(level.map[x][y].tile+level.map[x][y].type*64, file);
            if ((level.map[x][y].tile == 17 || level.map[x][y].tile == 25) && 
                level.map[x][y].type == 3)
            {
                fputc(strlen(text[x][y])+1, file);
                fputs(text[x][y], file);
            }
        }
    }
    fclose(file);
    SDL_Delay(200);
    SDL_WM_SetCaption("Oki - map editor", "Oki - map editor");
}

void draw_tile(int x, int y, int tiletype, int tile, SDL_Surface *target)
{
    SDL_Surface *image;
    SDL_Rect rect, rect2;
    
    if (tiletype != 3)
    {
        cut_image(tileset, target, tile, 8, x*BLOCK_WIDTH, 
                  y*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT);
    } else
    {
       cut_image(tileset, target, 0, 8, x*BLOCK_WIDTH, y*BLOCK_HEIGHT, BLOCK_WIDTH,
                 BLOCK_HEIGHT);
                    image = events;
                    rect.x = 7*BLOCK_WIDTH;
                    rect.y = 7*BLOCK_HEIGHT;
                    rect.w = BLOCK_WIDTH;
                    rect.h = BLOCK_HEIGHT;
                    switch (tile)
                    {
                        case 0:
                            image = monster[0];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 1:
                            image = events;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 2:
                            image = events;
                            rect.x = 10;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 3:
                            image = events;
                            rect.x = 30;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 4:
                            image = events;
                            rect.x = 0;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 5:
                            image = events;
                            rect.x = 10;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 6:
                            image = events;
                            rect.x = 20;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 7:
                            image = monster[1];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 8:
                            image = events;
                            rect.x = 50;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 9:
                            image = events;
                            rect.x = 60;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 10:
                            image = events;
                            rect.x = 70;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 11:
                            image = events;
                            rect.x = 30;
                            rect.y = 10;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 12:
                            image = events;
                            rect.x = 0;
                            rect.y = 20;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 13:
                            image = events;
                            rect.x = 10;
                            rect.y = 20;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 14:
                            image = events;
                            rect.x = 20;
                            rect.y = 20;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 15:
                            image = events;
                            rect.x = 30;
                            rect.y = 20;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 16:
                            image = monster[2];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = 2*BLOCK_WIDTH;
                            rect.h = 2*BLOCK_HEIGHT;
                        break;
                        case 17:
                            image = events;
                            rect.x = 4*BLOCK_WIDTH;
                            rect.y = 2*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 18:
                            image = monster[3];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 19:
                            image = monster[4];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 20:
                            image = tileset;
                            rect.x = 4*BLOCK_WIDTH;
                            rect.y = 2*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 21:
                            image = events;
                            rect.x = 6*BLOCK_WIDTH;
                            rect.y = 2*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 22:
                            image = events;
                            rect.x = 7*BLOCK_WIDTH;
                            rect.y = 2*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 23:
                            image = monster[5];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 24:
                            image = events;
                            rect.x = BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 25:
                            image = man;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 26:
                            image = oke_img;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 27:
                            image = monster[6];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 28:
                            image = events;
                            rect.x = 2*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 29:
                            image = monster[7];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 30:
                            image = events;
                            rect.x = 3*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 31:
                            image = events;
                            rect.x = 4*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 32:
                            image = monster[8];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 33:
                            image = monster[9];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = 4*BLOCK_WIDTH;
                            rect.h = 4*BLOCK_HEIGHT;
                        break;
                        case 34:
                            image = torch;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 35:
                            image = monster[10];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 36:
                            image = monster[10];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 37:
                            image = events;
                            rect.x = 5*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 38:
                            image = events;
                            rect.x = 6*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 39:
                            image = rock;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = 3*BLOCK_WIDTH;
                            rect.h = 3*BLOCK_HEIGHT;
                        break;
                        case 40:
                            image = events;
                            rect.x = 7*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 41:
                            image = events;
                            rect.x = 0;
                            rect.y = 4*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = 2*BLOCK_HEIGHT;
                        break;
                        case 42:
                            image = events;
                            rect.x = BLOCK_WIDTH;
                            rect.y = 4*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 43:
                            image = events;
                            rect.x = 2*BLOCK_WIDTH;
                            rect.y = 4*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 44:
                        case 45:
                        case 46:
                        case 47:
                            image = monster[12];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 48:
                            image = monster[5];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 49:
                            image = glass;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH*2;
                            rect.h = BLOCK_HEIGHT*4;
                        break;
                        case 50:
                            image = computer;
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 51:
                            image = monster[13];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 52:
                            image = monster[13];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 53:
                            image = monster[14];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = 2*BLOCK_WIDTH;
                            rect.h = 2*BLOCK_HEIGHT;
                        break;
                        case 54:
                            image = monster[14];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = 2*BLOCK_WIDTH;
                            rect.h = 2*BLOCK_HEIGHT;
                        break;
                        case 55:
                            image = events;
                            rect.x = 7*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 56:
                            image = events;
                            rect.x = 7*BLOCK_WIDTH;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 57:
                            image = events;
                            rect.x = 3*BLOCK_WIDTH;
                            rect.y = 4*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 58:
                            image = events;
                            rect.x = 4*BLOCK_WIDTH;
                            rect.y = 4*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 59:
                            image = events;
                            rect.x = 5*BLOCK_WIDTH;
                            rect.y = 4*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 60:
                            image = monster[11];
                            rect.x = 0;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT+5;
                        break;
                        case 61:
                            image = events;
                            rect.x = 0;
                            rect.y = 3*BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 62:
                            image = events;
                            rect.x = 4*BLOCK_WIDTH;
                            rect.y = BLOCK_HEIGHT;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                        case 63:
                            image = events;
                            rect.x = 20;
                            rect.y = 0;
                            rect.w = BLOCK_WIDTH;
                            rect.h = BLOCK_HEIGHT;
                        break;
                    }
                    rect2.x = x*BLOCK_WIDTH;
                    rect2.y = y*BLOCK_HEIGHT;
                    rect2.w = BLOCK_WIDTH;
                    rect2.h = BLOCK_HEIGHT;
                    SDL_BlitSurface(image, &rect, target, &rect2);
                }
}

void show_map()
{
    int x, y;
    
    for (y=level.height;y>=0;y--)
    {
        for (x=level.width;x>=0;x--)
        {
            if (level.map[x][y].type == type || mode)
            {
                draw_tile(x, y, level.map[x][y].type,
                          level.map[x][y].tile, game);
            }
        }
    }
}
