#ifndef __LEVEL_H_
#define _LEVEL_H_
#include "cell.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


class lev{
   int level;
   int seed;
   cell *ab;
   public:
    std::string levelonesequence;
    int levelonecounter;
    lev(int seed);
    ~lev();
    void updatelevel(int level);
    void generate(cell *ab);
};

#endif
