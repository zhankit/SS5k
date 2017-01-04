#ifndef __board__H__
#define __board__H__

#include <iostream>
#include "level.h"
#include "window.h"
#include <string>
#include <set>

class board{
    cell **grid;
    lev *celg;
    Xwindow *window;
  //stores the current and max level
    int level;
    std::string inputfile;
    int movesremain;
    int maxLevel;
    int score;
    int startscore;
    int highscore;
    int seed;
    bool textMode;
    bool useFile;
    int deletcell;
  //variables to keep track of where in the input file we're reading from
    std::string seq;
    int seqposition;

   //private function//
   void cleargrid();
   bool noLocked();
   void swapgrid(cell *ab, cell*cd);
   void drop();
   void fillgrid();
   bool hasmatch(int r, int c);
   int Leftmatches(int row, int col);
   int Rightmatches(int row, int col);
   int Upmatches(int row, int col);
   int Downmatches(int row, int col);
   bool psychedelic(int row, int col);
   bool upright(int row, int col);
   bool lateral(int row, int col);
   bool basic(int row, int col);
   bool unstable(int row, int col);
   bool matchexist();
   int exp(int num, int chain);
   void deletegrid(int x, int y, int z, int num);
   int getpoints(int squares, int chain);
    //chain reaction
   void action();
   void draw();
   
   
   // check swap
    bool isvalidswap(int r,int c,int direction);
    bool isamatch(char color, int r ,int c,int direction);

    // check validcoor
    bool InBound(int x,int y);


   // squaregenerator
    void createlevel0();
    void createlevel1();
    void createlevel2();

public:
    // Ctor
     board(bool textMode,int seed, std::string inputfile, bool useFile,int startLevel);
     void changefile(std::string newfile);
     void setwindow(Xwindow *window);
    // Dtor
    ~board();
    void init();
    void swap(int x,int y,int direction);
    std::string hint();
    void scramble();
    void levelup();
    void leveldown();
    void restart();
    friend std::ostream &operator<<(std::ostream &out, board &b);

};


#endif
