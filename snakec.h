/*
    SNAKEC 0.01(ALPHA_EDITION)
  ______      ____    __      _ _       _    _    ______
/  ___\_\   | \ \\  | ||    / \ \\    | || / // |   __ ||
| ||        | |\ \\ | ||   / //\ \\   | ||/ //  | ||
\ \\_____   | ||\ \\| ||  / /===\ \\  | |  //   | |=====
    ---\\\  | || \ \| || / /_____\ \\ | || \\   |   ___||
 ______|| | | ||  \ | || | ||    | || | ||\ \\  | ||___
 \____ ///  |_||   \|_|| |_||    | || |_|| \_\\ |_____ ||

It's called snake core for it's basicly build for my snake project
==================================================================
 * Copyright(c) 1999-2018 NyancoChan 100% Indivisual
 *  
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would
 *    be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
=================================================================
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

#define CALLBACK __stdcall

#define LL long long
#define INTPTR int*
#define CHARPTR char*
#define ABS(X) X>0?X:-X
#define DOUBLE(x) x*x
#define LEN(ARRAY,TYPE) (sizeof(ARRAY)/sizeof(TYPE))
#define MAX(x,y) x>y?x:y 
#define MIN(x,y) x>y?y:x
#define RAN(x) rand()%x

/*=======================================================
*
* @defgroup error handleing 
* 
* @defgroup Keyinput
*
* @defgroup smap(NOT THAT GUI)
*
=========================================================*/
/*err tracker*/
typedef unsigned int STATUS; 
// success
#define SUCCEED             0
// normal exit
#define NORM_FINISH         1
// abnormal exit without anyreason
#define ABNORM_FINISH       2
// overflow
#define OVERFLOWED          3

/*key input*/
typedef char KEY_VALUE;        //key_num
#define KEY_SPACE          32
#define KEY_APOSTROPHE     39  /* ' */
#define KEY_COMMA          44  /* , */
#define KEY_MINUS          45  /* - */
#define KEY_PERIOD         46  /* . */
#define KEY_SLASH          47  /* / */
#define KEY_0              48
#define KEY_1              49
#define KEY_2              50
#define KEY_3              51
#define KEY_4              52
#define KEY_5              53
#define KEY_6              54
#define KEY_7              55
#define KEY_8              56
#define KEY_9              57
#define KEY_SEMICOLON      59 /* ; */
#define KEY_EQUAL          61 /* = */
#define KEY_A              65
#define KEY_B              66
#define KEY_C              67
#define KEY_D              68
#define KEY_E              69
#define KEY_F              70
#define KEY_G              71
#define KEY_H              72
#define KEY_I              73
#define KEY_J              74
#define KEY_K              75
#define KEY_L              76
#define KEY_M              77
#define KEY_N              78
#define KEY_O              79
#define KEY_P              80
#define KEY_Q              81
#define KEY_R              82
#define KEY_S              83
#define KEY_T              84
#define KEY_U              85
#define KEY_V              86
#define KEY_W              87
#define KEY_X              88
#define KEY_Y              89
#define KEY_Z              90

/* function keys */
#define KEY_ESCAPE         256
#define KEY_ENTER          257
#define KEY_TAB            258
#define KEY_BACKSPACE      259
#define KEY_INSERT         260
#define KEY_DELETE         261
#define KEY_RIGHT          262
#define KEY_LEFT           263
#define KEY_DOWN           264
#define KEY_UP             265
#define KEY_F1             290
#define KEY_F2             291
#define KEY_F3             292
#define KEY_F4             293
#define KEY_F5             294
#define KEY_F6             295
#define KEY_F7             296
#define KEY_F8             297
#define KEY_F9             298
#define KEY_F10            299
#define KEY_F11            300
#define KEY_F12            301
#define KEY_LEFT_SHIFT     340
#define KEY_LEFT_CONTROL   341
#define KEY_LEFT_ALT       342
#define KEY_LEFT_SUPER     343
#define KEY_RIGHT_SHIFT    344
#define KEY_RIGHT_CONTROL  345
#define KEY_RIGHT_ALT      346
#define KEY_RIGHT_SUPER    347

//=======================================================
/*
// @sPOINT
// @LINE
// @WINDOW
*/
/*
    sPOINT. It's just a point on the map.
    X:X position
    Y:Y position
*/
struct sPOINT{
// postion for a point
    int X, Y;
// the construction function    
    sPOINT();
// the construction function with params
    sPOINT(int x, int y);
// the destroy function
    ~sPOINT();
// operate "self-minus"
    sPOINT operator ~();
// operate "plus"
    sPOINT operator +(const sPOINT B);
// operate "minus"
    sPOINT operator -(const sPOINT B);
// operate "resolve"
    sPOINT operator /(const int B);
// operator "bigger than"    
    bool operator >(const sPOINT B);
// operator "logical equal"
    bool operator ==(const sPOINT B);
//  WARNING: >> means "in"
    bool operator >>(const sPOINT *B);
// ABS function
    friend float Abs(sPOINT  A);
// mata vector function
    friend sPOINT meta(sPOINT A, sPOINT B);
};
/*
    Window vector
*/
struct LINE{
/*
* @params 2 points
* @params color
*/    
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
class SMAP{
    private:
        int MWIDTH, MHEIGHT;
        int WNUM;
        std::vector<WINDOW> REGISTED;
        char BITMAP[255][255];
    public:
        SMAP(int LEN_X, int LEN_Y);
        ~SMAP();
        int REGISTER(int X, int Y, int WIDTH, int HEIGHT, char BCOLOR);
        int UNREG(int uuid);
        void CLEARWINDOW(int uuid);
        int PAINT(int uuid, sPOINT A, sPOINT B);
        int PAINT(int uuid, sPOINT A, sPOINT B, char COLOR);
        void PAINTMAIN();
        void DELAY(uint16_t _gap);
        void PRINTSCR();
};
//=========================================================
/*
    keyboard listener
*/
void *get_key(void *key);
//KEYBOARD LISTENER
class KEYBOARD{
    private:
        char _KEY;
        pthread_t KEY_THREAD;  
        std::vector<char> _BINDLIST;
        STATUS (*_CallBack)();
    public:
        KEYBOARD();
        //0:success;1:normal exit;-1:bad exit;
        int LISTEN();
        //stop listening
        int STOP();
        //return nowkey
        char THISKEY();
        //bind a event
        int BIND(KEY_VALUE key, STATUS (*_callback)());
        ~KEYBOARD();
};
//=========================================================
#undef CALLBACK
#endif

//INCLUDE WRITES HERE