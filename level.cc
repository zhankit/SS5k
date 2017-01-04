#include "level.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;



lev::lev(int seed){
    // Set seed
    if (seed == -1) {
        srand(time(NULL));
    }else {
        srand(seed);
    }
   this->seed=seed;
   levelonecounter=-1;
   levelonesequence="";}

lev::~lev(){}


void lev::generate(cell *cd){
     this->ab=cd;
     string s="___";
      int x;
      if(levelonecounter !=-1){
          int num=levelonesequence.length();
          if(levelonecounter >= num){
            levelonecounter=0;
          }
          s[2]=levelonesequence[levelonecounter];
          levelonecounter++;
        }
     else{
      if(level==1){
            x=rand()%12+1;
            //choose colour base on the probability
            if(x==1 || x==2 || x==3){
              s[2]='0';
                   }
             if(x==4 || x==5 || x==6){
                  s[2]='1';
             }
            if(x==7 || x==8){
              s[2]='2';
               }
             if(x==9 || x==10){
               s[2]='3';
                }
              if(x==11){
               s[2]='4';
              }
              if(x==12){
                s[2]='5';}
      }
      else if(level==2){
          x=rand()%6+1;
            //choose colour base on the probability
                  if(x==1){
                  s[2]='0';
                   }
                  if(x==2){
                   s[2]='1';
                  }
                  if(x==3){
                  s[2]='2';
                  }
                  if(x==4){
                  s[2]='3';
                   }
                  if(x==5){
                   s[2]='4';
                  }
                  if(x==6){
                   s[2]='5';}
                 }
     }
     if(level==1){
     //set the probability of the sqaure being special
               x=rand()%5+1;//x is in range 1-5;
                if(x==5){
                  x=rand() % 4+1;
                  if(x==1){
                   s[1]='h';
                   }
                  else if(x==2){
                  s[1]='v';
                   }
                  else if(x==3){
                  s[1]='b';
                  }
                  else{
                   s[1]='p';
                  }
                  }
               else{
                  s[1]='_';
                }
        }   
     else if(level==2){
       //set the probability of the sqaure being special
           x=rand() % 5+1;
             if(x==1){
               s[1]='h';
              }
             if(x==2){
              s[1]='v';
             }
             if(x==3){
              s[1]='b';
             }
             if(x==4){
              s[1]='p';
             }
             if(x==5){
              s[1]='_';
             }
      }  
       ab->setcell(s[0], s[1], s[2]);
}

void lev::updatelevel(int level){
    this->level=level;
} 
