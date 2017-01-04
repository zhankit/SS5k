#include "board.h"
#include "window.h"

#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


/************************************************
  dtor
************************************************/
board::~board(){
    cleargrid();
    delete grid;
    delete window;
}

/**********************************************
link to Xwindow
**********************************************/
void board::setwindow(Xwindow *window){
     this->window=window;
}

/***********************************************
 CLEAR THE GRID
 ************************************************/
void board::cleargrid(){
    for (int i=0;i<10;i++){
        delete [] grid[i];
    }
    delete [] grid;
    grid = 0;
    delete celg;
}


/***********************************************
  swap two grid
***********************************************/
void board::swapgrid(cell *ab, cell*cd){
     char locked1 = ab->getstate();
     char locked2 = cd->getstate();
     char square1=  ab->getsquare();
     char square2=  cd->getsquare();
     char colour1=  ab->getcolour();
     char colour2=  cd->getcolour();
    ab->setcell(locked2, square2, colour2);
    cd->setcell(locked1, square1, colour1);
    ab->draw(window);
    cd->draw(window);
}



/************************************************
   start the game with various possible
 ************************************************/
board::board(bool textMode, int seed, string inputfile, bool useFile, int startLevel){

    this->textMode = textMode;
    this->seed = seed;
    // Set seed
    if (seed == -1) {
        srand(time(NULL));
    }else {
        srand(seed);
    }
    window=NULL;

    // Set score to be 0
    this->score = 0;
    this->inputfile = inputfile;
    this->useFile = useFile;
    this->level = startLevel;
    this->maxLevel = 3;
    init();
}

//returns true if no cells in the board are locked
bool board::noLocked() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].getstate() == 'l') {
                return false;
            }
        }
    }
    return true;
}
/************************************************
  input a new file and do the same on the same level
************************************************/
 void board::changefile(string newfile){
      this->inputfile=newfile;
      restart();
}

/************************************************
  graw the board
************************************************/
void board::draw(){
    std::ostringstream ss;
    ss << "Score: " << score;
    window->drawBigString(550,200,ss.str(), 6);

    ss.str(std::string());
    ss << "Level: " << level;

    window->drawBigString(550,230,ss.str(), 7);
    ss.str(std::string());
    ss << "Movesremain: " << movesremain;

    window->drawBigString(550,260,ss.str(), 8);
     ss.str(std::string());
    ss << "Hight score: " << highscore;

    window->drawBigString(550,280,ss.str(), 9);
    for(int i=0; i<10;i++){
      for(int j=0; j<10; j++){
         grid[i][j].draw(window);
      }
}
}
/*************************************************
  initialize the board
*************************************************/
void board::createlevel0(){
    string file=this->inputfile;
    ifstream fin(file.c_str());
      string s;
   for(int r=0; r<10; r++){
    for(int c=0; c<10; c++){
     fin >>s;
     grid[r][c].setcell(s[0], s[1], s[2]);
       }
   }
  if(fin>>s){
   this->seq=s;
   this->seqposition=0;
   celg-> levelonesequence = s;
   celg-> levelonecounter= 0;}
}


//generate level one
void board::createlevel1(){
    for(int r=0; r<10; r++){
     for(int c=0; c<10; c++){
       celg->generate(&grid[r][c]);
        bool find=hasmatch(r, c);
         while(find){
           celg->generate(&grid[r][c]);
           find=hasmatch(r,c);
          }
         }
   }
}

//check has match for a grid
bool board::hasmatch(int r, int c){
     if(InBound(r-2, c)){
       if((grid[r][c].getcolour()== grid[r-1][c].getcolour()) && (grid[r][c].getcolour()== grid[r-2][c].getcolour())){
           return true;
       }}
     if(InBound(r+2,c)){
       if((grid[r][c].getcolour()== grid[r+1][c].getcolour()) && (grid[r][c].getcolour()== grid[r+2][c].getcolour())){
           return true;
       }}
     if(InBound(r,c+2)){
       if((grid[r][c].getcolour()== grid[r][c+1].getcolour()) && (grid[r][c].getcolour()== grid[r][c+2].getcolour())){
           return true;
       }}
      if(InBound(r,c-2)){
       if((grid[r][c].getcolour()== grid[r][c-1].getcolour()) && (grid[r][c].getcolour()== grid[r][c-2].getcolour())){
           return true;
       }}
      return false;
}


