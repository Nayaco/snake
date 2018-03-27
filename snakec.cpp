/*
    main part of the snakecore
*/

#include "snakec.h"

//==========================================================
sPOINT::sPOINT(){X = 0; Y = 0;}
sPOINT::sPOINT(int x, int y){X = x; Y = y;}
sPOINT::~sPOINT(){}
sPOINT sPOINT::operator ~(){
    sPOINT C(-X, -Y);
    return C;
}
sPOINT sPOINT::operator +(const sPOINT B){
    sPOINT C(0, 0);
    C.X = X + B.X;
    C.Y = Y + B.Y;
    return C;
}
sPOINT sPOINT::operator -(const sPOINT B){
    sPOINT C(0, 0);
    C.X = X - B.X;
    C.Y = Y - B.Y;
    return C;
}
sPOINT sPOINT::operator /(const int B){
    sPOINT C(0, 0);
    C.X = X / B; 
    C.Y = Y / B;
    return C;
}
bool sPOINT::operator >(const sPOINT B){
    return X > B.X;
}
bool sPOINT::operator ==(const sPOINT B){
    return (X == B.X) && (Y == B.Y); 
}
bool sPOINT::operator >>(const sPOINT *B){
    for(int i = 0;i < LEN(B, sPOINT); i++){
        if(*this == B[i])return 1;
    }
    return 0;
}

float Abs(sPOINT  A){
    return sqrt(DOUBLE((float)A.X) + DOUBLE((float)A.Y));
}

sPOINT meta(sPOINT A, sPOINT B){
    sPOINT C = A - B;
    return C / Abs(C);
}

//==========================================================
LINE::LINE(){}
LINE::LINE(int x_1, int y_1, int x_2, int y_2){
    X_1 = x_1;
    Y_1 = y_1;
    X_2 = x_2;
    Y_2 = y_2;
    COLOR = '#';
}
LINE::LINE(int x_1, int y_1, int x_2, int y_2, char color){
    X_1 = x_1;
    Y_1 = y_1;
    X_2 = x_2;
    Y_2 = y_2;
    COLOR = color;
}
//===========================================================
WINDOW::WINDOW(){}
WINDOW::WINDOW(int x, int y, int width, int height, int uuid){
    X = x; Y = y;
    WIDTH = width;
    HEIGHT = height;
    WUUID = uuid;
    BACKGROUND = 32;
}
WINDOW::WINDOW(int x, int y, int width, int height, char color, int uuid){
    X = x; Y = y;
    WIDTH = width;
    HEIGHT = height;
    BACKGROUND = color;
    WUUID = uuid;
}
void WINDOW::DRAWLINE(sPOINT A, sPOINT B){
    LINE C(A.X, A.Y, B.X, B.Y);
    MAP.push_back(C);
}
void WINDOW::DRAWLINE(sPOINT A, sPOINT B, char color){
    LINE C(A.X, A.Y, B.X, B.Y, color);
    MAP.push_back(C);
}
void WINDOW::CLEARLINE(){
    MAP.clear();
}
char WINDOW::WBACKGROUND(){
    return this->BACKGROUND;
}
std::vector<LINE>::iterator WINDOW::lend(){
    return MAP.end();
}   
std::vector<LINE>::iterator WINDOW::lbegin(){
    return MAP.begin();
}
int WINDOW::lsize(){
    return MAP.size();
}
//=========================================================

