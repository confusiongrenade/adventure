//
//  adventure.c
//
//  My Final Project is a recreation of level 1 of the 1980 Atari VCS Video Game "Adventure" by Warren Robinett
// In Adventure, you play as a nameless hero (the square) on a quest to retrieve the holy grail and
// return it to your castle (the gold castle).  In order to succede in your quest, you must fight off the
// dragons, find the key to the enemy castle, and navigate the labryth in order to find the chalice.
// the pixel art has been recreated as accuratey  as possible, which means that, just like in the original
// game, the dragon looks like a duck/seahorse, and the sword looks like an arrow. you use the WASD keys
// to move, and use the space bar to drop the item you are holding on to.  press the "p" key to quit.

// I choose this game becuase it is probably my favorite retro video game, and I felt like creating the game was withing my programming scope.  Also, Adventure is credited with being the first Action Adventure video game, and also the first easter egg in a video game.  Unfortunately, in this version, the easter egg has not been implemented.  after working on it, I realsied that the game was in my scope, but it was very difficult.
//  Created by Nicholas Carroll on 11/1/15.
//
//


#include <stdlib.h>
#include <stdio.h>
#include "gfx5.h"
#include <math.h>
#include <unistd.h>
//#include "adventure.h"


struct color {
    int r;
    int g;
    int b;
};
struct obj{
    int x;
    int y;
    struct color color;
    int carried;
    int id;
    int carrying;
    int planex;
    int planey;
    int alive;
    int size;
    
};

struct wall{
    int x;
    int y;
    int l;
    int h;
    struct color color;
    int carried;
    int id;
    int carrying;
    int planex;
    int planey;
    int alive;
    int door;
    
    
};



struct hero {
    int x;
    int y;
    int obj;
    struct obj *carry;
    int planex;
    int planey;
    int alive;
    int speed;
    int size;
    
};


void drawCharacter(int x, int y);
void drawSword( int x, int y);

int collision2(struct hero x, struct obj y);
void drawDragon( int x, int y);
void draw(struct obj x);
int collision3(struct hero x, struct obj y);
void wall( struct wall x);
int collisionWall( struct wall x, struct hero y);
void drawChalice(struct obj x);
void changeRooms( struct hero *you, int xsize, int ysize);
void drawKey( struct obj x);
void drawKeyBlack( struct obj x);