//generate level two

void board::createlevel2(){
     for(int r=0; r<10; r++){
       for(int c=0; c<10; c++){
         celg->generate(&grid[r][c]);
         bool find=hasmatch(r, c);
         while(find){
           celg->generate(&grid[r][c]);
           find=hasmatch(r,c);
          }
   }
   }
  int countlock=0;
      // Creats random integer between 0-9 inclusive
         while(countlock <=20){
            int x1 = rand() % 10;
            int y1 = rand() % 10;

            if (grid[x1][y1].getstate() != 'l' ) {
                char square=grid[x1][y1].getsquare();
                char colour=grid[x1][y1].getcolour();
                grid[x1][y1].setcell('l', square, colour);
                countlock++;
            }
        }
 }






  

   

void board::init(){
     if(grid != 0){
          this->cleargrid();
     }
    grid = new cell *[10];

    for (int i = 0; i < 10; i++) {
        grid[i] = new cell [10];
        for (int j = 0; j < 10; j++) {
            grid[i][j].setcell('_', '_', '_');
            grid[i][j].setcoor(i,j);
        }
    }
    startscore=score;
    celg= new lev(this->seed);
    celg->updatelevel(level);
    this->seq="";
    this->seqposition=-1;
    
  if(level==0 || useFile){
    createlevel0();
    this->movesremain=20;
      }
  else if(level==1){
    createlevel1();
    this->movesremain=25;
     }
  else if(level==2 || level==3){
    createlevel2();
    this->movesremain=35;
  }
}


/***************************************
 restart the game
***************************************/
void board::restart(){
    cleargrid();
    score=0;
    highscore=0;
    init();
}





/*****************************************
   drop down the grid and fill the empty
*****************************************/
void board::drop(){
    for(int c=0; c <10;c++){
      for(int r=9; r >=0; r--){
        if(grid[r][c].getstate()=='_' && grid[r][c].getsquare()=='_' && grid[r][c].getcolour()=='_'){
          for(int j=r; j >=0; j--){
            if( grid[j][c].getstate() !='_' || grid[j][c].getsquare() !='_' || grid[j][c].getcolour()!='_'){
             swapgrid(&grid[r][c], &grid[j][c]);
             break;
             }
          }
        }
      }
     }
}

void board::fillgrid(){
    for(int r=9; r >=0; r--){
      for(int c=0; c <10; c++){
       if(grid[r][c].getstate()=='_' && grid[r][c].getsquare()=='_' && grid[r][c].getcolour()=='_'){
          string s="___";
            if(level==0){
               int num=this->seq.length();
             if(this->seqposition >= num){
                this->seqposition=0;
               }
                 s[2]=seq[seqposition++];
                 grid[r][c].setcell(s[0], s[1], s[2]);
            }
           else{
             celg->generate(&grid[r][c]);
            }
             grid[r][c].draw(window);
            }
}
}
}


/***********************************************************************
   chain reaction 
***********************************************************************/
int board::Leftmatches(int row, int col){
       int left = 0;
	for (int c = col; c>=0; c--){
		if ((grid[row][c].getcolour()) == (grid[row][col].getcolour())){
			left += 1;
		}
                else{return left;}
         }
       return left;
}

