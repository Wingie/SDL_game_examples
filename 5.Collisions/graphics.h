extern SDL_Surface *screen;
#include "SGE/sge.h"
#define COLOR 0xFF00FF
#define PITCH (screen->pitch / 4)
#define MX 800
#define MY 600
const SDL_Rect rect = {0,0,MX,MY};
#include <math.h>
struct point
{
      int x;
      int y;   
};
/***
    This structure defines a circle to be drawn onto the screen.
***/
struct circle
{
       int x;
       int y;
       int r;
       Uint32 col;
};

/***
    This structure is required for the moving logic
***/
struct move{
int kLR;
int kUD; 
};

/***
    This code updates The circle following the move algorithm. It just
    adjusts the circle centre point x,y following the move logic
***/
void update(circle *p,move m)
{
 p->x += m.kLR;
 p->y += m.kUD;
 if(p->x > MX)
        p->x = MX-5;
 if(p->y > MY)
        p->y = MY-5;
 if(p->x < 0)
        p->x = 5;
 if(p->y < 0)
        p->y = 5;
}

/***
    This funciton draws both the circles onto the screen
***/
void circdraw(circle *c1, circle *c2)
{
 sge_Circle(screen, c1->x, c1->y, c1->r,c1->col); 
 sge_Circle(screen, c2->x, c2->y, c2->r,c2->col);    
}

point update(point p, int x = 0, int y = 0)
{
 p.x += x;
 p.y += y;
 if(p.x > MX)
        p.x = MX;
 if(p.y > MY)
        p.y = MY;
 return p;
}


void putpixel(point p, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = p.y * (screen->pitch / 4);
  ptr[lineoffset + p.x] = color;
}

void putpixel(int x,int y, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4);
  ptr[lineoffset + x] = color;
}

void shutdown()
{
    SDL_FreeSurface(screen);
    SDL_Quit();
}


void init()
{
// Initialize SDL's subsystems - in this case, only video.

  if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  // Register shutdown to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(shutdown);

  // Attempt to create a 640x480 window with 32bit pixels.
  screen = SDL_SetVideoMode(MX, MY, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    
  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }
  //Hide mouse cursor
  //SDL_ShowCursor(0);
  // Set the title of our window.
    SDL_WM_SetCaption("WWS", 0);
    SDL_SetClipRect(screen,&rect);
}


/***
    This function clears the screen,
***/
void cls(int c = 0)
{
  int i, j;
  for (i = 0; i < MX; i++)
  {  
      for (j = 0; j < MY; j++)
        putpixel(i,j,c);
  }
}

