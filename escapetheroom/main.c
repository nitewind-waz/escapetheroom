
// Library luar
#include "include/room.h"
#include "include/bag.h"
#include "include/utils.h"

extern bool visited[MAX_ROOMS];

int main(){
    srand(time(NULL));
    ruangan root = NULL;
    riwayat* roomhistory = NULL;
    
    
    BuildRandomRoom(&root);
    memset(visited, 0, sizeof(visited)); // reset sebelum traversal

    ruangan exitRoom = FindExitRoom(root);

    if (exitRoom != NULL) {
        printf("Exit ditemukan di ruangan %c\n", exitRoom->id);
    } else {
        printf("Exit tidak ditemukan.\n");
    }
    printRoom(root);
    MasukPintu(root);
    
    return 0;
}