int board:: Rightmatches(int row, int col){
      int right = 0;
        for (int c = col; c<10; c++){
                if ((grid[row][c].getcolour()) == (grid[row][col].getcolour())){
                        right += 1;
                }
                else{return right;}
        }
      return right;
}
int board:: Upmatches(int row, int col){
      int up = 0;
        for (int c = row; c>=0; c--){
                if ((grid[c][col].getcolour()) == (grid[row][col].getcolour())){
                        up += 1;
                }
                else{return up;}
        }
      return up;
}
int board:: Downmatches(int row, int col){
      int down = 0;
        for (int c = row; c<10; c++){
                if ((grid[c][col].getcolour()) == (grid[row][col].getcolour())){
                        down += 1;
                }
                else{return down;}
        }
      return down;
}



bool board::psychedelic(int row, int col){
      if(grid[row][col].getstate()=='l'){
          return false;
        }
        int left = Leftmatches(row, col);
        int right = Rightmatches(row, col);
        int up = Upmatches(row, col);
        int down = Downmatches(row, col);
        char color=grid[row][col].getcolour();
      if(left+right-1 >=5){
        deletegrid(row, col, 2, left-1);
        deletegrid(row, col, 3, right-1);
        int specialcol=((left+right)/2+col-left);
        grid[row][col].setcell('_','_','_');
        grid[row][specialcol].setcell('_','p',color);
        grid[row][specialcol].draw(window);
        return true;
      }
      else if(up+down-1 >=5){
        deletegrid(row, col, 0, up-1);
        deletegrid(row, col, 1, down-1);
        int specialrow=((up+down)/2+(row-up));
        grid[row][col].setcell('_','_','_');
        grid[specialrow][col].setcell('_','p',color);
        grid[specialrow][col].draw(window);
        return true;
      }
      return false;
}
       


bool board::upright(int row, int col){
     if(grid[row][col].getstate()=='l'){
          return false;
        }
        int up = Upmatches(row, col-1);
        int down = Downmatches(row, col-1);
        char color=grid[row][col].getcolour();
      if(up+down-1==4){
        deletegrid(row, col, 0, up-1);
        deletegrid(row, col, 1, down-1);
        int specialrow=((up+down)/2+(row-up));
        grid[row][col].setcell('_','_','_');
        grid[specialrow][col].setcell('_','v',color);
        grid[specialrow][col].draw(window);
        return true;
       }
     return false;
}

bool board::lateral(int row, int col){
      if(grid[row][col].getstate()=='l'){
          return false;
        }
        int left = Leftmatches(row, col);
        int right = Rightmatches(row, col);
        char color=grid[row][col].getcolour();
        if(left+right-1==4){
        deletegrid(row, col, 2, left-1);
        deletegrid(row, col, 3, right-1);
        int specialcol=((left+right)/2+(col-left));
        grid[row][col].setcell('_','_','_');
        grid[row][specialcol].setcell('_','h',color);
        grid[row][specialcol].draw(window);
        return true;
       }
       return false;
}

        



bool board::basic(int row, int col){
      if(grid[row][col].getstate()=='l'){
          return false;
        }
        int left = Leftmatches(row, col);
        int right = Rightmatches(row, col);
        int up = Upmatches(row, col);
        int down = Downmatches(row, col);
      if(left+right-1>=3){
        deletegrid(row, col, 2, left-1);
        deletegrid(row, col, 3, right-1);
        grid[row][col].setcell('_','_','_');
        grid[row][col].draw(window);
        return true;
      }
      else if(up+down-1>=3){
        deletegrid(row, col, 0, up-1);
        deletegrid(row, col, 1, down-1);
        grid[row][col].setcell('_','_','_');
        grid[row][col].draw(window);
        return true;
      }
      return false;
}