int main()
{
    
    // establish all of the variables
    int wallmax = 167;
    int itemsmax = 7;
    int width = 24;
    int belly = 10;
    int dx, dy;
    int pixel = 3;
    double theta;
    int win =0;
    int j = 0;
    
    
    struct color bg;// grey
    bg.r = 219;
    bg.g =219;
    bg.b = 219;
    struct color p2; // washed out green
    p2.r = 120;
    p2.g = 140;
    p2.b = 40;
    struct color y; // yorgle yellow
    y.r = 255;
    y.g = 247;
    y.b = 0;
    struct color r; // rhindle red
    
    struct color b; // maze blue
    b.r = 66;
    b.g = 72;
    b.b = 202;
    
    struct color black;
    black.r =0;
    black.g=0;
    black.b = 0;
    
    struct color maroon;
    maroon.r = 189;
    maroon.g = 111;
    maroon.b = 63;
    
    struct color p; // purple, chalice room
    p.r = 127;
    p.g = 84;
    p.b = 165;
    
    struct color g; // green
    g.r = 90;
    g.g = 177;
    g.b = 93;
    
    struct color pg; // puke green
    pg.r = 161;
    pg.g = 176;
    pg.b = 85;
    
    struct color o; // orange
    o.r = 177;
    o.g =106;
    
    o.b = 72;
    
    
    int speed =15, i;
    int inside = 1;
    int xsize = 800;
    int ysize = 600;
    int xmid = xsize/2;
    int ymid = ysize/2;
    char c;
    
    
    // Open a new window for drawing.
    gfx_open(800, 600, "Adventure");
    
    struct hero you;
    you.x = xmid;
    you.y = 3*ysize/4;
    you.obj = 0;
    you.planex = 0;
    you.planey =0;
    you.alive = 1;
    you.speed =speed;
    you.size  = 3*pixel;
    struct obj mag;
    mag.x =xmid - 20;
    mag.y = xmid - 20;
    mag.id = 2;
    
    struct wall w[160];
    
    
    
    
    //  Yellow castle, room 0,0
    
    
    
    w[142].x = 0;
    w[142].y= 0;
    w[142].l = 3*xsize/8;
    w[142].h =  width;
    w[142].planex = 0;
    w[142].planey = 0;
    w[142].color =y;
    
    w[143].x = (5*xsize/8);
    w[143].y= 0;
    w[143].l = 3*xsize/8;
    w[143].h =  width;
    w[143].planex = 0;
    w[143].planey = 0;
    w[143].color =y;
    
    
    w[144].x = (5*xsize/8);
    w[144].y= ysize-width;
    w[144].l = 3*xsize/8;
    w[144].h =  width;
    w[144].planex = 0;
    w[144].planey = 0;
    w[144].color =y;
    
    w[145].x = 0;
    w[145].y= ysize-width;
    w[145].l = 3*xsize/8;
    w[145].h =  width;
    w[145].planex = 0;
    w[145].planey = 0;
    w[145].color =y;
    
    w[146].x = 0;
    w[146].y= 0;
    w[146].l = width;
    w[146].h =  ysize;
    w[146].planex = 0;
    w[146].planey = 0;
    w[146].color =y;
    
    w[147].x = xsize-width;
    w[147].y= 0;
    w[147].l = width;
    w[147].h =  ysize;
    w[147].planex = 0;
    w[147].planey = 0;
    w[147].color =y;
    
    w[148].x = xsize/2-10*width;
    w[148].y= 0;
    w[148].l = width;
    w[148].h =  4*width;
    w[148].planex = 0;
    w[148].planey = 0;
    w[148].color =y;
    
    w[160].x = xsize/2-8*width;
    w[160].y= 0;
    w[160].l = width;
    w[160].h =  4*width;
    w[160].planex = 0;
    w[160].planey = 0;
    w[160].color =y;
    
    w[161].x = xsize/2-6*width;
    w[161].y= 0;
    w[161].l = width;
    w[161].h =  4*width;
    w[161].planex = 0;
    w[161].planey = 0;
    w[161].color =y;
    
    w[149].x = xsize/2-4*width;
    w[149].y= 0;
    w[149].l = width;
    w[149].h =  4*width;
    w[149].planex = 0;
    w[149].planey = 0;
    w[149].color =y;
    
    w[150].x = xsize/2+3*width;
    w[150].y= 0;
    w[150].l = width;
    w[150].h =  4*width;
    w[150].planex = 0;
    w[150].planey = 0;
    w[150].color =y;
    
    w[152].x = xsize/2+5*width;
    w[152].y= 0;
    w[152].l = width;
    w[152].h =  4*width;
    w[152].planex = 0;
    w[152].planey = 0;
    w[152].color =y;
    
    w[153].x = xsize/2+7*width;
    w[153].y= 0;
    w[153].l = width;
    w[153].h =  4*width;
    w[153].planex = 0;
    w[153].planey = 0;
    w[153].color =y;
    
    w[154].x = xsize/2-10*width;
    w[154].y= 4*width;
    w[154].l = 7*width;
    w[154].h =  10*width;
    w[154].planex = 0;
    w[154].planey = 0;
    w[154].color =y;
     
     
    
    w[155].x = xsize/2+9*width;
    w[155].y= 0;
    w[155].l = width;
    w[155].h =  4*width;
    w[155].planex = 0;
    w[155].planey = 0;
    w[155].color =y;
    
    w[156].x = xsize/2+3*width;
    w[156].y= 4*width;
    w[156].l = 7*width;
    w[156].h =  10*width;
    w[156].planex = 0;
    w[156].planey = 0;
    w[156].color =y;

    w[157].x = xsize/2-8*width;
    w[157].y= 10*width;
    w[157].l = 16*width;
    w[157].h =  7*width;
    w[157].planex = -0;
    w[157].planey = 0;
    w[157].color =y;
    w[157].door = 1;
    
    w[158].x = xsize/2-8*width;
    w[158].y= 17*width;
    w[158].l = 5*width;
    w[158].h =  3*width;
    w[158].planex = 0;
    w[158].planey = 0;
    w[158].color =y;
    
    w[159].x = xsize/2+3*width;
    w[159].y= 17*width;
    w[159].l = 5*width;
    w[159].h =  3*width;
    w[159].planex = 0;
    w[159].planey = 0;
    w[159].color =y;
    
    ///   no longer yellow castle, still room 0,0
   
    w[2].x = xsize-12;
    w[2].y= 0 ;
    w[2].l = 12;
    w[2].h = ysize;
    w[2].planex = 0;
    w[2].planey = 0;
    w[2].color = p2;
    
    w[3].x = 0;
    w[3].y= 0 ;
    w[3].l = 12;
    w[3].h = ysize;
    w[3].planex = 0;
    w[3].planey = 0;
    
    w[19].x = (5*xsize/8);
    w[19].y= ysize-width;
    w[19].l = 3*xsize/8;
    w[19].h =  width;
    w[19].planex = 0;
    w[19].planey = 0;
    
    w[20].x = 0;
    w[20].y= ysize-width;
    w[20].l = 3*xsize/8;
    w[20].h =  width;
    w[20].planex = 0;
    w[20].planey = 0;
    // ROOM 0, 1 (IN CASTLE)
    w[162].x = 0;
    w[162].y= 0 ;
    w[162].l = width;
    w[162].h = ysize;
    w[162].planex = 0;
    w[162].planey = 1;
    w[162].color = y;
    
    w[163].x = xsize-width;
    w[163].y= 0 ;
    w[163].l = width;
    w[163].h = ysize;
    w[163].planex = 0;
    w[163].planey = 1;
    w[163].color = y;
    
    w[164].x = 0;
    w[164].y= 0 ;
    w[164].l = xsize;
    w[164].h = width;
    w[164].planex = 0;
    w[164].planey = 1;
    w[164].color = y;
    
    
    w[165].x = (5*xsize/8);
    w[165].y= ysize-width;
    w[165].l = 3*xsize/8;
    w[165].h =  width;
    w[165].planex = 0;
    w[165].planey = 1;
     w[165].color = y;
    
    w[166].x = 0;
    w[166].y= ysize-width;
    w[166].l = 3*xsize/8;
    w[166].h =  width;
    w[166].planex = 0;
    w[166].planey = 1;
    w[166].color = y;
    
    //ROOM 0, -1 (SOUTH OF CASTLE)
    
    w[5].color = y;
    w[5].x = 0;
    w[5].y= ysize-width ;
    w[5].l = -xsize;
    w[5].h = width;
    w[5].planex = 0;
    w[5].planey = -1;
    
    w[17].x = 0;
    w[17].y= 0;
    w[17].l = 3*xsize/8;
    w[17].h =  12;
    w[17].planex = 0;
    w[17].planey = -1;
    
    w[18].x = (5*xsize/8);
    w[18].y= 0;
    w[18].l = 3*xsize/8;
    w[18].h =  width;
    w[18].planex = 0;
    w[18].planey = -1;
    
    
    // ROOM 1, -1  (NORTH OF DRAGON DEN)
    w[6].x = 0;
    w[6].y= 0 ;
    w[6].l = xsize;
    w[6].h = 12;
    w[6].planex = 1;
    w[6].planey = -1;
    w[6].color = y;
    
    w[7].x = xsize-width;
    w[7].y= 0 ;
    w[7].l = width;
    w[7].h = ysize;
    w[7].planex = 1;
    w[7].planey = -1;
    
    
    // ROOM -1, -1 (SOUTH OF MAZE)
    
    w[11].x = 0;
    w[11].y= 0 ;
    w[11].l = 12;
    w[11].h = ysize;
    w[11].planex = -1;
    w[11].planey = -1;
    
    w[12].x = 0;
    w[12].y= ysize-12;
    w[12].l = xsize;
    w[12].h =  12;
    w[12].planex = -1;
    w[12].planey = -1;
    
    w[14].x = 0;
    w[14].y= 0;
    w[14].l = 3*xsize/8;
    w[14].h =  12;
    w[14].planex = -1;
    w[14].planey = -1;
    
    w[13].x = (5*xsize/8);
    w[13].y= 0;
    w[13].l = 3*xsize/8;
    w[13].h =  width;
    w[13].planex = -1;
    w[13].planey = -1;
    
    // DRAGON DEN
    
    w[8].x = xsize-width;
    w[8].y= 0 ;
    w[8].l = width;
    w[8].h = ysize;
    w[8].planex = 1;
    w[8].planey = -2;
    
    w[9].x = 0;
    w[9].y= ysize-width ;
    w[9].l = xsize;
    w[9].h = width;
    w[9].planex = 1;
    w[9].planey = -2;
    
    w[10].x = 0;
    w[10].y= 0 ;
    w[10].l = 12;
    w[10].h = ysize;
    w[10].planex = 1;
    w[10].planey = -2;
    
    w[21].x = 0;
    w[21].y= 0;
    w[21].l = 3*xsize/8;
    w[21].h =  12;
    w[21].planex = 1;
    w[21].planey = -2;
    
    
    
    
    // ROOM ONE OF MAZE (-1,0)
    
    
    w[15].x = 0;
    w[15].y= ysize-width;
    w[15].l = 3*xsize/8;
    w[15].h =  width;
    w[15].planex = -1;
    w[15].planey = 0;
    
    w[16].x = (5*xsize/8);
    w[16].y= ysize-width;
    w[16].l = 3*xsize/8;
    w[16].h =  width;
    w[16].planex = -1;
    w[16].planey = 0;
    
    w[22].x = (5*xsize/8);
    w[22].y= 0;
    w[22].l = 3*xsize/8;
    w[22].h =  width;
    w[22].planex = 1;
    w[22].planey = -2;
    
    w[23].x = (5*xsize/8);
    w[23].y= ysize-width;
    w[23].l = 3*xsize/8;
    w[23].h =  width;
    w[23].planex = 1;
    w[23].planey = -1;
    
    w[24].x = 0;
    w[24].y= ysize-width;
    w[24].l = 3*xsize/8;
    w[24].h =  width;
    w[24].planex = 1;
    w[24].planey = -1;
    
    /// first room of the maze
    w[25].x = (xsize/2) - width;
    w[25].y=  0 ;
    w[25].l = 2*width;
    w[25].h =  width;
    w[25].planex = -1;
    w[25].planey = 0;
    
    
    w[26].x = (xsize/2) - 4*width;
    w[26].y=  0 ;
    w[26].l = 1*width;
    w[26].h =  ysize/4;
    w[26].planex = -1;
    w[26].planey = 0;
    
    
    
    w[27].x = (xsize/2) + 3*width;
    w[27].y=  0 ;
    w[27].l = 1*width;
    w[27].h =  ysize/4;
    w[27].planex = -1;
    w[27].planey = 0;
    
    
    w[28].x = (xsize/2) - 4*width;
    w[28].y=  ysize/4 ;
    w[28].l = 8*width;
    w[28].h =  width;
    w[28].planex = -1;
    w[28].planey = 0;
  
    
    w[32].x = (xsize/2) - 10*width;
    w[32].y=  0;
    w[32].l = 2*width;
    w[32].h =  (3*ysize/4);
    w[32].planex = -1;
    w[32].planey = 0;
    
    w[33].x = (xsize/2) + 8*width;
    w[33].y=  0;
    w[33].l = 2*width;
    w[33].h =  (3*ysize/4);
    w[33].planex = -1;
    w[33].planey = 0;
    
    w[34].x = (xsize/2) - 10*width;
    w[34].y=  (3*ysize/4) - width;
    w[34].l = 20*width;
    w[34].h =  2*width;
    w[34].planex = -1;
    w[34].planey = 0;
    
    w[35].x = (xsize/2) + 12*width;
    w[35].y=  0;
    w[35].l = width;
    w[35].h =  (3*ysize/4) +width;
    w[35].planex = -1;
    w[35].planey = 0;
    
    w[36].x = (xsize/2) - 13*width;
    w[36].y=  0;
    w[36].l = width;
    w[36].h =  (3*ysize/4)+ 2*width;
    w[36].planex = -1;
    w[36].planey = 0;
    
    w[37].x = 0;
    w[37].y=  (3*ysize/4);
    w[37].l =4*width;
    w[37].h =  2*width;
    w[37].planex = -1;
    w[37].planey = 0;
    
    w[38].x = (xsize/2) + 12*width;
    w[38].y=  (3*ysize/4);
    w[38].l =5*width;
    w[38].h =  2*width;
    w[38].planex = -1;
    w[38].planey = 0;
    
    w[39].x = (xsize/2) + 12*width;
    w[39].y=  0;
    w[39].l =(xsize/2) + 12*width;
    w[39].h =  width;
    w[39].planex = -1;
    w[39].planey = 0;

    w[40].x = 0;
    w[40].y=  0;
    w[40].l =(xsize/2) - 13*width;
    w[40].h =  width;
    w[40].planex = -1;
    w[40].planey = 0;
    
    w[41].x = 0;
    w[41].y=  (ysize/4);
    w[41].l =width;
    w[41].h =  ysize/4;
    w[41].planex = -1;
    w[41].planey = 0;
    
    w[42].x = xsize-width;
    w[42].y=  ysize/4;
    w[42].l =width;
    w[42].h =  ysize/4;
    w[42].planex = -1;
    w[42].planey = 0;
    
    ////  SECOND ROOM OF MAZE
    
    w[43].x = 0;
    w[43].y= 0 ;
    w[43].l = xsize;
    w[43].h = width;
    w[43].planex = -1;
    w[43].planey = 1;

    w[44].x = 0;
    w[44].y= ysize/4 ;
    w[44].l = 2*width;
    w[44].h = ysize/2;
    w[44].planex = -1;
    w[44].planey = 1;
    //w[1].color = y;
    
    
    w[45].x = 0;
    w[45].y= ysize/4 ;
    w[45].l = xsize/4 - width;
    w[45].h = 2*width;
    w[45].planex = -1;
    w[45].planey = 1;
    
    
    w[46].x = xsize/4 +width;
    w[46].y= ysize/4 ;
    w[46].l = xsize/2 - 2*width;
    w[46].h = 2*width;
    w[46].planex = -1;
    w[46].planey = 1;
    
    w[47].x = 3*xsize/4 +width;
    w[47].y= ysize/4 ;
    w[47].l = xsize/2 - 2*width;
    w[47].h = 2*width;
    w[47].planex = -1;
    w[47].planey = 1;
    
    w[48].x = xsize/2 -width;
    w[48].y=  ysize/4 ;
    w[48].l = 2*width;
    w[48].h = 3*ysize/4;
    w[48].planex = -1;
    w[48].planey = 1;
    
    
    w[49].x = xsize -2*width;
    w[49].y=  ysize/4 ;
    w[49].l = 2*width;
    w[49].h =  ysize/2;
    w[49].planex = -1;
    w[49].planey = 1;
    
    
    
    w[50].x = 0;
    w[50].y= ysize-width;
    w[50].l = xsize/2 -13*width;
    w[50].h =  width;
    w[50].planex = -1;
    w[50].planey = 1;
    
    
    w[54].x = (xsize/2) + 3*width;
    w[54].y=  ysize/2 ;
    w[54].l = 1*width;
    w[54].h =  ysize/2;
    w[54].planex = -1;
    w[54].planey = 1;
    
    
    w[55].x = (xsize/2) -4*width;
    w[55].y=  ysize/2 ;
    w[55].l = 1*width;
    w[55].h =  ysize/2;
    w[55].planex = -1;
    w[55].planey = 1;
    
    
    w[51].x = (xsize/2) + 12*width;
    w[51].y=  ysize- width;
    w[51].l =(xsize/2) + 12*width;
    w[51].h =  width;
    w[51].planex = -1;
    w[51].planey = 1;
    
    w[52].x = (xsize/2) - 4*width;
    w[52].y=  ysize/2;
    w[52].l = width;
    w[52].h =  ysize/2;
    w[52].planex = -1;
    w[52].planey = 1;
    
    
    
    w[53].x = (xsize/2) + 8*width;
    w[53].y=  ysize - width;
    w[53].l = 2*width;
    w[53].h =  2*width;
    w[53].planex = -1;
    w[53].planey = 1;
    
    
    w[52].x = (xsize/2) - 10*width;
    w[52].y=  ysize - width;
    w[52].l = 2*width;
    w[52].h =  2*width;
    w[52].planex = -1;
    w[52].planey = 1;
    
    
    
    
    w[56].x = (xsize/2) - 13*width;
    w[56].y=  ysize/2;
    w[56].l = width;
    w[56].h =  ysize/2;
    w[56].planex = -1;
    w[56].planey = 1;
    
    w[57].x = (xsize/2) + 12*width;
    w[57].y=  ysize/2;
    w[57].l = width;
    w[57].h =  ysize/2;
    w[57].planex = -1;
    w[57].planey = 1;
    
    
    w[58].x = (xsize/2) - 13*width;
    w[58].y=  ysize/2;
    w[58].l = 9*width;
    w[58].h =  2*width;
    w[58].planex = -1;
    w[58].planey = 1;
    
    
    
    w[59].x = (xsize/2) + 3*width;
    w[59].y=  ysize/2;
    w[59].l = 9*width;
    w[59].h =  2*width;
    w[59].planex = -1;
    w[59].planey = 1;
    
    /// ROOM THREE OF MAZE
    
    
    w[60].x = 0;
    w[60].y= 0;
    w[60].l = 3*xsize/8;
    w[60].h =  width;
    w[60].planex = -2;
    w[60].planey = 1;
    
    
    w[61].x = 5*xsize/8;
    w[61].y= 0;
    w[61].l = 3*xsize/8;
    w[61].h =  width;
    w[61].planex = -2;
    w[61].planey = 1;
    
    
    
    w[62].x = 5*xsize/8;
    w[62].y= 0;
    w[62].l = width;
    w[62].h =  ysize/4;
    w[62].planex = -2;
    w[62].planey = 1;
    
    
    
    w[63].x = 3*xsize/8 - width;
    w[63].y= ysize/8;
    w[63].l = 2*width;
    w[63].h =  ysize/8;
    w[63].planex = -2;
    w[63].planey = 1;
    
    
    w[64].x = 3*xsize/8 - width;
    w[64].y= 0;
    w[64].l = width;
    w[64].h =  ysize/8;
    w[64].planex = -2;
    w[64].planey = 1;
    
    
    w[65].x = 5*xsize/8 - width;
    w[65].y= ysize/8;
    w[65].l = 2*width;
    w[65].h =  ysize/8;
    w[65].planex = -2;
    w[65].planey = 1;
    
    
    w[66].x = xsize/4 - width;
    w[66].y= 0;
    w[66].l = 1*width;
    w[66].h =  ysize/2;
    w[66].planex = -2;
    w[66].planey = 1;
    
    
    w[67].x = 3*xsize/4;
    w[67].y= 0;
    w[67].l = 1*width;
    w[67].h =  ysize/2;
    w[67].planex = -2;
    w[67].planey = 1;
    
    
    w[68].x = 0;
    w[68].y= ysize/2;
    w[68].l = 3*xsize/8 + width;
    w[68].h =  ysize/4;
    w[68].planex = -2;
    w[68].planey = 1;
    
    
    w[69].x = 5*xsize/8 - width;
    w[69].y= ysize/2;
    w[69].l = 3*xsize/8 + width;
    w[69].h =  ysize/4;
    w[69].planex = -2;
    w[69].planey = 1;
    
    
    w[70].x = 5*xsize/8 - width;
    w[70].y= ysize/2;
    w[70].l = 3*xsize/8 + width;
    w[70].h =  ysize/4;
    w[70].planex = -2;
    w[70].planey = 1;
    
    
    
    w[71].x = 0;
    w[71].y= ysize/4 ;
    w[71].l = 2*width;
    w[71].h = ysize/2;
    w[71].planex = -2;
    w[71].planey = 1;
    
    
    
    
    w[72].x = xsize -2*width;
    w[72].y=  ysize/4 ;
    w[72].l = 2*width;
    w[72].h =  ysize/2;
    w[72].planex = -2;
    w[72].planey = 1;
    
    w[73].x = 0;
    w[73].y= ysize-width;
    w[73].l = xsize/2 -13*width;
    w[73].h =  width;
    w[73].planex = -2;
    w[73].planey = 1;
    
    w[74].x = (xsize/2) + 13*width;
    w[74].y=  ysize- width;
    w[74].l =(xsize/2) - 13*width;
    w[74].h =  width;
    w[74].planex = -2;
    w[74].planey = 1;
    
    
    
    w[75].x = 5*xsize/8 - width;
    w[75].y= ysize/2;
    w[75].l = 2*width;
    w[75].h =  ysize/2;
    w[75].planex = -2;
    w[75].planey = 1;
    
    
    w[76].x = 3*xsize/8 - width;
    w[76].y= ysize/2;
    w[76].l = 2*width;
    w[76].h =  ysize/2;
    w[76].planex = -2;
    w[76].planey = 1;
    
    w[85].x = xsize/2 -11*width;
    w[85].y= ysize/2;
    w[85].l = 2*width;
    w[85].h =  ysize/2;
    w[85].planex = -2;
    w[85].planey = 1;
    
    w[86].x = (xsize/2) + 9*width;
    w[86].y=  ysize/2;
    w[86].l = 2*width;
    w[86].h =  ysize/2;
    w[86].planex = -2;
    w[86].planey = 1;
    
    
    
    //  ROOM 4 OF MAZE
    
    w[77].x = 0;
    w[77].y= 0;
    w[77].l = xsize/2 -13*width;
    w[77].h =  width;
    w[77].planex = -2;
    w[77].planey = 0;
    
    w[78].x = xsize/2 + 13*width;
    w[78].y= 0;
    w[78].l = xsize/2 -11*width;
    w[78].h =  width;
    w[78].planex = -2;
    w[78].planey = 0;
    
    
    
    w[79].x = 5*xsize/8 - width;
    w[79].y= 0;
    w[79].l = 2*width;
    w[79].h =  3*ysize/4;
    w[79].planex = -2;
    w[79].planey = 0;
    
    
    
    w[80].x = 3*xsize/8 - width;
    w[80].y= 0;
    w[80].l = 2*width;
    w[80].h =  3*ysize/4;
    w[80].planex = -2;
    w[80].planey = 0;
    
    
    
    w[81].x = 3*xsize/8 - width;
    w[81].y= 3*ysize/4;
    w[81].l = 1*width;
    w[81].h =  ysize/4;
    w[81].planex = -2;
    w[81].planey = 0;
    
    
    
    w[82].x = 5*xsize/8 - 0*width;
    w[82].y= 3*ysize/4;
    w[82].l = 1*width;
    w[82].h =  ysize/4;
    w[82].planex = -2;
    w[82].planey = 0;
    
    
    w[83].x = 3*xsize/8 - 5*width;
    w[83].y= ysize/4;
    w[83].l = 2*width;
    w[83].h =  ysize;
    w[83].planex = -2;
    w[83].planey = 0;
    
    
    w[84].x = 5*xsize/8  +3*width;
    w[84].y= ysize/4;
    w[84].l = 2*width;
    w[84].h =  ysize;
    w[84].planex = -2;
    w[84].planey = 0;
    
    
    w[87].x = xsize/2 -11*width;
    w[87].y= 0;
    w[87].l = 2*width;
    w[87].h =  ysize/4;
    w[87].planex = -2;
    w[87].planey = 0;
    
    w[88].x = (xsize/2) + 9*width;
    w[88].y=  0;
    w[88].l = 2*width;
    w[88].h =  ysize/4;
    w[88].planex = -2;
    w[88].planey = 0;
    
    
    
    w[89].x = 5*xsize/8  +3*width;
    w[89].y=  (ysize/4);
    w[89].l =3*xsize/8;
    w[89].h =  ysize/4;
    w[89].planex = -2;
    w[89].planey = 0;
    
    
    
    
    w[90].x = 0;
    w[90].y=  (ysize/4);
    w[90].l = 2*xsize/8;
    w[90].h =  ysize/4;
    w[90].planex = -2;
    w[90].planey = 0;
    
    w[91].x = 5*xsize/8  +7*width;
    w[91].y= 3*ysize/4;
    w[91].l = 2*width;
    w[91].h =  ysize/4;
    w[91].planex = -2;
    w[91].planey = 0;
    
    
  
    
    
    w[92].x = 3*xsize/8  -9*width;
    w[92].y= 3*ysize/4;
    w[92].l = 2*width;
    w[92].h =  ysize/4;
    w[92].planex = -2;
    w[92].planey = 0;
    
    w[93].x = 0;
    w[93].y= 3*ysize/4;
    w[93].l = 3*xsize/8  -11*width;
    w[93].h =  2*width;
    w[93].planex = -2;
    w[93].planey = 0;
    
    
    
    w[94].x = xsize - 3*xsize/8  +11*width;
    w[94].y= 3*ysize/4;
    w[94].l = 3*xsize/8  -11*width;
    w[94].h =  2*width;
    w[94].planex = -2;
    w[94].planey = 0;
    
    
    w[95].x = xsize - 3*xsize/8  +9*width;
    w[95].y= ysize - width;
    w[95].l = 3*xsize/8  -9*width;
    w[95].h =  2*width;
    w[95].planex = -2;
    w[95].planey = 0;
    
    
    w[96].x = 0;
    w[96].y= ysize - width;
    w[96].l = 3*xsize/8  -9*width;
    w[96].h =  2*width;
    w[96].planex = -2;
    w[96].planey = 0;
    
    
    
    //MAZE ROOM 5
    
    
    
    w[97].x = 5*xsize/8  +3*width;
    w[97].y=  0;
    w[97].l =2*width;
    w[97].h =  ysize/4;
    w[97].planex = -2;
    w[97].planey = -1;
    
    
    w[98].x = 3*xsize/8  -5*width;
    w[98].y=  0;
    w[98].l =2*width;
    w[98].h =  ysize/4;
    w[98].planex = -2;
    w[98].planey = -1;
    
    
    
    w[99].x = 5*xsize/8  +0*width;
    w[99].y=  0;
    w[99].l =1*width;
    w[99].h =  ysize/4 + 2*width ;
    w[99].planex = -2;
    w[99].planey = -1;
    
    w[100].x = 3*xsize/8  -1*width;
    w[100].y=  0;
    w[100].l =1*width;
    w[100].h =  ysize/4 + 4*width ;
    w[100].planex = -2;
    w[100].planey = -1;
    
    
    w[101].x = 5*xsize/8  -0*width;
    w[101].y=  ysize/4 + 2*width;
    w[101].l = xsize/4;
    w[101].h =   2*width ;
    w[101].planex = -2;
    w[101].planey = -1;
    
    
    w[102].x = 3*xsize/8  -9*width;
    w[102].y=  ysize/4 + 2*width;
    w[102].l = xsize/4;
    w[102].h =   2*width ;
    w[102].planex = -2;
    w[102].planey = -1;
    
    
    w[103].x = 5*xsize/8  +7*width;
    w[103].y=  0;
    w[103].l =2*width;
    w[103].h =  ysize/4 +4*width;
    w[103].planex = -2;
    w[103].planey = -1;
    
    
    
    w[104].x = 3*xsize/8  -9*width;
    w[104].y=  0;
    w[104].l = 2*width;
    w[104].h =   ysize/4  +2*width;
    w[104].planex = -2;
    w[104].planey = -1;
    
    
    
    w[105].x = 0;
    w[105].y= 0;
    w[105].l = (xsize/2) - 13*width;
    w[105].h =  width;
    w[105].planex = -2;
    w[105].planey = -1;
    
    
    w[106].x = xsize-((xsize/2) - 13*width);
    w[106].y= 0;
    w[106].l = (xsize/2) - 13*width;
    w[106].h =  width;
    w[106].planex = -2;
    w[106].planey = -1;
    
    w[107].x = 0;
    w[107].y= ysize/4 ;
    w[107].l = 2*width;
    w[107].h = ysize/2;
    w[107].planex = -2;
    w[107].planey = -1;
    
    w[108].x = xsize -2*width;
    w[108].y= ysize/4 ;
    w[108].l = 2*width;
    w[108].h = ysize/2;
    w[108].planex = -2;
    w[108].planey = -1;
    
    w[109].x = 0;
    w[109].y= 3*ysize/4 -2*width;
    w[109].l = xsize;
    w[109].h = 2*width;
    w[109].planex = -2;
    w[109].planey = -1;
    
    w[110].x = 0;
    w[110].y= ysize -1*width;
    w[110].l = xsize;
    w[110].h = 1*width;
    w[110].planex = -2;
    w[110].planey = -1;
    
    w[111].x = xsize/2 -width;
    w[111].y=  3*ysize/4;
    w[111].l =  2*width;
    w[111].h =  ysize/4;
    w[111].planex = -2;
    w[111].planey = -1;
    
    // this part turns all of the maze blue
    for (i=25; i < 112; i++)
        w[i].color = b;
    
    //BLACK CASTLE
    
    w[112].x = 0;
    w[112].y= 0;
    w[112].l = 3*xsize/8;
    w[112].h =  width;
    w[112].planex = -2;
    w[112].planey = 2;
    
    
    w[113].x = (5*xsize/8);
    w[113].y= 0;
    w[113].l = 3*xsize/8;
    w[113].h =  width;
    w[113].planex = -2;
    w[113].planey = 2;
    
    w[114].x = (5*xsize/8);
    w[114].y= ysize-width;
    w[114].l = 3*xsize/8;
    w[114].h =  width;
    w[114].planex = -2;
    w[114].planey = 2;
    
    
    w[115].x = 0;
    w[115].y= ysize-width;
    w[115].l = 3*xsize/8;
    w[115].h =  width;
    w[115].planex = -2;
    w[115].planey = 2;
    
    w[120].x = 0;
    w[120].y= 0;
    w[120].l = width;
    w[120].h =  ysize;
    w[120].planex = -2;
    w[120].planey = 2;
    
    
    
    w[121].x = xsize-width;
    w[121].y= 0;
    w[121].l = width;
    w[121].h =  ysize;
    w[121].planex = -2;
    w[121].planey = 2;
    
    
    
    w[129].x = xsize/2-10*width;
    w[129].y= 0;
    w[129].l = width;
    w[129].h =  4*width;
    w[129].planex = -2;
    w[129].planey = 2;
    
    
    w[130].x = xsize/2-8*width;
    w[130].y= 0;
    w[130].l = width;
    w[130].h =  4*width;
    w[130].planex = -2;
    w[130].planey = 2;
    
    
    
    
    w[131].x = xsize/2-6*width;
    w[131].y= 0;
    w[131].l = width;
    w[131].h =  4*width;
    w[131].planex = -2;
    w[131].planey = 2;
    
    
    w[132].x = xsize/2-4*width;
    w[132].y= 0;
    w[132].l = width;
    w[132].h =  4*width;
    w[132].planex = -2;
    w[132].planey = 2;
    
    
    w[133].x = xsize/2+3*width;
    w[133].y= 0;
    w[133].l = width;
    w[133].h =  4*width;
    w[133].planex = -2;
    w[133].planey = 2;
    
    w[134].x = xsize/2+5*width;
    w[134].y= 0;
    w[134].l = width;
    w[134].h =  4*width;
    w[134].planex = -2;
    w[134].planey = 2;
    
    
    
    w[135].x = xsize/2+7*width;
    w[135].y= 0;
    w[135].l = width;
    w[135].h =  4*width;
    w[135].planex = -2;
    w[135].planey = 2;
    
    
    w[136].x = xsize/2-10*width;
    w[136].y= 4*width;
    w[136].l = 7*width;
    w[136].h =  10*width;
    w[136].planex = -2;
    w[136].planey = 2;
    
    
    w[137].x = xsize/2+9*width;
    w[137].y= 0;
    w[137].l = width;
    w[137].h =  4*width;
    w[137].planex = -2;
    w[137].planey = 2;
    
    w[138].x = xsize/2+3*width;
    w[138].y= 4*width;
    w[138].l = 7*width;
    w[138].h =  10*width;
    w[138].planex = -2;
    w[138].planey = 2;
    
    w[139].x = xsize/2-8*width;
    w[139].y= 10*width;
    w[139].l = 16*width;
    w[139].h =  7*width;
    w[139].planex = -2;
    w[139].planey = 2;
    w[139].door = 2;

    w[140].x = xsize/2-8*width;
    w[140].y= 17*width;
    w[140].l = 5*width;
    w[140].h =  3*width;
    w[140].planex = -2;
    w[140].planey = 2;
    
    w[141].x = xsize/2+3*width;
    w[141].y= 17*width;
    w[141].l = 5*width;
    w[141].h =  3*width;
    w[141].planex = -2;
    w[141].planey = 2;
    
    // MAGNENT ROOM
    
    w[116].x = 0;
    w[116].y= 0;
    w[116].l = 3*xsize/8;
    w[116].h =  width;
    w[116].planex = -2;
    w[116].planey = 3;
    
    w[117].x = (5*xsize/8);
    w[117].y= 0;
    w[117].l = 3*xsize/8;
    w[117].h =  width;
    w[117].planex = -2;
    w[117].planey = 3;
    
    w[118].x = (5*xsize/8);
    w[118].y= ysize-width;
    w[118].l = 3*xsize/8;
    w[118].h =  width;
    w[118].planex = -2;
    w[118].planey = 3;
    
    w[119].x = 0;
    w[119].y= ysize-width;
    w[119].l = 3*xsize/8;
    w[119].h =  width;
    w[119].planex = -2;
    w[119].planey = 3;
    
    w[122].x = 0;
    w[122].y= 0;
    w[122].l = width;
    w[122].h =  ysize;
    w[122].planex = -2;
    w[122].planey = 3;
    
    w[123].x = xsize-width;
    w[123].y= 0;
    w[123].l = width;
    w[123].h =  ysize;
    w[123].planex = -2;
    w[123].planey = 3;
    
    // CHALICE ROOM
    
    w[124].x = 0;
    w[124].y= 0;
    w[124].l = width;
    w[124].h =  ysize;
    w[124].planex = -2;
    w[124].planey = 4;
    
    w[125].x = xsize-width;
    w[125].y= 0;
    w[125].l = width;
    w[125].h =  ysize;
    w[125].planex = -2;
    w[125].planey = 4;
    
    w[126].x = 0;
    w[126].y= ysize-width;
    w[126].l = 3*xsize/8;
    w[126].h =  width;
    w[126].planex = -2;
    w[126].planey = 4;
    
    w[127].x = (5*xsize/8);
    w[127].y= ysize-width;
    w[127].l = 3*xsize/8;
    w[127].h =  width;
    w[127].planex = -2;
    w[127].planey = 4;
    
    w[128].x =0;
    w[128].y= 0;
    w[128].l = xsize;
    w[128].h =  width;
    w[128].planex = -2;
    w[128].planey = 4;
    
    
    //THIS ESTABLISHES EACH EACH WALL AS NOT A DOOR
    for (i=0; i<wallmax; i++)
    {
        w[i].alive = 0;
        w[i].door = 0;
        if ((w[i].planex == -1) && (w[i].planey==0))
            w[i].color = b;
        if ((w[i].planex == -2) && (w[i].planey==2))
                w[i].color = black;
        if ((w[i].planex == -2) && (w[i].planey==3))
            w[i].color = maroon;
        if ((w[i].planex == -2) && (w[i].planey==4))
                w[i].color = p;
        if ((w[i].planex == -1) && (w[i].planey==-1))
            w[i].color = p2;
        if ((w[i].planex == 0) && (w[i].planey==-1))
            w[i].color = g;
        if ((w[i].planex == 1) && (w[i].planey==-1))
            w[i].color = g;
        if ((w[i].planex == 1) && (w[i].planey==-2))
            w[i].color = o;
    }
    // THIS ESTABLISHES EACH DOOR
    w[157].door = 1;
    w[139].door = 2;
    
    // THIS LETS YOU KOW WHICH WHAT WAS THE PREVIOUS ITEM, SO YOU CAN'T PICK UP AN ITEM AS SOON AS YOU DROP IT
    int prev;
    
    
    //  THIS IS AN ARRAY OF ALL ITEMS
    struct obj items[15];
    
    // ITEMS[1] IS THE SWORD
    items[1].x = 50;
    items[1].y = 50;
    items[1].id = 3;
    items[1].planex = 0;
    items[1].planey = 1;
    
    items[1].color.r = 255;
    items[1].color.g = 213;
    items[1].color.r = 119;
    
    // ITEMS[2] IS THE DRAGON
    items[2].x = 10;
    items[2].y = 10;
    items[2].id = 4;
    items[2].color.r = 204;
    items[2].color.g = 92;
    items[2].color.r = 60;
    items[2].alive = 1;
    items[2].planex = 1;
    items[2].planey = -2;
    
    // ITEMS[3] IS THE CHALACE
    items[3].x = xmid;
    items[3].y = ymid;
    items[3].id = 5;
    items[3].color.r = 204;
    items[3].color.g = 92;
    items[3].color.r = 60;
    items[3].alive = 1;
    items[3].planex = -2;
    items[3].planey = 4;
    
    // ITEMS[5] IS THE GOLD KEY
    items[5].x = 3*width;
    items[5].y = 3*width;
    items[5].id = 7;
    items[5].color.r = 204;
    items[5].color.g = 92;
    items[5].color.r = 60;
    items[5].alive = 1;
    items[5].planex = 0;
    items[5].planey = 0;
    
    // ITEMS[6] IS THE BLACK KEY
    items[6].x = 3*width;
    items[6].y = 3*width;
    items[6].id = 8;
    items[6].color.r = 0;
    items[6].color.g = 0;
    items[6].color.r = 0;
    items[6].alive = 1;
    items[6].planex = 1;
    items[6].planey = -2;
    
    // INITIALLY DRAW YOUR CHARACTER
    drawCharacter(you.x , you.y);
    
    
    // DRAWS ALL CHARACTERS ON THE SAME PLANE AS THE CHARACTER
    for (i =1; i<itemsmax; i++)
        {
        if (items[i].planex == you.planex)
            if (items[i].planey ==you.planey)
                draw(items[i]);
        }
    

    // THIS ESTABLISHES THE CLEAR COLOR TO EMULATE THE ACTUAL BACKGROUND FROM THE ATARI GAME
    gfx_clear_color(bg.r,bg.g,bg.b);
    
    
    
    
    while(1) {
        
        
        // J IS INCRIMENTED
        j++;
        
        
        // IF A KEY IS PRESSED, IT CAPTURES THAT KEY AND STORES IT AS 'C'
        if (gfx_event_waiting())
        {
            c = gfx_wait();
            
        }
        
        
        
        
        // THE GAME ADJUSTS BASED ON THE INPUTTED CHARACTER ON THE KEYBOARD
        switch (c)
        {
            case 'Q':
            case 'a': // GO WEST
                you.x-=speed;
                // EACH WALL IS CHECKED TO MAKE SURE THE MOVE IS WITHIN BOUNDS, IF IT IS NOT, THEN THE MOVE IS CHANGED BACK
                for (i = 1; i<wallmax; i++)
                    if (collisionWall(w[i], you))
                        you.x +=speed;
                break;
            case 'S':
            case 'd': // GO EAST
                you.x+=speed;
                // EACH WALL IS CHECKED TO MAKE SURE THE MOVE IS WITHIN BOUNDS, IF IT IS NOT, THEN THE MOVE IS CHANGED BACK
                for (i = 1; i<wallmax; i++)
                    if (collisionWall(w[i],you))
                        you.x-=speed;
                break;
            case 'R':
            case 'w': // GO NORTH
                you.y -=speed;
                // EACH WALL IS CHECKED TO MAKE SURE THE MOVE IS WITHIN BOUNDS, IF IT IS NOT, THEN THE MOVE IS CHANGED BACK
                for (i = 1; i<wallmax; i++)
                    if (collisionWall(w[i], you))
                    {
                        // THIS CHECKS IF YOU ARE ENTERING A DOOR, AND HOLDING A KEY. IF SO, YOU CAN PROCEDE FORWARD
                        if ((you.obj == 7 ) && (w[i].door==1))
                            w[i].alive = 1;
                        if ((you.obj ==8) && (w[i].door == 2))
                            w[i].alive =1;
                        else{
                        you.y +=speed;
                        }
                    }
                break;
                
            case 's': // GO SOUTH
                you.y +=speed;
                // EACH WALL IS CHECKED TO MAKE SURE THE MOVE IS WITHIN BOUNDS, IF IT IS NOT, THEN THE MOVE IS CHANGED BACK
                for (i = 1; i<wallmax; i++)
                    if (collisionWall(w[i],you))
                        you.y -=speed;
                break;
                
            case ' ': // DROP ITEM
                //MAKES YOUR PAST ITEM "PREV" SO YOU DON'T ACCIDENTALLY IMMEDIATELY PICK IT UP
                prev = you.obj;
                // YOU NO LONGER HAVE THE PROPERTIES OF ONE WHO HOLDS THAT ITEM
                you.obj = 0;
                break;
            default:
                break;
                
                
        }
        
        
        while(1)
        { // THIS IS CONTINUALLY BEING CHECKED,REGUARDLESS OF WHETHER OR NOT YOU ARE INPUTTING ANYTHING
        
        
        // ALLOWS YOU TO PICK UP THE SWORD BY VERIFYING YOU DIDN'T IMMEDIATELY DROP IT, AND YOU ARE TOUCJING IT
            if (prev != items[1].id)
                if (collision3(you,items[1]))
                {
                prev =  you.obj;
                you.obj = items[1].id;
                }
            
            //ALLOWS YOU TO PICK UP THE GOLD KEY
            if (prev != items[5].id)
                if (collision3(you,items[5]))
                {
                    prev =  you.obj;
                    you.obj = items[5].id;
                    
                }
            // ALLOWS YOU TO PICK UP THE BLACK KEY
            if (prev != items[6].id)
                if (collision3(you,items[6]))
                {
                    prev =  you.obj;
                    you.obj = items[6].id;
                }
            // ALLOWS YOU TO PICK UP THE CHALIC
            if (prev != items[3].id)
                if (collision3(you,items[3]))
                {
                    prev =  you.obj;
                    you.obj = items[3].id;
                    
                }
            // DETERMINES IT YOU HAVE CONTACTED THE DRAGON, KILLS DRAGON IF YOU ARE HOLDING SWORD
            if (collision3(you,items[2]))
            {
                if(you.obj == items[1].id)
                   items[2].alive = 0;
                else{
                   prev =  you.obj;
                    you.obj = items[2].id;
                   }
            }
        // DETERMINES WHAT HAPPENS WHEN YOU ARE 'HOLDING' CERTIAN ITEMS
        switch (you.obj)
        {
            case 3: // THE OBJECT ID FOR THE SWORD IS 3
                // WHEN YOU ARE HOLDING THE SWORD, THE SWORD STAYS WITH YOU
                items[1].x = you.x;
                items[1].y = you.y;
                items[1].planex = you.planex;
                items[1].planey = you.planey;
                break;
                
            case 4:// THE OBJECT ID FOR THE DRAGON IS 4
                // IF THE DRAGON IS ALIVE AND YOU WERE IN CONTACT WITH THE DRAGON, THEN YOU BECOME DEAD
                if (items[2].alive == 1)
                you.alive = 0;
                break;
                
            case 5:// THE OBJECT ID FOR THE CHALICE IS 5
                //WHEN YOU ARE HOLDING THE CHALICE, THE CHALICE STAYS WITH YOU
                items[3].x = you.x;
                items[3].y = you.y;
                items[3].planex = you.planex;
                items[3].planey = you.planey;
                break;
                
            case 7:  // THE OBEJCT ID FOR THE GOLD KEY IS 7
                // WHEN YOU ARE HOLDING THE GOLD KEY, THE GOLD KEY STAYS WITH YOU
                items[5].x = you.x;
                items[5].y = you.y;
                items[5].planex = you.planex;
                items[5].planey = you.planey;
                break;
            
            case 8:// THE OBJECT ID FOR THE BLACK KEY IS 8
                // WHEN YOU ARE HOLDING THE BLACK KEY,THE BLACK KEY STAYS WITH YOU
                items[6].x = you.x;
                items[6].y = you.y;
                items[6].planex = you.planex;
                items[6].planey = you.planey;
                break;
                
                
            case 0: break;// WHEN YOU ARE HOLDING NOTHING, NOTHING SPECIAL HAPPENS
        }
        
        // THIS PART OF THE CODE ALLOWS FOR THE DRAGON TO FOLLOW YOU
            j++;// THIS ALLOWS FOR THE DRAGON TO MOVE EVEN WHEN YOU AREN'T
        if((you.alive)&&(items[2].alive)) // THE DRAGON ONLY CHASES YOU IF YOU ARE BOTH ALVIE
            if ((items[2].planex == you.planex) && (items[2].planey == you.planey)) // THE DRAGON ONLY CHASES YOU IF YOU ARE IN THE SAME ROOM
                if((j%50) == 0) // IF THE DRAGON POSITTION CHANGED EVERY TIME IT WENT THROUGH THIS PART OF THE LOOP, IT WOULD BE TOO FAST.  THIS ALLOWS IT TO DO IT EVERY 50TH TIME TO MAKE ITS SPEED MORE REASONABLE
                {
                    
                    // TO CALCULATE  THE ANGLE THE DRAGON APPROACHS, THE DIFFERENCE IN X AND Y ARE CALCULATED FIRST
                dx  = items[2].x- you.x;
                dy =  -you.y + items[2].y;
                    if (!dy==0) // IF THE CHANGE IN Y IS 0, THIS PART WILL CRASH, THUS THIS EXCEPTION IS NECESSARY
                    {
                        if (dy<0) ///DETERMINES THE X AND Y CHANGE BASED ON THE CALCULATED ANGLE
                        {
                            theta = atan(dx/dy);
                            items[2].x += 5* sin(theta);
                            items[2].y += 5* cos(theta);
                        }
                        if (dy>0) // SAME AS ABOVE
                        {
                            theta = atan(dx/dy);
                            items[2].x -= 5* sin(theta);
                            items[2].y -= 5* cos(theta);
                        }
                    }
                    else if (dy==0) // IF DY = 0, ONLY MOVE ALONG THE X COORDINATE
                    {
                        if (dx ==0)
                            continue;
                        else if (dx>0)
                            items[2].x -= 5;
                        else if (dx <0)
                            items[2].x += 5;
                        else continue;
                    }
                }
            
            
            usleep(25000); // THIS WAIT BLOCK IS NECESSARY FOR THE ANIMATION TO APPEAR
            gfx_clear();// CLEARS THE SCREEN SO YOU IT CAN BE REDRAWN
            drawCharacter(you.x,you.y); // DRAWS THE CHARACTER
           
            
            // DRAWS ALL WALLS IN THE SAME ROOM AS YOU
            for (i = 1; i<wallmax; i++)
            {
                if (w[i].planex == you.planex)
                    if (w[i].planey == you.planey)
                        wall(w[i]);
            }
            
            // DRAWS ALL ITEMS IN THE SAME ROOM AS YOU
            for (i =1; i<itemsmax; i++)
            {
                if (items[i].planex == you.planex)
                    if (items[i].planey == you.planey)
                        draw(items[i]);
            }
            
            // IF YOU ARE DEAD, YOU CANNOT MOVE BEYOND THE BOUNDS OF THE DRAGON'S BELLY
            if (you.alive == 0)
            {
                if (you.x>(items[2].x +belly))
                {
                    you.x = items[2].x;
                }
                if (you.x<(items[2].x -belly))
                {
                    you.x = items[2].x;
                }
                if (you.y>(items[2].y+belly))
                {
                    you.y = items[2].y;
                }
                if (you.y<(items[2].y -belly))
                {
                    you.y = items[2].y;
                }
            }
            
            
            gfx_flush();// FLUSHES THE OUTPUT TO THE SCREEN
            
        
        // IF YOU GO OUTSIDE OF THE WINDOW, THEN YOU MOVE TO A DIFFERENT ROOM AND YOUR AND Y COORDINATE CHANGE
        if (you.x>xsize)
        {
            // THESE ARE A FEW EXCEPTION WHERE YOU DONT GO IMMEDIATELY TO THE NEXT ROOM OVER WHEN LEAVING A ROOM, AND THEY ARE USED IN THE MAZE
            if ((you.planey == 0) && (you.planex == -1))
            {
                you.planex = -2;
                you.planey = 0;
                you.x-=xsize;
            }
            
            if ((you.planey == 1) && (you.planex == -1))
            {
                you.planex = -2;
                you.planey = -1;
                you.x-=xsize;
            }
            
            if ((you.planey == -1) && (you.planex == -2))
            {
                you.planex = -2;
                you.planey = 1;
                you.x-=xsize;
            }
            else{
            you.x-=xsize;
            you.planex+=1;
            }
            
        }
        if (you.x<0)
        {
            // SAME AS ABOVE, USED FOR MAZE
            if ((you.planey == 0) && (you.planex == -2))
            {
                you.planex = -1;
                you.planey = 0;
                you.x+=xsize;
            }
            if ((you.planey == -1) && (you.planex == -2))
            {
                you.planex = -1;
                you.planey = 1;
                you.x+=xsize;
            }
            if ((you.planey == +1) && (you.planex == -2))
            {
                you.planex = -2;
                you.planey = -1;
                you.x+=xsize;
            }
            else{
            
            you.x+=xsize;
            you.planex-=1;
            }
        }
        if (you.y>ysize)
        {
            you.y-=ysize;
            you.planey-=1;
        }
        if (you.y<0)
        {
            you.y+=ysize;
            you.planey+=1;
        
        }
         
         
        // IF YOU TYPE A KEY, THE SEQUENCE IS BROKEN SO THE SCREEN CAN REFLECT THE RESULTS OF THAT KEY
        if (gfx_event_waiting())
            break;
        }
        
        
        // IF YOU ARE HOLDING THE CHALICE, AND INSIDE OF THE GOLD CASTLE, YOU WIN, AND THE GAME PAUSES FOR 5 SECONDS
        if (you.obj == items[3].id)
            if (you.planex == 0)
                if (you.planey == 1)
        {
            win = 1;
            printf("\t you win! \n");
            sleep(5);
            break;
        }
        
        
        // IF YOU PRESS THE 'P' KEY, YOU QUIT THE GAME
        if(c=='p')
            break;
    }
}






