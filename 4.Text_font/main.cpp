#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include "SGE/sge.h"
#include <string>
#include <iostream>
#include <math.h>
#define MX 800
#define MY 600
using namespace std;
SDL_Surface *screen;
point p1 = {MX/2,MY/2};
point p2 = {0,0};

/** 
    This is the global font variable for the font engine.
**/
sge_TTFont *font;



void render()
{
     static int i = 0;
     /***
         This function is like printf!
         screen - SDL screen where the font must be drawn
         font - the global font object that is the result of the font open function
         10,400 - x and y position of leftmost part of the font
         0,200,100 - R,G,B values for the FONT
         0,0,0 - R,G,B values for Background
         155 - transparency of text (0 is invisible - 255 is opaque)
     ***/
     sge_tt_textoutf( screen, font, 10,400, 0,200,100, 0,0,0, 255, "Testing: %d", i++ );
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;
    SDL_Delay(500);
      // Only text can be sent -  no variables. - (screen, font,"HELLO",x,y, forecolor, backcolor, opacity)
    sge_tt_textout( screen, font,"HELLO", 10,100, 0xFFFFFF, 0, 255);
    SDL_Delay(100);
    sge_tt_textout( screen, font,"WORLD", 220,100, 0xFFFFFF, 0, 255);
    SDL_Delay(100);
    sge_tt_textout( screen, font,"!!!!", 420,100, 0xFFFFFF, 0, 255);
    SDL_Delay(500);
    cls();
    SDL_Delay(500);
      
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

  /***
      These two lines initialise the FOnt Engine.
      They can also be put inside the init(); too
  ***/
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

      case SDL_QUIT:
        return(0);
      }
    }
  }
  return 0;

}