bool board::unstable(int row, int col){
        if(grid[row][col].getstate()=='l'){
          return false;
        }
	int left = Leftmatches(row, col);
	int right = Rightmatches(row, col);
	int up = Upmatches(row, col);
	int down = Downmatches(row, col);
        char color=grid[row][col].getcolour();
        if((left >= 3) && (up >= 3) && (right >= 3)){
            deletegrid(row, col, 0, up-1);
            deletegrid(row, col, 2, left-1);
            deletegrid(row, col, 3, right-1);
            grid[row][col].setcell('_','b',color);
            grid[row][col].draw(window);
           return true;
        }
         if((left >= 3) && (down >= 3) && (right >= 3)){
           deletegrid(row, col, 1, down-1);
           deletegrid(row, col, 2, left-1);
           deletegrid(row, col, 3, right-1);
           grid[row][col].setcell('_','b',color);
           grid[row][col].draw(window);
           return true;
        }
         if((left >= 3) && (up >= 3) && (down >= 3)){
           deletegrid(row, col, 0, up-1);
            deletegrid(row, col, 2, left-1);
            deletegrid(row, col, 1, down-1);
            grid[row][col].setcell('_','b',color);
            grid[row][col].draw(window);
           return true;
        }
         if((down >= 3) && (up >= 3) && (right >= 3)){
            deletegrid(row, col, 0, up-1);
            deletegrid(row, col, 3, right-1);
            deletegrid(row, col, 1, down-1);
            grid[row][col].setcell('_','b',color);
            grid[row][col].draw(window);
           return true;
        }
	if ((left >= 3) && (up >= 3)){
             deletegrid(row, col, 0, up-1);
             deletegrid(row, col, 2, left-1);
             grid[row][col].setcell('_','b',color);
             grid[row][col].draw(window);
		return true;
	}
	if ((left >= 3) && (down >= 3)){
             deletegrid(row, col, 1, down-1);
             deletegrid(row, col, 2, left-1);
             grid[row][col].setcell('_','b',color);
             grid[row][col].draw(window);
		return true;
	}
	if ((right >= 3) && (up >= 3)){
              deletegrid(row, col, 3, right-1);
             deletegrid(row, col, 2, left-1);
             grid[row][col].setcell('_','b',color);
             grid[row][col].draw(window);
		return true;
	}
	if ((right >= 3) && (down >= 3)){
             deletegrid(row, col, 0, up-1);
             deletegrid(row, col, 2, left-1);
             grid[row][col].setcell('_','b',color);
             grid[row][col].draw(window);
		return true;
	}
	return false;
}




bool board::matchexist(){
   bool matchExists = false;
   this->deletcell=0;
  for (int row = 0; ((row < 10) && !matchExists); row++){
		for (int col = 0; ((col < 10) && !matchExists); col++){
                   if (unstable(row, col)){
                       this->deletcell++;
                        matchExists=true;
	            }
                    else if(psychedelic(row, col)){
                             this->deletcell++;
                              matchExists=true;
                      }
                    else if(lateral(row, col)){
                            this->deletcell++;
                             matchExists=true;
                    }
                    else if(upright(row, col)){
                            this->deletcell++;
                           matchExists=true;
                    }
                    else if(basic(row, col)){
                             this->deletcell++;
                             matchExists=true;
                    }
		}
	}
	return matchExists;
}

int board::exp(int num, int chain){
    if(chain==0){
      return 1;
    }
    return num * chain;
}


void board::deletegrid(int x, int y, int z, int num){
     int index=1;
     if(z==0){

       for(;index <= num; index++){
          if( x-index >= 0){
         grid[x-index][y].setcell('_','_','_');
         grid[x-index][y].draw(window);}
       }
     }
     if(z==1){

       for(;index <= num; index++){
         if( x+index < 10){
         grid[x+index][y].setcell('_','_','_');
         grid[x+index][y].draw(window);
       }
    }
   }
    if(z==2){
       for(;index <= num; index++){
          if( y-index >= 0){
         grid[x][y-index].setcell('_','_','_');
         grid[x][y-index].draw(window);}
     }

     }
    if(z==3){
       for(;index <= num; index++){
         if( y+index < 10){
         grid[x][y+index].setcell('_','_','_');
         grid[x][y+index].draw(window);}
       }
     }
   this->deletcell +=index-1;
}            
       

     


