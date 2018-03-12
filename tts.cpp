/*
    SNAKE 0.05(ALPHA_EDITION)
  ______      ____    __      _ _       _    _    ______
/  ___\_\   | \ \\  | ||    / \ \\    | || / // |   __ ||
| ||        | |\ \\ | ||   / //\ \\   | ||/ //  | ||
\ \\_____   | ||\ \\| ||  / /===\ \\  | |  //   | |=====
    ---\\\  | || \ \| || / /_____\ \\ | || \\   |   ___||
 ______|| | | ||  \ | || | ||    | || | ||\ \\  | ||___
 \____ ///  |_||   \|_|| |_||    | || |_|| \_\\ |_____ ||
*/

#include "stx.h"
using namespace std;

/*
    sPOINT. It's just a point on the map.
    X:X position
    Y:Y position
*/
struct sPOINT{
    int X, Y;
    sPOINT(){X = 0; Y = 0;}
    sPOINT(int x, int y){X = x; Y = y;}
    ~sPOINT(){}
    sPOINT operator ~(){
        sPOINT C(-X, -Y);
        return C;
    }
    sPOINT operator +(const sPOINT B){
        sPOINT C(0, 0);
        C.X = X + B.X;
        C.Y = Y + B.Y;
        return C;
    }
    sPOINT operator -(const sPOINT B){
        sPOINT C(0, 0);
        C.X = X - B.X;
        C.Y = Y - B.Y;
        return C;
    }
    sPOINT operator /(const int B){
        sPOINT C(0, 0);
        C.X = X / B; 
        C.Y = Y / B;
        return C;
    }
    bool operator >(const sPOINT B){
        return X > B.X;
    }
    bool operator ==(const sPOINT B){
        return (X == B.X) && (Y == B.Y); 
    }
    //WARNING: >> means "in"
    bool operator >>(const sPOINT *B){
        for(int i = 0;i < LEN(B, sPOINT); i++){
            if(*this == B[i])return 1;
        }
        return 0;
    }
    friend float Abs(sPOINT  A){
        return sqrt(DOUBLE((float)A.X) + DOUBLE((float)A.Y));
    }
    friend sPOINT meta(sPOINT A, sPOINT B){
        sPOINT C = A - B;
        return C / Abs(C);
    }
};

/*
    keyboard listener
*/
void *get_key(void *key){
    char* T_KEY = (char*)key;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);           //允许退出线程   
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,   NULL);
    while(1)*T_KEY = getch();
    pthread_exit(NULL);
}
class KEYBOARD{
    private:
        char KEY;
        pthread_t KEY_THREAD;
        
    public:
        KEYBOARD(){
            this->KEY = 0;
        }
        /*
            0:success;1:normal exit;-1:bad exit;
        */
        int LISTEN(){
            int rc = pthread_create(&this->KEY_THREAD, NULL, get_key, (void*)&this->KEY);
            return rc;
        }
        int STOP(){
            int rc = pthread_cancel(this->KEY_THREAD);
            return rc;
        }
        char THISKEY(){
            return this->KEY;
        }
        ~KEYBOARD(){
        }
};
/*
    MAIN REGISTER AND PAINTER
*/

