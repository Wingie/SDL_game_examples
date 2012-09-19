#include <stdlib.h>
#include "SDL/SDL.h"
#include "SGE/sge.h"
#include "graphics.h"
#include <math.h>
#define FPS 100
#define MX 800
#define MY 600


SDL_Surface *screen;        // SDL Screen
point p2 = {MX/2,MY/2};     // Point 2 initialized to MX/2 and MY/2
point p1 = {0,0};           // Point 1 initialized to centre
move m1 = {0,0}, m2 = {0,0,};  // Two move structures for both points

void init();                   //Prototype for init()

/***
     This function takes a pointer to a point struct and a move sruct
     it updates the point co-ords according to their move variables.
     move variables are updated in the keyboard loop
     The code also has to make sure, the point doesnt leave the screen.
     The last 4 if statements take care of that.
****/
void update(point *p,move m)
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


void render()
{
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;
   
   //CLearing the screen with black   
   cls(0);   
   //updating p1 with m1; noe we are passing a pointer to p1
   update(&p1,m1); 
   
   sge_AALine(screen,p1.x,p1.y,p2.x,p2.y,0xFF0000);
   putpixel(p1,COLOR);  
   //putpixel(p2,COLOR);   
  
  // Unlock if needed
  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);
    
  // Tell SDL to update the whole screen
  SDL_Flip(screen);
}

void shutdown()
{
    SDL_FreeSurface(screen);
    SDL_Quit();
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
      //event.type holds information about what type of event happened.    
      switch (event.type)
      {
      //This case will be true, when a key is pressed down.
      case SDL_KEYDOWN:
        //Here we need to check which key has been pressed.   
        switch (event.key.keysym.sym)
        {
        //update the corresponding move variable to correct number
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
        
        // This case will be true whent the key is released
        case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
       //update the corresponding move variable to 0. Stopping movement
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
         
}
