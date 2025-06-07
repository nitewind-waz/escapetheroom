
// Library luar
#include "./include/utils.h"
#include "include/room.h"
#include "include/bag.h"


int main(){
    srand(time(NULL));
    ruangan root = NULL;
    riwayat* roomhistory = NULL;
    bagStack inventory;
    initBagStack(&inventory);

    pushInventory(&inventory, roomKey);
    pushInventory(&inventory, exitKey);
    printBag(&inventory);
    BuildRandomRoom(&root);
    printRoom();
    MasukPintu(root);
    
    return 0;
}