#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include "SGE/sge.h"

#include <math.h>
#define MX 800
#define MY 600

SDL_Surface *screen;
sge_TTFont *font;

/***
    create a move variable 
    and two circle variables initialise to two different centre points
***/
move m1 = {0,0};
circle c1={MX/2-30,MY/2,20,0xFF0000},c2 = {MX/2+10,MY/2,20,0x00FF00};

/***
    This function takes in two circles.
    and calculates distances between centres.
    using the distance function.
    and returns distance
***/
float distance(circle *c1, circle *c2)
{
    float d = (c1->x - c2->x)*(c1->x - c2->x) + (c1->y - c2->y)*(c1->y - c2->y);
    d = sqrt(d);
    return d;
}


void render()
{
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;
      
      /***
          Clear screen
          update circle 1 with m1 move struct
          draw the circle
      ***/
      cls(0);
      update(&c1,m1);         
      circdraw(&c1,&c2);
      
      /***
          Gets distance between two circles
      ***/
      float dist = distance(&c1,&c2);
      if (dist < 40)                 //COLLISION use color - RED
            sge_tt_textoutf( screen, font, 10,MY-20, 255,0,0, 0,0,0, 255, "%f", dist);
      else                           //NO COLLISION Use color - GREEN
            sge_tt_textoutf( screen, font, 10,MY-20, 0,255,0, 0,0,0, 255, "%f", dist);

  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);

  // Tell SDL to update the whole screen
  SDL_Flip(screen);
}




// Entry point
int main(int argc, char *argv[])
{
  init();
  // Main loop: loop forever.
  sge_TTF_Init();
  font = sge_TTF_OpenFont("cour.ttf",30);
  
  while (1)
  {
    // Do The display!
    render();
    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
          m1.kLR = -1;
          break;
        case SDLK_RIGHT:
          m1.kLR = 1;
          break;
        case SDLK_UP:
          m1.kUD = -1;
          break;
        case SDLK_DOWN:
          m1.kUD = 1;
          break;
        }
        break;
        
        case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
          m1.kLR = 0;
          break;
        case SDLK_RIGHT:
          m1.kLR = 0;
          break;
        case SDLK_UP:
          m1.kUD = 0;
          break;
        case SDLK_DOWN:
          m1.kUD = 0;
          break;
        }
        break;
        
      case SDL_QUIT:
        return(0);
      }
    }
  }
  return 0;

}