void drawSword( int x, int y)
{ // THIS FUNCTION DRAWS PIXEL ART OF A SWORD
    
    gfx_color(255,247,0); // THIS MAKES SURE THE SWORD IS YELLOW
    
    int pixel = 3; // THIS CAN CHANGE THE PROPORTIONALITY OF THE SWORD
    
    // DRAWS THE SWORDS' RECTANGLES ONE BY ONE
    gfx_fill_rectangle(  x-(0*pixel), y-(-0*pixel) , 8*pixel, 1*pixel );
    gfx_fill_rectangle(  x-(-1*pixel), y-(1*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x-(-2*pixel), y-(-2*pixel) , 1*pixel, 1*pixel );
    gfx_fill_rectangle(  x-(-2*pixel), y-(-2*pixel) , 1*pixel, 1*pixel );
    gfx_fill_rectangle(  x-(-2*pixel), y-(2*pixel) , 1*pixel, 1*pixel );
}



void drawCharacter(int x, int y)
{
    // THIS FUNCTION DRAWS A LITTLE SQUARE TO REPRESENT THE HERO
    gfx_fill_rectangle( x-6, y-6, 12, 12 );
}

int collision3(struct hero x, struct obj y) // COLLISION 1 AND 2 WERE USED TO TEST, THIS IS THE REAL DEAL
{
    if ((x.planex == y.planex) && (x.planey == y.planey))
        if ((x.x + 7 >= y.x) && ( x.x - 7 <= y.x))
            if ((x.y + 7 >= y.y) && ( x.y - 7 <= y.y)) // IF THE OBJECT IS IN THE SAME ROOM, AND WITHIN A RANGE OF X AND Y COORDINATES SUITABLE, IT IS REGISTERED AS A COLLISION, RETURNING 1
                return 1;
    
    
    return 0;// OTHERWISE, THE FUNCTION RETURNS ZERO
}

void draw(struct obj x)// THIS IS A MULTIPURPOSE FUNCTION THAT CAN BE CALLED FOR NEARLY ANY ITEM
{
    // USES THE OBJECT'S ID TO DETERMINE WHAT IT DRAWS
    switch (x.id)
    {
            
        case 8: // BLACK KEY
            drawKeyBlack(x);
            break;
        case 7: // GOLD KEY
            drawKey(x);
            break;
        case 5:// CHALICE
            drawChalice(x);
            break;
            
        case 3: // SWORD
            drawSword(x.x,x.y);
            break;
            
        case 4: // DRAGON
            drawDragon(  x.x,  x.y);
            break;
    }
    
}


void drawDragon( int x, int y)
{ // DRAWS PIXEL ART OF A DRAGON
    int pixel = 3; // USED FOR SCALE
    // CHANGES COLOR TO RED
    gfx_color(204,92,60);
    
    // DRAWS EACH RECTANGLE ONE BY ONE
    gfx_fill_rectangle(  x-(4*pixel), y-(2*pixel) , 2*pixel, 5*pixel );
    gfx_fill_rectangle(  x-(4*pixel), y-(10*pixel) , 4*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(0*pixel), y-(9*pixel) , 3*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(-1*pixel), y-(7*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(0*pixel), y-(11*pixel) , 4*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(-1*pixel), y-(12*pixel) , 2*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(3*pixel), y-(3*pixel) , 2*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(2*pixel), y-(4*pixel) , 6*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(1*pixel), y-(5*pixel) , 4*pixel, 3*pixel );
    gfx_fill_rectangle(  x-(-2*pixel), y-(4*pixel) , 2*pixel, 7*pixel );
    gfx_fill_rectangle(  x-(-1*pixel), y-(-1*pixel) , 3*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(0*pixel), y-(-5*pixel) , 4*pixel, 1*pixel );
    gfx_fill_rectangle(  x-(-3*pixel), y-(-5*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x-(0*pixel), y-(-4*pixel) ,   1*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(2*pixel), y-(-2*pixel) ,   4*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(2*pixel), y-(-7*pixel) , 6*pixel, 1*pixel );
    gfx_fill_rectangle(  x-(2*pixel), y-(-6*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(4*pixel), y-(-5*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x-(4*pixel), y-(-6*pixel) , 3*pixel, 1*pixel );
    // CHANGES THE COLOR TO BACKGROUND GREY TO DRAW THE EYE
    gfx_color(219,219,219);
    // DRAWS EYE
    gfx_fill_rectangle(  x-(0*pixel), y-(10*pixel) ,   2*pixel, 1*pixel );
    //COLOR BACK TO RED
    gfx_color(204,92,60);
}

void wall( struct wall x)
{
    // CHANGES THE COLOR TO THE COLOR THE WALL IS SUPPOSED TO BE
    gfx_color(x.color.r,x.color.g,x.color.b);
    // DRAWS THE RECTANGULAR WALL
    gfx_fill_rectangle( x.x, x.y , x.l, x.h );
    
}



int collisionWall( struct wall x, struct hero y)// THIS FUNCTION MAKES SURE THE WALL IS NOT AN UNLOCKED DOOR ('LIVE") AND THEN RETURNS A ONE IF YOU COLLIDE WITH IT.  OTHER WISE IT RETURNS A ZERO
{
    if (x.alive == 1)
        return 0;
    if ((x.planex == y.planex) && (x.planey == y.planey))
    {
        if (((y.x + (y.size/2))> (x.x)) && ((y.x - (y.size/2))< (x.x + x.l)))
            if (((y.y + (y.size/2))> (x.y)) && ((y.y - (y.size/2))< (x.y + x.h)))
                return 1;
        
    }
    
    return 0;
    
}



void drawChalice(struct obj x)
{// DRAW PIXEL ART OF A CHALICE
    int pixel = 3; // USED FOR SCALE
    gfx_color(255,247,0); // CHANGES COLOR TO GOLD
    gfx_fill_rectangle(  x.x-(0*pixel), x.y-(-0*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x.x-(-1*pixel), x.y-(-2*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x.x-(-2*pixel), x.y-(-3*pixel) , 4*pixel, 3*pixel );
    gfx_fill_rectangle(  x.x-(-3*pixel), x.y-(-3*pixel) , 2*pixel, 6*pixel );
    gfx_fill_rectangle(  x.x-(-1*pixel), x.y-(-8*pixel) , 6*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-7*pixel), x.y-(-0*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x.x-(-6*pixel), x.y-(-2*pixel) , 1*pixel, 3*pixel );
}


void drawKey( struct obj x)
{ // DRAWS PIXEL ART OF A KEY
    int pixel = 3; // USED FOR SCALE
    
    // CHANGES COLOR TO GOLD/YELLOW
    gfx_color(255,247,0);
    
    // DRAWS RECTANGLES ONE BY ONE
    gfx_fill_rectangle(  x.x-(0*pixel), x.y-(-0*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x.x-(-1*pixel), x.y-(-0*pixel) , 1*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-2*pixel), x.y-(-0*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x.x-(-3*pixel), x.y-(-0*pixel) , 1*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-4*pixel), x.y-(1*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x.x-(-4*pixel), x.y-(1*pixel) , 3*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-4*pixel), x.y-(-1*pixel) , 3*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-7*pixel), x.y-(1*pixel) , 1*pixel, 3*pixel );
}

void drawKeyBlack( struct obj x)
{// JUST LIKE THE LAST ONE, EXCEPT THIS TIME THE KEY IS BLACK
    int pixel = 3;
    gfx_color(0,0,0);
    gfx_fill_rectangle(  x.x-(0*pixel), x.y-(-0*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x.x-(-1*pixel), x.y-(-0*pixel) , 1*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-2*pixel), x.y-(-0*pixel) , 1*pixel, 2*pixel );
    gfx_fill_rectangle(  x.x-(-3*pixel), x.y-(-0*pixel) , 1*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-4*pixel), x.y-(1*pixel) , 1*pixel, 3*pixel );
    gfx_fill_rectangle(  x.x-(-4*pixel), x.y-(1*pixel) , 3*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-4*pixel), x.y-(-1*pixel) , 3*pixel, 1*pixel );
    gfx_fill_rectangle(  x.x-(-7*pixel), x.y-(1*pixel) , 1*pixel, 3*pixel );
}

