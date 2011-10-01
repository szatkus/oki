#include <errno.h>
#ifdef UNIX
#include <sys/stat.h>
#endif

#include "global.h"
#include "conf.h"
#include "map.h"

FILE *cfg;

int read_cfg(char def)
{
    signed char ch;
    
    ch = fgetc(cfg);
    if (ch > 0) return ch;
    else return def;
}

int read_cfg2(short int def)
{
    signed short int ch;
    
    ch = fgetc(cfg)*256;
    ch += fgetc(cfg);
    if (ch > 0) return ch;
    else return def;
}

void write_cfg(char ch)
{
    if (ch >= 0) fputc(ch, cfg);
    else fputc(0, cfg);
}

void write_cfg2(short int ch)
{
    if (ch >= 0) 
    {
        fputc(ch/256, cfg);
        fputc(ch-(ch/256)*256, cfg);
    }
    else 
    {
        fputc(0, cfg);
        fputc(0, cfg);
    }
}

void load_cfg()
{
#ifdef UNIX
    sprintf(temp, "%s/.oki", getenv("HOME"));
    mkdir(temp, S_IRWXU);
    sprintf(temp, "%s/.oki/oki_cfg", getenv("HOME"));
    cfg = fopen(temp, "a+b");
#endif
#ifdef WIN32
    cfg = fopen("oki.cfg", "a+b");
#endif
    fs = read_cfg(0);
    left = read_cfg2(SDLK_LEFT);
    up = read_cfg2(SDLK_UP);
    right = read_cfg2(SDLK_RIGHT);
    down = read_cfg2(SDLK_DOWN);
    A = read_cfg2(SDLK_z);
    B = read_cfg2(SDLK_x);
    mapset = read_cfg(0);
    fclose(cfg);
}

void save_cfg()
{
#ifdef UNIX
    sprintf(temp, "%s/.oki", getenv("HOME"));
    mkdir(temp, 0);
    sprintf(temp, "%s/.oki/oki_cfg", getenv("HOME"));
    cfg = fopen(temp, "wb");
#endif
#ifdef WIN32
    cfg = fopen("oki.cfg", "wb");
#endif
    write_cfg(fs);
    write_cfg2(left);
    write_cfg2(up);
    write_cfg2(right);
    write_cfg2(down);
    write_cfg2(A);
    write_cfg2(B);
    write_cfg(mapset);
    fclose(cfg);
}
