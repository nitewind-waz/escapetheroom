// Library luar
#include "include/room.h"
#include "include/bag.h"
#include "include/lockedroom.h"
#include "include/stack.h"

extern bool visited[MAX_ROOMS];

int main(){
    srand(time(NULL));
    ruangan root = NULL;
    riwayat* roomhistory = NULL;
    bagList inventory;
    bool menu = true;
    initBagList(&inventory);
    Player player = {false, false};

    // Inisialisasi sistem ruangan terkunci
    LockedQueue lockedRooms;
    initLockedQueue(&lockedRooms);
    BuildRandomRoom(&root);
    while (menu )
    {
        system("cls");
        printf("cara main :\n");
        printf("1. tekan \' A \' untuk ke pintu sebelah kiri \n");
        printf("2. tekan \' S \' untuk ke pintu yang ada di bawah \n");
        printf("3. tekan \' D \' untuk ke pintu sebelah kanan \n");
        printf("4. tekan \' W \' untuk Pindah Ke ruangan sebelumnya yang di datengin \n");
        printf("5. tekan \' H \' untuk melihat list Riwayat ruangan yang di jelajahi sebelumnya \n");
        printf("6. tekan \' M \' untuk mencari jalur ke EXIT \n");
        printf("7. tekan \' Q \' menampilkan ruangan yang terkunci \n");
        printf("8. tekan \' I \' untuk membuka inventory\n\n");
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
    resetVisitedAll(root);
    TemukanKunciExit(root);
    printRoom(root);
    MasukPintu(root, &inventory, &player);
    return 0;
}