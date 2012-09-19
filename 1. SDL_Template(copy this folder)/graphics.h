

#define COLOR 0xFF00FF     
#define PITCH (screen->pitch / 4)
#include <math.h>

/***
    MX and MY changed here will change the size of the screen.
    the SDL_rect code is to manage clipping: do not change
    the extern SDL_surface *screen is the same global variable in main
***/
#define MX 800
#define MY 600
const SDL_Rect rect = {0,0,MX,MY};
extern SDL_Surface *screen;


struct point
{
      int x;
      int y;   
};

/*** 
     what does this code do?
***/
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

/***
    some variants of putpixel code. 
***/
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

/***
    This funciton must be called when SDL exits.
    so this function is registered in init() by an atexit()
***/
void shutdown()
{
    SDL_FreeSurface(screen);
    SDL_Quit();
}

/***
    This is the init() function that is called my main()
    only after this function is called will SDL function become available.
    If the program closes suddenly, it means that this function has failed!
    check .dll files .lib files and project linking options.
***/
void init()
{

  /***
      First we try and init SDL
  ***/   
  if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

  /*** 
       Register shutdown to be called at exit; makes sure things are
       leaned up when we quit.
  ***/ 
  atexit(shutdown);

  /***
      This function is what sets the screen pointer to the
      initialised SDL screen surface.
      MX and MY are the size of the screen set in the beggining of this file.
  ***/
  screen = SDL_SetVideoMode(MX, MY, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    
  /***
      Some problem. Stop Program.
  ***/
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
    exit(1);
  }

    SDL_WM_SetCaption("Workshop India!", 0);
    /***
        required function to make sure no pixels are written by SGE ouside
        the allowed screen area!
    ***/
    SDL_SetClipRect(screen,&rect);
}

