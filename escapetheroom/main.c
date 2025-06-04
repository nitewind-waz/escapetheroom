
// Library luar
#include "./include/utils.h"
#include "include/room.h"


int main(){
    // srand(time(NULL));
    ruangan root = NULL;

    BuildRandomRoom(&root);

    printRoom();
    MasukPintu(root);
    
    return 0;
}