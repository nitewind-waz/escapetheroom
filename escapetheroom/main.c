
// Library luar
#include "./include/utils.h"
#include "include/room.h"


int main(){
    srand(time(NULL));
    
    ruangan rooms[MAX_ROOMS];
    

    BuildRandomRoom(rooms);
    printRoom();
    return 0;
}