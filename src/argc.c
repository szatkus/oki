#include "global.h"
#include "conf.h"
#include "fps.h"
#include "okiGL.h"

int check_argc(int *args, char **argc)
{
    char i;
    
    limit = 50;
    enable_fps = 0;
    smooth = 0;
    for (i=0;i<(int)args;i++)
    {
        if (!memcmp(argc[i], "--help", 5) || !memcmp(argc[i], "-h", 2))
        {
            printf("Oki v. %s\n\n", VERSION);
            printf("-fs, --fullscreen   fullscreen mode\n");
            printf("-d, --data DIR      directory with data\n");
            printf("-fps                show FPS\n");
            printf("-s, --smooth        smooth screen (OpenGL)\n");
            printf("-h, --help          this help\n");
            printf("-v, --version       game version\n\n");
            exit(0);
        }
        if (!memcmp(argc[i], "--fullscreen", 12) ||!memcmp(argc[i], "-fs", 3))
            fs = 1;
        if (!memcmp(argc[i], "--data", 6) || !memcmp(argc[i], "-d", 2))
            strcpy(data, argc[i+1]);
        if (!memcmp(argc[i], "--smooth", 8) || !memcmp(argc[i], "-s", 2))
            smooth = 1;
        if (!memcmp(argc[i], "-fps", 4)) enable_fps = 1;
        if (!memcmp(argc[i], "--version", 9) || !memcmp(argc[i], "-v", 2))
        {
            printf("Oki v. %s\n", VERSION);
            printf("04/02/05\n");
            printf("Created by Szatkus\n");
            printf("www.szatkus.tk\n");
            printf("szatkus@op.pl\n");
            exit(0);
        }
    }
}
