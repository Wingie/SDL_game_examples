struct point
{
      int x;
      int y;
      
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
  int   x, y, xlength, ylength, dx, dy;
  float xslope, yslope;
  xlength = abs(p1.x-p2.x);
  if ((p1.x-p2.x)  < 0) dx = -1;
  if ((p1.x-p2.x) == 0) dx =  0;
  if ((p1.x-p2.x)  > 0) dx = +1;
  ylength = abs(p1.y-p2.y);
  if ((p1.y-p2.y)  < 0) dy = -1;
  if ((p1.y-p2.y) == 0) dy =  0;
  if ((p1.y-p2.y)  > 0) dy = +1;
  if (dy == 0) {
    if (dx < 0)
      for (x=p1.x; x<p2.x+1; x++)
	putpixel(x,p1.y,col);
    if (dx > 0)
      for (x=p2.x; x<p1.x+1; x++)
	putpixel(x,p1.y,col);
  }
  if (dx == 0) {
    if (dy < 0)
      for (y=p1.y; y<p2.y+1; y++)
	putpixel(p1.x,y,col);
    if (dy > 0)
      for (y=p2.y; y<p1.y+1; y++)
	putpixel(p1.x,y,col);
  }
  if ((xlength != 0) && (ylength != 0)) {
    xslope = (float)xlength/(float)ylength;
    yslope = (float)ylength/(float)xlength;
  }
  else {
    xslope = 0.0;
    yslope = 0.0;
  }
  if ((xslope != 0) && (yslope != 0) &&
      (yslope/xslope < 1) && (yslope/xslope > -1)) {
    if (dx < 0)
      for (x=p1.x; x<p2.x+1; x++) {
	y = round (yslope*x);
	putpixel(x,y,col);
      }
    if (dx > 0)
      for (x=p2.x; x<p1.x+1; x++) {
	y = round (yslope*x);
	putpixel(x,y,col);
      }
  }
  else {
    if (dy < 0)
      for (y=p1.x; y<p2.x+1; y++) {
	x = round (xslope*y);
	putpixel(x,y,col);
      }
    if (dy > 0)
      for (y=p2.x; y<p1.x+1; y++) {
	x = round (xslope*y);
	putpixel(x,y,col);
      }
  }
}
