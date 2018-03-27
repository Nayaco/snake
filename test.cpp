#include "snakec.h"
int main(){
    SMAP *map = new SMAP(70, 50);
    int guuid = map->REGISTER(0, 0, 50, 50, '*');
    
    while(1){
        map->CLEARWINDOW(guuid);
        map->PAINT(guuid,sPOINT(1,1),sPOINT(1,30),'#');
        map->PAINTMAIN();
        map->PRINTSCR();
        Sleep(500);
    }return 0;
}