int board::getpoints(int squares, int chain) {
	if (squares == 3) {
		return squares * exp(2, chain);
	}
	else if (squares == 4) {
		return 2 * squares * exp(2, chain);
	}
	else if (squares == 5) {
		return 3 * squares * exp(2, chain);
	}
	else if (squares > 5) {
		return 4 * squares * exp(2, chain);
	}
	else {
		return 0;
	}
}


 void board::action(){
     int chain=0;
     int high=0;
     bool findmatch=matchexist();
     while(findmatch){
       int square=this->deletcell;
       drop();
       fillgrid();
       score +=getpoints(square, chain);
       high +=getpoints(square,chain);
       chain++;
       findmatch=matchexist();
     }
    if(high > this->highscore){
       this->highscore=high;
    }
}


/**************************************
  level up and level down
**************************************/
void  board::levelup(){
     if(this->level < maxLevel){
       this->level++;
       cleargrid();
       init();
     }
}

void board::leveldown(){
     if(level > 0){
       this->level--;
       cleargrid();
       init();
     }
}


/************************************
  swap the cell

*************************************/




/*************************************************
    check if the coordinate is valid
 ************************************************/
bool board::InBound(int x,int y){
    if (x >= 0 && x <= 9 && y >= 0 && y <= 9) {
        return true;
    }
    return false;
}

  /***********************************************
    Check if there is any match after swap
 ************************************************/
bool board::isamatch(char color, int r ,int c,int direction){
     if(grid[r][c].getstate()=='l'){return false;}
    // Check from centre
    if (InBound(r-1,c) && InBound(r+1,c) &&
        grid[r-1][c].getcolour() == color &&
        grid[r+1][c].getcolour() == color &&
        (direction == 3 || direction == 2)) {
        return true;
    }else if(InBound(r,c-1) && InBound(r,c+1) &&
             grid[r][c-1].getcolour() == color &&
             grid[r][c+1].getcolour() == color &&
             (direction == 0 || direction == 1)) {
        return true;
    }
   // Check from boundaries expect the direction it swaps from
    if (direction == 0) {
        if (InBound(r-1,c) && InBound(r-2,c) &&
            grid[r-1][c].getcolour() == color &&
            grid[r-2][c].getcolour() == color) {
            return true;
        }else if(InBound(r,c-1) && InBound(r,c-2) &&
                 grid[r][c-1].getcolour() == color &&
                 grid[r][c-2].getcolour() == color) {
            return true;
        }else if(InBound(r,c+1) && InBound(r,c+2) &&
                 grid[r][c+1].getcolour() == color &&
                 grid[r][c+2].getcolour() == color) {
            return true;
        }
    }else if( direction == 1){
        if (InBound(r+1,c) && InBound(r+2,c) &&
           grid[r+1][c].getcolour() == color &&
           grid[r+2][c].getcolour() == color) {
            return true;
        }else if(InBound(r,c-1) && InBound(r,c-2) &&
                 grid[r][c-1].getcolour() == color &&
                 grid[r][c-2].getcolour() == color) {
            return true;
     }else if(InBound(r,c+1) && InBound(r,c+2) &&
                 grid[r][c+1].getcolour() == color &&
                 grid[r][c+2].getcolour() == color) {
            return true;
        }
    }else if( direction == 3){
        if (InBound(r,c+1) && InBound(r,c+2) &&
            grid[r][c+1].getcolour() == color &&
            grid[r][c+2].getcolour() == color) {
            return true;
        }else if(InBound(r-1,c) && InBound(r-2,c) &&
                 grid[r-1][c].getcolour() == color &&
                 grid[r-2][c].getcolour() == color) {
            return true;
        }else if(InBound(r+1,c) && InBound(r+2,c) &&
                grid[r+1][c].getcolour() == color &&
                grid[r+2][c].getcolour() == color) {
            return true;
        }
     }else if( direction == 2){
        if (InBound(r,c-1) && InBound(r,c-2) &&
            grid[r][c-1].getcolour() == color &&
            grid[r][c-2].getcolour() == color) {
            return true;
        }else if(InBound(r-1,c) && InBound(r-2,c) &&
                 grid[r-1][c].getcolour() == color &&
                 grid[r-2][c].getcolour() == color) {
            return true;
        }else if(InBound(r+1,c) && InBound(r+2,c) &&
                 grid[r+1][c].getcolour() == color &&
                 grid[r+2][c].getcolour() == color) {
            return true;
        }
    }
    return false;
}



