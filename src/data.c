#include "global.h"

char temp3[256];

char *getdata(char name[256])
{    
    if (strlen(data))
    {
        sprintf(temp3, "%s/%s", data, name);
        return temp3;
    } else return name;
}
