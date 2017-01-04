#include "cell.h"
#include <iostream>
#include <string>
enum {White=0, Black, Red, Green, Blue};


using namespace std;

cell::cell(){};
cell::~cell(){};


void cell::setcell(char state, char square, char color){
    this->state=state;
    this->square=square;
    this->colour=color;
}

void cell::setcoor(int r, int c){
     this->row=r;
     this->col=c;
}



char cell::getstate(){return this->state;}


char cell:: getsquare(){
     return this->square;}

char cell::getcolour(){
     return this->colour;
 }

void cell::draw(Xwindow *window){
      int dimension=50;
      if (window){
		window->fillRectangle(col*dimension, row*dimension, dimension, dimension, colour-'0');
     int x = col * dimension;
     int y = row * dimension;
     if(this->square=='b'){
	int offset = 10;
	int size = dimension - (2 * offset);
	window->fillRectangle(x + offset, y + offset, size, size, 5);
      }
     if(this->square=='p'){
        int width = dimension / 3;
	int length = dimension;
	int offset = dimension / 3;
	window->fillRectangle(x+offset, y, width, length, 6);
	window->fillRectangle(x, y+offset, length, width, 6);
     }
     if(this->square=='v'){
        int stripeWidth = 10;
	window->fillRectangle((x + (stripeWidth * 0)), y, stripeWidth, dimension, colour-'0');
	window->fillRectangle((x + (stripeWidth * 1)), y, stripeWidth, dimension, 6);

	window->fillRectangle((x + (stripeWidth * 2)), y, stripeWidth, dimension, colour-'0');
	window->fillRectangle((x + (stripeWidth * 3)), y, stripeWidth, dimension, 6);

	window->fillRectangle((x + (stripeWidth * 4)), y, stripeWidth, dimension, colour-'0');
     }
     if(this->square=='h'){
        int stripeHeight = 10;
	window->fillRectangle(x, y, dimension, stripeHeight, colour);
	window->fillRectangle(x, (y + stripeHeight), dimension, stripeHeight, 6);

	window->fillRectangle(x, (y + (stripeHeight*2)), dimension, stripeHeight, colour-'0');
	window->fillRectangle(x, (y + (stripeHeight*3)), dimension, stripeHeight, 6);

	window->fillRectangle(x, (y + (stripeHeight*4)), dimension, stripeHeight, 6); 
     }
     if(state=='l'){
	int width = 4;
	int offset = 2;
	int length = dimension - (2 * offset);	
	window->fillRectangle(x+offset, y+offset, width, length, 1);
	window->fillRectangle(x+offset, y+offset, length, width, 1);
	window->fillRectangle(x+offset, y+dimension-width-offset, length, width, 1);
	window->fillRectangle(x+dimension-width-offset, y+offset, width, length, 1);}
}
}
