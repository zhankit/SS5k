#include <iostream>
#include <string>
#include <cstdlib>

#include "board.h"
#include "window.h"

using namespace std;

int main(int argc, char* argv[]) {
    bool textMode = false; //0 = both text and graphics, 1 = text
    int seed = -1; //random number generator seed
    string inputfile = "sequence.txt"; // input file
    bool useFile = false; //to check whether scriptfile command has been used
    int startLevel = 0; //game start level

    string commandline;
    string command[7] = {"swap","hint","scramble","levelup","leveldown","restart", "changefile"}; //add new commands here

    //command-line options
    for (int i = 1; i < argc; i++) {
        string comm = argv[i];
        //make program in textmode
        if (comm == "-text") {
            textMode = true;
        }
        //set random seed
        else if (comm == "-seed") {
            seed = atoi(argv[i+1]);
            i++;
        }
        //use a file to initialize board
        else if (comm == "-scriptfile") {
            inputfile = argv[i+1];
            useFile = true;
            i++;
        }
        //set a start level
        else if (comm == "-startlevel") {
            startLevel = atoi(argv[i+1]);
            i++;
        }
    }
   cout<<"You can input the valid command as follow:"<<endl;
   for(int i=0; i<7; i++){
      cout<<command[i]<<" ";
   }
   cout<<endl;
   cout<<"You can replace the command name as you wish with same fuctional by enter replace xxx yyy where xxx is original command and yyy is the new command!"<<endl;
   board *b = new board(textMode, seed, inputfile, useFile,startLevel); 
   if(!textMode){
     Xwindow *window=new Xwindow(700, 500);
     b->setwindow(window);
   }
     cout << *b;
     while(cin>>commandline){
        if(commandline==command[0]){
           int x,y,z;
          cin>>x>>y>>z;
          b->swap(x,y,z);
          cout<<"You are trying to swap row: "<<x+1<<" "<<"col: "<<y+1<<" "<<"to direction: "<<z<<endl;
           cout << *b;
         
        }
       else if(commandline==command[1]){
         cout<< b->hint()<<endl;
       }
       else if(commandline==command[2]){
         if(b->hint() !=""){
           cout<<"There still have moves to swap, cannot be swapped. Try to enter hint command."<<endl;
         }
         else{
            b->scramble();
             cout << *b;
         }
       }
       else if(commandline==command[3]){
         b->levelup();
         cout << *b;
       }
       else if(commandline==command[4]){
          b->leveldown();
          cout << *b;
       }
       else if(commandline==command[5]){
          b->restart();
          cout << *b;
        }
       else if(commandline==command[6]){
          string newfile;
          cin>>newfile;
          b->changefile(newfile);
          cout << *b;
       }
       else if(commandline=="replace"){
          string oldcommand;
          string newcommand;
          cin>>oldcommand>>newcommand;
           for(int i=0;i<7;i++){
             if(command[i]==oldcommand){
                command[i]=newcommand;
                break;
             }}
        }  
          
     }
   delete b;
   return 0;
}
    


