#include "global.h"
#include "MEmap.h"
#include "conf.h"
#include "okiGL.h"

int check_argc(int *args, char **argc)
{
    int i;
    
    strcpy(map, "new_map.map");
    strcpy(data, "");
    new_map = 1;
    smooth = 0;
    for (i=0;i<(int)args;i++)
    {
        if (!memcmp(argc[i], "--help", 5) || !memcmp(argc[i], "-h", 2))
        {
            printf("Oki - map editor v. %s\n\n", VERSION);
            printf("-fs, --fullscreen   fullscreen mode\n");
            printf("-d, --data DIR      directory with data\n");
            printf("-m, --map MAP       load map\n");
            printf("-n, --new MAP       create new map\n");
            printf("-s, --smooth        smooth screen (OpenGL)\n");
            printf("-h, --help          this help\n");
            printf("-v, --version       game version\n\n");
            exit(0);
        }
        if (!memcmp(argc[i], "--fullscreen", 12) ||!memcmp(argc[i], "-fs", 3))
            fs = 1;
        if (!memcmp(argc[i], "--data", 6) || !memcmp(argc[i], "-d", 2))
            strcpy(data, argc[i+1]);
        if (!memcmp(argc[i], "--map", 5) || !memcmp(argc[i], "-m", 2) ||
            !memcmp(argc[i], "--new", 5) || !memcmp(argc[i], "-n", 2))
        {
            strcpy(map, argc[i+1]);
            new_map = !memcmp(argc[i], "--new", 5) || !memcmp(argc[i], "-n", 2);
        }
        if (!memcmp(argc[i], "--smooth", 8) || !memcmp(argc[i], "-s", 2))
            smooth = 1;
        if (!memcmp(argc[i], "--version", 9) || !memcmp(argc[i], "-v", 2))
        {
            printf("Oki - map editor v. %s\n", VERSION);
            printf("04/02/05\n");
            printf("Created by Szatkus\n");
            printf("www.szatkus.tk\n");
            printf("szatkus@op.pl\n");
            exit(0);
        }
    }
}
