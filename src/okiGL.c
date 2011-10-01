#include "global.h"
#include "okiGL.h"
#include "SDL_rotozoom.h"

void show_screen()
{
    #ifndef OPENGL
    int x, y;
    SDL_Rect rect;
    rect.w = SCALE;
    rect.h = SCALE;
    for (y = 0; y < screen->h; y++)
    {
	    for (x = 0; x < screen->w; x++)
	    {
			rect.x = x*SCALE;
			rect.y = y*SCALE;
			SDL_FillRect(screen2, &rect, *(Uint32*)(screen->pixels+x*3+y*screen->w*3) & 0x00ffffff);
		}
	}
    SDL_UpdateRect(screen2, 0, 0, 0, 0);
    #else
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, screen->w, screen->h, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, screen->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (!smooth) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    if (darkness) glColor3f(1.0f/darkness, 1.0f/darkness, 1.0f/darkness);
    else glColor3f(1, 1, 1);
    glTexCoord2f(0, 0.9375);
    glVertex2f(-1, -1);
    glTexCoord2f(0, 0);
    glVertex2f(-1, 1);
    glTexCoord2f(0.625, 0);
    glVertex2f(1, 1);
    glTexCoord2f(0.625, 0.9375);
    glVertex2f(1, -1);
    glEnd();
    SDL_GL_SwapBuffers();
    #endif
}
