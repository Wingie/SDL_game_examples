/***
    Header files
           these header files are required for SDL to operate
           look in the dev-cpp folder on your Hard drive.
           there will be an SDL folder with a bunch of header files
           we link to thise.
   
***/
#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"
#include "SGE/sge.h"
#include <math.h>

/***
    This pointer screen points to the SDL_surface object
    this screen is what is displayed on screen
    and what we are supposed to draw stuff to
***/
SDL_Surface *screen;

/***
    This is the render function.
    This function is our *drawing* functions.
***/
void render()
{
  /*** 
         This statement is hardware dependant. only certain hardware requires it
         LOCKING means nothing else can write to the are of memory
         the screen pointer points to. Avoids errors and memory interlink issues
  ***/
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;

      // This is a function that allows us to draw a pixel onto the screen
      
      _PutPixel(screen,i, MY/2, 0xFFFFFF);

  /***
      Undoes the above SDL_LOCK code. 
      SDL_Flip() is when the changes that we have made to the *screen
      can be seen by us.
  ***/
  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);
  // Tell SDL to update the whole screen
  SDL_Flip(screen);
}




/***

    This function is the main(). 
    Program starts execution from here only.
    
***/
int main(int argc, char *argv[])
{
  init();
  
  /***
      infinite game loop!
  ***/
  while (1)
  {
    // Do The display! : Displays whatever we want to 
    render();
    
    /***
         Event handler for the game.
         Events that happened are returned one at a time by pollevent function
    ***/
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      // event.type is a type of macro constants defined in the SDL header files
      switch (event.type)
      {
      // Means the x button of the window has been pressed.
      case SDL_QUIT:
        return(0);
      }
    }
  }
  return 0;
}




/****  
BELOW CODE IS HOW YOU MUST INDENT YOUR CODE!!

for(something something)
{
 next indent line;
 all code that belongs to the for goes here;
 if(somthing something)
 {
  the code for the if is HERE;
  note a one space indent only;
  dont put additional tabs;
  while(1)
  {
   The while loop runs;
   these lines of code;
   again note the indent levels;
   
  }            
 }
 else
 {
  not this indent level is the same as the above;
  if statement;    
 }
}

****/
