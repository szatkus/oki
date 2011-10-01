#include "SDL.h"

#include "global.h"
#include "game.h"
#include "objects.h"
#include "map.h"

FILE *save;

int read_save(char def)
{
    signed char ch;
    
    ch = fgetc(save);
    if (ch > 0) return ch;
    else return def;
}

void write_save(char ch)
{
    if (ch >= 0) fputc(ch, save);
    else fputc(0, save);
}

void save_game()
{
#ifdef UNIX
    sprintf(temp, "%s/.oki", getenv("HOME"));
    mkdir(temp, 0);
    sprintf(temp, "%s/.oki/%s_save", getenv("HOME"), maplist[mapset]);
    save = fopen(temp, "wb");
#endif
#ifdef WIN32
    sprintf(temp, "maps/%s/save", maplist[mapset]);
    save = fopen(temp, "wb");
#endif
    write_save(progress);
    write_save(coins);
    write_save(lifes);
    write_save(oki->speed);
    write_save(oki->jump.power);
    write_save(oki->strength);
    write_save(oki->run);
    write_save(oki->jump.time);
    write_save(oki->HP);
    write_save(oki->shoot);
    fclose(save);
}

void load_game()
{
#ifdef UNIX
    sprintf(temp, "%s/.oki", getenv("HOME"));
    mkdir(temp, 0);
    sprintf(temp, "%s/.oki/%s_save", getenv("HOME"), maplist[mapset]);
    save = fopen(temp, "a+b");
#endif
#ifdef WIN32
    sprintf(temp, "maps/%s/save", maplist[mapset]);
    save = fopen(temp, "a+b");
#endif
    progress = read_save(0);
    coins = read_save(0);
    lifes = read_save(2);
    oki->speed = read_save(3);
    oki->jump.power = read_save(5);
    oki->strength = read_save(0);
    oki->run = read_save(0);
    oki->jump.time = read_save(5);
    oki->HP = read_save(0);
    oki->shoot = read_save(0);
    fclose(save);
}
