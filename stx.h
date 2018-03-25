/*
    SNAKEC 0.01(ALPHA_EDITION)
  ______      ____    __      _ _       _    _    ______
/  ___\_\   | \ \\  | ||    / \ \\    | || / // |   __ ||
| ||        | |\ \\ | ||   / //\ \\   | ||/ //  | ||
\ \\_____   | ||\ \\| ||  / /===\ \\  | |  //   | |=====
    ---\\\  | || \ \| || / /_____\ \\ | || \\   |   ___||
 ______|| | | ||  \ | || | ||    | || | ||\ \\  | ||___
 \____ ///  |_||   \|_|| |_||    | || |_|| \_\\ |_____ ||
*/
#ifndef STX_H
#define STX_H

#include <windows.h>
#include <cstdio>
#include <cstdlib> 
#include <conio.h>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>
#define LL long long
#define INTPTR int*
#define CHARPTR char*
#define ABS(X) X>0?X:-X
#define DOUBLE(x) x*x
#define LEN(ARRAY,TYPE) (sizeof(ARRAY)/sizeof(TYPE))
#define MAX(x,y) x>y?x:y 
#define MIN(x,y) x>y?y:x
#define RAN(x) rand()%x

/*err tracker*/
typedef unsigned int STATUS; 
#define SUCCEED 0
#define NORM_FINISH 1
#define ABNORM_FINISH 2
#define OVERFLOWED 3
//=======================================================
/*
//@sPOINT
//@LINE
//@WINDOW
*/
/*
    sPOINT. It's just a point on the map.
    X:X position
    Y:Y position
*/
struct sPOINT{
    int X, Y;
    sPOINT();
    sPOINT(int x, int y);
    ~sPOINT();
    sPOINT operator ~();
    sPOINT operator +(const sPOINT B);
    sPOINT operator -(const sPOINT B);
    sPOINT operator /(const int B);
    bool operator >(const sPOINT B);
    bool operator ==(const sPOINT B);
    //WARNING: >> means "in"
    bool operator >>(const sPOINT *B);
    friend float Abs(sPOINT  A);
    friend sPOINT meta(sPOINT A, sPOINT B);
};
/*
    Window vector
*/
struct LINE{
    int X_1, Y_1, X_2, Y_2;
    char COLOR;
    LINE();
    LINE(int x_1, int y_1, int x_2, int y_2);
    LINE(int x_1, int y_1, int x_2, int y_2, char color);
};
/*
    MAIN REGISTER AND PAINTER
*/
struct WINDOW{
    int X, Y, WIDTH ,HEIGHT, WUUID;
    std::vector<LINE> MAP;
    char BACKGROUND;
    WINDOW();
    WINDOW(int x, int y, int width, int height, int uuid);
    WINDOW(int x, int y, int width, int height, char color, int uuid);
    void DRAWLINE(sPOINT A, sPOINT B);
    void DRAWLINE(sPOINT A, sPOINT B, char color);
    void CLEARLINE();
    char WBACKGROUND();
    std::vector<LINE>::iterator lend();   
    std::vector<LINE>::iterator lbegin();
    int lsize();
};
//=========================================================
/*
    keyboard listener
*/
void *get_key(void *key);
class KEYBOARD{
    private:
        char _KEY;
        pthread_t KEY_THREAD;    
    public:
        KEYBOARD();
        //0:success;1:normal exit;-1:bad exit;
        int LISTEN();
        int STOP();
        char THISKEY();
        ~KEYBOARD();
};
//=========================================================
class SMAP{
    private:
        int MWIDTH, MHEIGHT;
        int WNUM;
        std::vector<WINDOW> REGISTED;
        char BITMAP[127][127];
    public:
        SMAP(int LEN_X, int LEN_Y);
        ~SMAP();
        int REGISTER(int X, int Y, int WIDTH, int HEIGHT, char BCOLOR);
        int UNREG(int uuid);
        void CLEARWINDOW(int uuid);
        int PAINT(int uuid, sPOINT A, sPOINT B);
        int PAINT(int uuid, sPOINT A, sPOINT B, char COLOR);
        void PAINTMAIN();
        void PRINTSCR();
};
//=========================================================
#endif

//INCLUDE WRITES HERE