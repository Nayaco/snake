
//INCLUDE WRITES HERE
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
    MAIN REGISTER AND PAINTER
*/
struct LINE{
    int X_1, Y_1, X_2, Y_2;
    int COLOR;
    LINE(){}
    LINE(int x_1, int y_1, int x_2, int y_2){
        X_1 = x_1;
        Y_1 = y_1;
        X_2 = x_2;
        Y_2 = y_2;
        COLOR = BACKGROUND_INTENSITY;
    }
    LINE(int x_1, int y_1, int x_2, int y_2, int color){
        X_1 = x_1;
        Y_1 = y_1;
        X_2 = x_2;
        Y_2 = y_2;
        COLOR = BACKGROUND_INTENSITY;
    }
};
struct WINDOW{
    int X, Y, WIDTH ,HEIGHT, WUUID;
    vector<LINE> MAP;
    int BACKGROUND;
    WINDOW(){}
    WINDOW(int x, int y, int width, int height, int uuid){
        X = x; Y = y;
        WIDTH = width;
        HEIGHT = height;
        WUUID = uuid;
        BACKGROUND = 32;
    }
    WINDOW(int x, int y, int width, int height, int color, int uuid){
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
    void DRAWLINE(sPOINT A, sPOINT B,int color){
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
        int BITMAP[127][127];
        char WORDMAP[127][127];
        HANDLE WHANDLE;
    public:
        SMAP(int LEN_X, int LEN_Y){
            WNUM = 0;
            this->MWIDTH = LEN_X;
            this->MHEIGHT =  LEN_Y;
            this->WHANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
        }
        ~SMAP(){}
        int REGISTER(int X, int Y, int WIDTH, int HEIGHT, int BCOLOR){
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
                    BITMAP[i][j] = BACKGROUND_INTENSITY;
                } 
            }
            for(; itor < this->REGISTED.end(); itor++){
                vector<LINE>::iterator Witor = (*itor).MAP.begin();
                for(int i = 0; i < (*itor).HEIGHT; i++){
                    for(int j = 0; j < (*itor).WIDTH; j++){
                        BITMAP[(*itor).X + i][(*itor).Y + j] = (*itor).BACKGROUND;
                    }
                }
                for(; Witor < (*itor).MAP.end(); Witor++){  
                    if((*Witor).X_1 == (*Witor).X_2){
                        int S = MIN((*Witor).Y_1, (*Witor).Y_2);
                        int T = MAX((*Witor).Y_1, (*Witor).Y_2);
                        int C = (*Witor).COLOR;
                        for(int i = S; i <= T; i++){
                            BITMAP[(*itor).Y + i][(*itor).X + (*Witor).X_1] = C;
                        }
                    }else if((*Witor).Y_1 == (*Witor).Y_2){
                        int S = MIN((*Witor).X_1, (*Witor).X_2);
                        int T = MAX((*Witor).X_1, (*Witor).X_2);
                        int C = (*Witor).COLOR;
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
                for(int j = 0; j < this->MWIDTH; j++){
                    SetConsoleTextAttribute(this->WHANDLE, BITMAP[i][j]);
                    cout<<' ';
                }
                cout<<endl;
            }
        }
};