void *get_key(void *key){
    char* T_KEY = (char*)key;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);   
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,   NULL);
    while(1)*T_KEY = getch();
    pthread_exit(NULL);
}
KEYBOARD::KEYBOARD(){
    this->_KEY = 0;
}
int KEYBOARD::LISTEN(){
    int rc = pthread_create(&this->KEY_THREAD, NULL, get_key, (void*)&this->_KEY);
    return rc;
}
int KEYBOARD::STOP(){
    int rc = pthread_cancel(this->KEY_THREAD);
    return rc;
}
char KEYBOARD::THISKEY(){
    return this->_KEY;
}
KEYBOARD::~KEYBOARD(){
}
//================================================
SMAP::SMAP(int LEN_X, int LEN_Y){
    WNUM = 0;
    this->MWIDTH = LEN_X;
    this->MHEIGHT =  LEN_Y;
}
SMAP::~SMAP(){}
int SMAP::REGISTER(int X, int Y, int WIDTH, int HEIGHT, char BCOLOR){
    this->WNUM++;
    WINDOW window(X, Y, WIDTH, HEIGHT, BCOLOR,this->WNUM);
    this->REGISTED.push_back(window);
    return WNUM;
}
int SMAP::UNREG(int uuid){
    std::vector<WINDOW>::iterator itor = this->REGISTED.begin();
    this->WNUM--;
    for(; itor<this->REGISTED.end(); itor++){
        if((*itor).WUUID == uuid){
            this->REGISTED.erase(itor);
            return 0;
        }
    }
    return 1;
}
void SMAP::CLEARWINDOW(int uuid){
    std::vector<WINDOW>::iterator itor = this->REGISTED.begin();
    for(; itor < this->REGISTED.end(); itor++){
        if((*itor).WUUID == uuid){
            (*itor).CLEARLINE();
            break;
        }
    }
    return;
}
int SMAP::PAINT(int uuid, sPOINT A, sPOINT B){
    std::vector<WINDOW>::iterator itor = this->REGISTED.begin();
    for(; itor < this->REGISTED.end(); itor++){
        if((*itor).WUUID == uuid){
            (*itor).DRAWLINE(A, B);
            return 0;
        }
    }
    return 1;
}
int SMAP::PAINT(int uuid, sPOINT A, sPOINT B, char COLOR){
    std::vector<WINDOW>::iterator itor = this->REGISTED.begin();
    for(; itor < this->REGISTED.end(); itor++){
        if((*itor).WUUID == uuid){
            (*itor).DRAWLINE(A, B, COLOR);
            return 0;
        }
    }
    return 1;
}
void SMAP::PAINTMAIN(){
    std::vector<WINDOW>::iterator itor = this->REGISTED.begin();
    for(int i = 0; i < this->MHEIGHT; i++){
        for(int j = 0; j < this->MWIDTH; j++){
            BITMAP[i][j] = 32;
        }
        BITMAP[i][MWIDTH] = 0; 
    }
    for(; itor < this->REGISTED.end(); itor++){
        std::vector<LINE>::iterator Witor = (*itor).MAP.begin();
        for(int i = 0; i < (*itor).HEIGHT; i++){
            for(int j = 0; j < (*itor).WIDTH; j++){
                BITMAP[(*itor).X + i][(*itor).Y + j] = (*itor).BACKGROUND;
            }
            BITMAP[i][MWIDTH] = 0; 
        }
        for(; Witor < (*itor).MAP.end(); Witor++){  
            if((*Witor).X_1 == (*Witor).X_2){
                int S = MIN((*Witor).Y_1, (*Witor).Y_2);
                int T = MAX((*Witor).Y_1, (*Witor).Y_2);
                char C = (*Witor).COLOR;
                for(int i = S; i <= T; i++){
                    BITMAP[(*itor).Y + i][(*itor).X + (*Witor).X_1] = C;
                }
            }else if((*Witor).Y_1 == (*Witor).Y_2){
                int S = MIN((*Witor).X_1, (*Witor).X_2);
                int T = MAX((*Witor).X_1, (*Witor).X_2);
                char C = (*Witor).COLOR;
                for(int i = S; i <= T; i++){
                    BITMAP[(*itor).Y + (*Witor).Y_1][(*itor).X + i] = C;
                }
            }
        }
    }
}
void SMAP::PRINTSCR(){
    COORD coord;
    coord.X=0;
    coord.Y=0;		
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,coord);
    for(int i = 0; i < this->MHEIGHT; i++){
        std::cout<<BITMAP[i]<<std::endl;
    }
}
//=======================================================================