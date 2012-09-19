#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include "SGE/sge.h"
#include "SDL/SDL_ttf.h"
#include <math.h>
#define MX 800
#define MY 600

SDL_Surface *screen;

point p1 = {MX/2,MY/2};
point p2 = {0,0};


void render()
{
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;
      
      //LINE
      sge_Line(screen, 0, 0, MX/2, MY/2, 0xFF00FF);
      //LINE(AA)
      sge_Line(screen, MX, 0, MX/2, MY/2, 0xFF0000);
      //LINE(MC)
      sge_mcLine(screen, 0, MY, MX/2, MY/2, 255,0,0,0,0,255);
      //REctangl border
      sge_Rect(screen, MX/2, MY/2, MX-2, MY-2, 0x00FF00);
      //FIlled Rectangle
      sge_FilledRect(screen, MX/2+20, MY/2+20, MX-20, MY-20, 0x7A150E);
      //Circle
      sge_Circle(screen, MX/2, MY/2, 250, 0x0000FF);
      //Filled circle
      sge_FilledCircle(screen, MX/2-200, MY/2-30, 50, 0xFFFFFF);
      //Ellipse
      sge_Ellipse(screen, MX/2, MY/2, 50,20, 0xF0FFFF);
      
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
          //dot.gKeyLeft = 1;
          p1 = update(p1,-1,0);
          break;
        case SDLK_RIGHT:
          //dot.gKeyRight = 1;
          p1 = update(p1,1,0);
          break;
        case SDLK_UP:
          //dot.gKeyUp = 1;
          p1 = update(p1,0,-1);
          break;
        case SDLK_DOWN:
          //dot.gKeyDown = 1;
          p1 = update(p1,0,1);
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

