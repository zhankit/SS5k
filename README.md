##Introduction

It is a video game, which is a match-three style puzzle game that draws emelemts from popular games, such as candy crush and the Bejewelled series.

##Compilation

Makefile bash script is included. Use the command make in unix environment. It will compiled with the program name WATAN and be excecuted by ./ss5k

Connection for X11 is require for graphics

#Display
The sample text display follows

```
Level: 1
Score: 0
Moves Remaining: 7
Hi Score: 100
----------
__0 __1 __2 __0 __1 __3 __0 __0 __1 __2
_h1 __2 __1 __0 __3 __1 _b2 __2 __3 __3
__1 __0 __2 __1 __3 __2 _v0 __1 __1 __2
__2 _v1 __0 __1 __2 __3 __2 __1 _b2 __2
__1 __2 __1 __3 __3 _b1 __0 __2 __1 __3
__1 __3 _p0 __0 __3 __1 __2 __2 __3 _v3
__0 __1 __2 __0 __1 __3 __0 _h0 __1 __2
__2 _h0 __0 __1 __2 _h3 __2 __1 __1 __2
__3 __1 __0 _h1 __0 __0 __1 __2 __2 _v3
__0 __0 _p1 __2 __3 __1 __0 __2 _v3 __3
```

Each square is represented by 3 characters: <br />
1. The first character is used for any advanced features you implement (see ahead for one such advanced feature). <br />
2. The second character is used to represent the type of square. 
```
h represent LateralSquare
v represent UprightSquare
b represent UnstableSquare
p represent PsychedelicSquare
```
3. The Third character is used to represent the colour of the square.
```
0 represent White
1 represent Red
2 represent Green
3 represent Blue
4 represent Cyan
5 represent Yellow
```
## Commands
**swap** :  x y z swaps the square at the (x,y) co-ordinate with the square in the z direction (0 for north, 1 for south, 2 for west and 3 for east) e.g. swap 4 5 3 results in an attempt to swap the square at (4,5) to the square to the east (right) i.e. the square at cell location (4,6). <br />
**hint** : The game returns a valid move (x,y, z as above) that would lead to a match. <br />
**scramble** : Available only if no moves are possible, this command reshuffles the squares on the board (no new cells are created) <br />
**levelup** : Increases the dificulty level of the game by one. You may clear the board and create a new one suitable for that level. If there is no higher level, this command has no effect. <br />
**leveldown** : The same as above, but this time decreasing the difficulty level of the game by one. <br />
**restart** : Clears the board and starts a new game at the same level. The player's score is reset to 0. If you have implemented a high score feature, that score is not reset. End-of-file (EOF) <br />


## Command-line Interface
-text : runs the program in text-only mode. No graphics are displayed. <br />
xxx sets the random number generator’s seed to xxx. <br />
-scriptfile xxx uses xxx for this level's initial board configuration. <br />
-startlevel n starts the game in level n. The game starts in level 0 if this option is notsupplied.<br />
-testing runs the game in testing mode. During testing<br />

