#ifndef _____CELL____H__
#define _____CELL____H_

#include <iostream>
#include <string>
#include "window.h"

class cell{
   char state;
   char square;
   char colour;
   int col;
   int row;
  public:
   cell();
   ~cell();
   void setcell(char state, char square, char color);
   void setcoor(int c, int r);
   char getstate();
   char getsquare();
   char getcolour();
   void draw(Xwindow *window);
};


#endif
