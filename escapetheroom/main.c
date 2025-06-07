
// Library luar
#include "include/room.h"
#include "include/bag.h"

extern bool visited[MAX_ROOMS];

int main(){
    srand(time(NULL));
    ruangan root = NULL;
    riwayat* roomhistory = NULL;
    
    
    BuildRandomRoom(&root);
    printRoom(root);
    MasukPintu(root);
    
    return 0;
}