
// Library luar
#include "include/room.h"
#include "include/bag.h"

extern bool visited[MAX_ROOMS];

int main(){
    srand(time(NULL));
    ruangan root = NULL;
    riwayat* roomhistory = NULL;
    bagStack inventory;
    bool menu = true;
    initBagStack(&inventory);

    pushInventory(&inventory, roomKey);
    pushInventory(&inventory, exitKey);
    BuildRandomRoom(&root);
    while (menu )
    {
        system("cls");
        printf("cara main :\n");
        printf("1. tekan \' A \' untuk ke pintu sebelah kiri \n");
        printf("2. tekan \' S \' untuk ke pintu yang ada di bawah \n");
        printf("3. tekan \' D \' untuk ke pintu sebelah kanan \n");
        printf("4. tekan \' W \' untuk Pindah Ke ruangan sebelumnya yang di datengin \n");
        printf("5. tekan \' H \' untuk melihat list Riwayat ruangan yang di jelajahi sebelumnya \n\n");
        printf("Mulai Bermain ?[y/t] : ");
        if (getch() == 'y' || getch() == 'Y')
        {
            menu = false;
            system("cls");
        }
        else{
            return 0;
        }
    }
    printBag(&inventory);
    printRoom(root);
    MasukPintu(root);
    return 0;
}