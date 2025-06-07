
// Library luar
#include "include/room.h"
#include "include/bag.h"
#include "include/utils.h"


int main(){
    // srand(time(NULL));
    ruangan root = NULL;
    bagStack inventory;
    initBagStack(&inventory);

    

    // BuildRandomRoom(&root);
    // printRoom();
    pushInventory(&inventory, exitKey);
    pushInventory(&inventory, roomKey);
    printBag(&inventory);
    // MasukPintu(root); 
    
    return 0;
}