struct LINE{
    int X_1, Y_1, X_2, Y_2;
    char COLOR;
    LINE(){}
    LINE(int x_1, int y_1, int x_2, int y_2){
        X_1 = x_1;
        Y_1 = y_1;
        X_2 = x_2;
        Y_2 = y_2;
        COLOR = '#';
    }
    LINE(int x_1, int y_1, int x_2, int y_2, char color){
        X_1 = x_1;
        Y_1 = y_1;
        X_2 = x_2;
        Y_2 = y_2;
        COLOR = color;
    }
};
struct WINDOW{
    int X, Y, WIDTH ,HEIGHT, WUUID;
    vector<LINE> MAP;
    char BACKGROUND;
    WINDOW(){}
    WINDOW(int x, int y, int width, int height, int uuid){
        X = x; Y = y;
        WIDTH = width;
        HEIGHT = height;
        WUUID = uuid;
        BACKGROUND = 32;
    }
    WINDOW(int x, int y, int width, int height, char color, int uuid){
        X = x; Y = y;
        WIDTH = width;
        HEIGHT = height;
        BACKGROUND = color;
        WUUID = uuid;
    }
    void DRAWLINE(sPOINT A, sPOINT B){
        LINE C(A.X, A.Y, B.X, B.Y);
        MAP.push_back(C);
    }
    void DRAWLINE(sPOINT A, sPOINT B, char color){
        LINE C(A.X, A.Y, B.X, B.Y, color);
        MAP.push_back(C);
    }
    void CLEARLINE(){
        MAP.clear();
    }
    char WBACKGROUND(){
        return this->BACKGROUND;
    }
    vector<LINE>::iterator lend(){
        return MAP.end();
    }   
    vector<LINE>::iterator lbegin(){
        return MAP.begin();
    }
    int lsize(){
        return MAP.size();
    }
};
class SMAP{
    private:
        int MWIDTH, MHEIGHT;
        int WNUM;
        vector<WINDOW> REGISTED;
        char BITMAP[127][127];
    public:
        SMAP(int LEN_X, int LEN_Y){
            WNUM = 0;
            this->MWIDTH = LEN_X;
            this->MHEIGHT =  LEN_Y;
        }
        ~SMAP(){}
        int REGISTER(int X, int Y, int WIDTH, int HEIGHT, char BCOLOR){
            this->WNUM++;
            WINDOW window(X, Y, WIDTH, HEIGHT, BCOLOR,this->WNUM);
            this->REGISTED.push_back(window);
            return WNUM;
        }
        int UNREG(int uuid){
            vector<WINDOW>::iterator itor = this->REGISTED.begin();
            this->WNUM--;
            for(; itor<this->REGISTED.end(); itor++){
                if((*itor).WUUID == uuid){
                    this->REGISTED.erase(itor);
                    return 0;
                }
            }
            return 1;
        }
        void CLEARWINDOW(int uuid){
            vector<WINDOW>::iterator itor = this->REGISTED.begin();
            for(; itor < this->REGISTED.end(); itor++){
                if((*itor).WUUID == uuid){
                    (*itor).CLEARLINE();
                    break;
                }
            }
            return;
        }
        int PAINT(int uuid, sPOINT A, sPOINT B){
            vector<WINDOW>::iterator itor = this->REGISTED.begin();
            for(; itor < this->REGISTED.end(); itor++){
                if((*itor).WUUID == uuid){
                    (*itor).DRAWLINE(A, B);
                    return 0;
                }
            }
            return 1;
        }
        int PAINT(int uuid, sPOINT A, sPOINT B, char COLOR){
            vector<WINDOW>::iterator itor = this->REGISTED.begin();
            for(; itor < this->REGISTED.end(); itor++){
                if((*itor).WUUID == uuid){
                    (*itor).DRAWLINE(A, B, COLOR);
                    return 0;
                }
            }
            return 1;
        }
        void PAINTMAIN(){
            vector<WINDOW>::iterator itor = this->REGISTED.begin();
            for(int i = 0; i < this->MHEIGHT; i++){
                for(int j = 0; j < this->MWIDTH; j++){
                    BITMAP[i][j] = 32;
                }
                BITMAP[i][MWIDTH] = 0; 
            }
            for(; itor < this->REGISTED.end(); itor++){
                vector<LINE>::iterator Witor = (*itor).MAP.begin();
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
        void PRINTSCR(){
            COORD coord;
            coord.X=0;
            coord.Y=0;		
            HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(hout,coord);
            for(int i = 0; i < this->MHEIGHT; i++){
                cout<<BITMAP[i]<<endl;
            }
        }
};

/*
    Main part : SNAKE
*/
const int START_LEN = 3;
class SNAKE{
    private:
        //dir:
        sPOINT DIRECT;
        int N_P;
        vector<sPOINT> Q;  
        vector<sPOINT>::iterator QITOR; 
    public:
        SNAKE(){}
        SNAKE(int x, int y){
            sPOINT B(x, y-START_LEN + 1);
            this->Q.push_back(B);
            sPOINT A(x, y);
            this->Q.push_back(A);
            this->N_P = 2;
            this->DIRECT = sPOINT(0, 1);
            this->QITOR = this->Q.begin();
        }
        ~SNAKE(){}
        sPOINT HEAD(){
            return this->Q.back();
        }
        sPOINT TAIL(){
            return this->Q.front();
        }
        void Iterateback(){
            this->QITOR = this->Q.begin();
        }
        sPOINT Iterate(){
            if(this->QITOR == this->Q.end()){
                this->QITOR = this->Q.begin();
                return sPOINT(-1, -1);
            }
            sPOINT B = (*this->QITOR);
            this->QITOR++;
            return B;
        }
        sPOINT SHOWNEXT(){
            return this->Q.back() + DIRECT;
        }
        void TURN(const sPOINT dir){
            this->DIRECT = dir;
            sPOINT C = this->Q.back();
            this->Q.push_back(C);
            this->QITOR = this->Q.begin();
            return;
        }
        void MOVE(int ISEAT){
            vector<sPOINT>::iterator begin = this->Q.begin();
            vector<sPOINT>::iterator end = this->Q.end() - 1;
            if(ISEAT){*end = *end + DIRECT; return;}
                else{
                    *end = *end + DIRECT;
                    sPOINT C(0, 0);
                    C = *begin + meta(*(begin + 1), *begin);
                    if(C == *(begin + 1)){
                        this->Q.erase(begin);
                        this->QITOR = this->Q.begin();
                        return;
                    }else{
                        *begin = C;
                        return;
                    }
                }
        }
        sPOINT SHOWDIR(){
            return DIRECT;
        }
};

class GAMEENGINE{
    private:
        int SCORE;
        int GHEIGHT, GWIDTH;
        unsigned int GMAP[51][51];
        SNAKE snake;
        sPOINT FRUIT;
        /*
            0:go on
            1:score+1
            2:gameover
        */
        unsigned int COLLISION(sPOINT T){
            if(this->GMAP[T.Y][T.X] == 1 || T.Y < 0 || T.X < 0 || T.X >= this->GWIDTH || T.Y >= this->GHEIGHT){
                return 2;
            }
            if((this->GMAP[T.Y][T.X]) == 2){
                return 1;
            }
            return 0;
        }
        sPOINT FRUIT_CREATE(){
            int fx, fy;
            do{
                fx = RAN(GWIDTH);
                fy = RAN(GHEIGHT);
            }while(this->GMAP[fy][fx]);
            this->GMAP[fy][fx] = 2;
            return sPOINT(fx, fy);
        }
    public:
        GAMEENGINE(int height, int width){
            for(int i = 0; i < height; i++)for(int j = 0; j < width; j++)this->GMAP[i][j] = 0;
            for(int i = 0; i < START_LEN; i++)this->GMAP[height/2+1 - i][width/2] = 1;
            this->GWIDTH = width;
            this->GHEIGHT = height;
            this->SCORE = 0;
            this->snake = SNAKE(width/2, height/2+1);
            srand((unsigned)time(NULL));
            this->FRUIT = this->FRUIT_CREATE();
        }
        ~GAMEENGINE(){}
        // 1gmover 0goon 
        STATUS UPDATE(sPOINT DIR){
            if(!(DIR==sPOINT(0,0))){
                if(!(DIR == this->snake.SHOWDIR()||DIR == ~this->snake.SHOWDIR())){
                    this->snake.TURN(DIR);
                }
            }
            sPOINT P;
            unsigned int STAT = this->COLLISION(this->snake.SHOWNEXT());
            if(STAT == 2)return NORM_FINISH;
            if(STAT == 0){
                sPOINT tail = this->snake.TAIL();
                this->GMAP[tail.Y][tail.X] = 0;
                this->snake.MOVE(0);
                sPOINT head = this->snake.HEAD();
                this->GMAP[head.Y][head.X] = 1;
            }
            if(STAT == 1){
                this->SCORE++;
                this->snake.MOVE(1);
                sPOINT head = this->snake.HEAD();
                this->GMAP[head.Y][head.X] = 1;
                this->FRUIT = this->FRUIT_CREATE();
            }
            return SUCCEED;
        }
        void RESETITOR(){
            this->snake.Iterateback();
        }
        sPOINT SHOWITOR(){
            return this->snake.Iterate();
        }
        sPOINT SHOWFRUIT(){
            return this->FRUIT;
        }
        int SHOWSCORE(){
            return this->SCORE;
        }
};

class LOOP{
    private: 
        GAMEENGINE *GAMEMAIN;
        KEYBOARD *key;
        SMAP *smap;
        int guuid, iuuid;
        STATUS run(){
            sPOINT DIR; 
            switch(tolower((*(this->key)).THISKEY())){
                case 'a':{
                    DIR = sPOINT(-1, 0);
                    break;
                }
                case 'w':{
                    DIR = sPOINT(0, -1);
                    break;
                }
                case 's':{
                    DIR = sPOINT(0, 1);
                    break;
                }
                case 'd':{
                    DIR = sPOINT(1, 0);
                    break;
                }
                case 27:{
                    exit(0);
                    break;
                }
            }
            if((*(this->GAMEMAIN)).UPDATE(DIR) == NORM_FINISH)return NORM_FINISH;
            (*(this->smap)).CLEARWINDOW(this->guuid);
            sPOINT A_1(0, 49);sPOINT A_2(0, 0);
            sPOINT A_3(49, 0);sPOINT A_4(49, 49);
            (*(this->smap)).PAINT(this->guuid, A_1, A_2, '#');
            (*(this->smap)).PAINT(this->guuid, A_2, A_3, '#');
            (*(this->smap)).PAINT(this->guuid, A_3, A_4, '#');
            (*(this->smap)).PAINT(this->guuid, A_4, A_1, '#');
            (*(this->smap)).PAINT(this->guuid, (*(this->GAMEMAIN)).SHOWFRUIT() + sPOINT(1, 1), (*(this->GAMEMAIN)).SHOWFRUIT() + sPOINT(1, 1), '@');
            sPOINT P_0 = (*(this->GAMEMAIN)).SHOWITOR();
            for(sPOINT P = (*(this->GAMEMAIN)).SHOWITOR(); !(P == sPOINT(-1, -1));P = (*(this->GAMEMAIN)).SHOWITOR()){
                (*(this->smap)).PAINT(this->guuid ,P_0 + sPOINT(1, 1), P + sPOINT(1, 1), 'O');
                P_0 = P;
            }
            (*(this->smap)).CLEARWINDOW(this->iuuid);
            sPOINT B_1(0, 49);sPOINT B_2(0, 0);
            sPOINT B_3(18, 0);sPOINT B_4(18, 49);
            (*(this->smap)).PAINT(this->iuuid, B_2, B_3, '#');
            (*(this->smap)).PAINT(this->iuuid, B_3, B_4, '#');
            (*(this->smap)).PAINT(this->iuuid, B_4, B_1, '#');
            int SCORE  = (*(this->GAMEMAIN)).SHOWSCORE();
            for(int i = 0; i < 4; i++, SCORE /= 10){
                (*(this->smap)).PAINT(this->iuuid, sPOINT(12 - i*2, 39), sPOINT(13 - i*2, 39), '0' + SCORE % 10);
            }
            (*(this->smap)).PAINTMAIN();
            (*(this->smap)).PRINTSCR();
            return SUCCEED;
        }
    public:
        LOOP(){
            this->GAMEMAIN = new GAMEENGINE(48, 48);
            (*this->GAMEMAIN).RESETITOR();
            this->key = new KEYBOARD();
            int rc = (*(this->key)).LISTEN();
            this->smap = new SMAP(70, 50);
            if(rc == -1)exit(1);
        }
        STATUS MAINLOOP(int ini){
            int now_time = time(NULL);
            this->guuid = (*(this->smap)).REGISTER(0, 0, 50, 50, ' ');
            this->iuuid = (*(this->smap)).REGISTER(50, 0, 19, 50, ' ');
            while(1){
                now_time = time(NULL);
                STATUS STAT = this->run();
                if(STAT != SUCCEED){
                    return STAT; 
                }
                Sleep(ini - time(NULL) + now_time);
            }
            return SUCCEED;
        }
};

int main(){
    LOOP *loop = new LOOP();
    (*loop).MAINLOOP(500);
    system("pause");
    return 0;
}