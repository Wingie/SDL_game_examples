extern SDL_Surface *screen;
#define COLOR 0xFF00FF
#define PITCH (screen->pitch / 4)
#define MX 800
#define MY 600

#include <math.h>
struct point
{
      int x;
      int y;
      
};

/**
   This structure required for the movement code.\
   kLR: -1 means Left; 1 means Right; 0 means No movement
   kUD: -1 means Down; 1 means Up;    0 means No movement
**/
struct move{
int kLR;
int kUD; 
};

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


void drawline(point p1, point p2, int col=COLOR) 
{
  
  sge_Line(screen,p1.x,p1.y,p2.x,p2.y,COLOR);
  
}

void cls(int c = 0)
{
  int i, j;
  for (i = 0; i < MX; i++)
  {  
      for (j = 0; j < MY; j++)
        putpixel(i,j,c);
  }
}