bool board::isvalidswap(int x,int y,int direction){
     if(direction==0){
          if(x <=0){return false;}
            
         return isamatch(grid[x][y].getcolour(), x-1, y, direction) || isamatch(grid[x-1][y].getcolour(), x, y, 1);
     }
    if(direction==1){
        if(x >=9){
            return false;}
            return isamatch(grid[x][y].getcolour(), x+1, y,direction) || isamatch(grid[x+1][y].getcolour(), x, y,0);
    }
    if(direction==2){
       if(y <=0){ return false;}
         return isamatch(grid[x][y].getcolour(), x, y-1, direction) || isamatch(grid[x][y-1].getcolour(), x, y,3);
         }
    if(direction==3){
      if(y >= 9){return false;}
            return isamatch(grid[x][y].getcolour(), x, y+1, direction) || isamatch(grid[x][y+1].getcolour(), x, y, 2);
    }
  return false;
}


void board::swap(int x, int y, int direction){
      if(!isvalidswap(x,y,direction)){
          cerr<<"not valid swap"<<endl;
          return;
      }
   else{
    if(direction==0){
      swapgrid(&grid[x][y], &grid[x-1][y]);
    }
    if(direction==1){
      swapgrid(&grid[x][y], &grid[x+1][y]);
    }
    if(direction==2){
     swapgrid(&grid[x][y], &grid[x][y-1]);
    }
    if(direction==3){
     swapgrid(&grid[x][y], &grid[x][y+1]);
    }
   //call chain action;
    action();
    movesremain--;
    
    if(movesremain==0){
      restart();
    }
   else{
   //level up if score passes the threshold
    if (level == 0) {
        if (score - startscore >= 200) {
            levelup();
        }
    }
    else if (level == 1) {
        if (score - startscore >= 300) {
            levelup();
        }
    }
    else if (level == 2) {
        if (score - startscore >= 500 && noLocked()) {
            levelup();
        }
    }}}
}

/*********************************************************
   hint
**********************************************************/
string board::hint(){
  for(int r=0; r<10;r++){
    for(int c=0; c<10;c++){
     for(int k=0; k<4; k++){
      if(isvalidswap(r, c, k)){
       ostringstream ss;
       ss << "swap " << r << " " << c << " " << k;
                    return ss.str();
                }
            }
        }
     }
    return "";
}

/*************************************************************
 scramble the board when there is no moves available
*************************************************************/
void board::scramble(){
      while(hint()==""){
       for ( int i = 0; i < 100; i++ ) {

            // Creats random integer between 0-9 inclusive
            int x1 = rand() % 10;
            int y1 = rand() % 10;

            if ( grid[x1][y1].getstate() == 'l' ) {
                break;
            }

            int x2 = rand() % 10;
            int y2 = rand() % 10;

           if (grid[x2][y2].getstate() == 'l' ) {
                      break;
                }

           swapgrid(&grid[x1][y1], &grid[x2][y2]);
        }
    }
}


/***************************************************
operator
****************************************************/
std::ostream &operator<<(std::ostream &out, board &b){
     if (! b.textMode) b.draw();
     out<<"Level: "<<b.level<<endl;
     out<<"Score: "<<b.score<<endl;
     out<<"Moves Remaining: "<<b.movesremain<<endl;
     out<<"Hi Score: "<<b.highscore<<endl;
     out<<"----------"<<endl;
     for(int i=0; i<10; i++){
       for(int j=0; j<10; j++){
        out<<b.grid[i][j].getstate()<<b.grid[i][j].getsquare()<<b.grid[i][j].getcolour()<<" ";
       }
        out<<endl;
     }
     return out;
}  
