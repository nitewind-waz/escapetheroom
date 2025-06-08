// Room.c
#include "../include/room.h"

ruangan CreateRoom(char id) {
    ruangan room = (ruangan)malloc(sizeof(Room));
    if (room != NULL) {
        room->id = id;
        room->hasDoorKey = false;
        room->hasExitKey = false;
        if (id == '~')
        {
            room->isExit = true;
        }
        else{
            room->isExit = false;
        }
        for (int i = 0; i < MAX_DOORS; i++) {
            room->doors[i] = NULL;
        }
    }
    return room;
}

bool HasDoorKey(ruangan room) {
    return room != NULL && room->hasDoorKey;
}

bool HasExitKey(ruangan room) {
    return room != NULL && room->hasExitKey;
}

int getKey(ruangan room) {
    if (room == NULL) return -1;
    if (HasDoorKey(room)) return 1;
    if (HasExitKey(room)) return 2;
    return 0;
}

bool HasEmptyDoor(ruangan room) {
    for (int i = 0; i < MAX_DOORS; i++) {
        if (room->doors[i] == NULL) return true;
    }
    return false;
}

int FindEmptyDoor(ruangan room) {
     int indeks[MAX_DOORS];
    int count = 0;

    for (int i = 0; i < MAX_DOORS; i++) {
        if (room->doors[i] == NULL) {
            indeks[count++] = i;
        }
    }

    if (count == 0) return -1;
    return indeks[rand() % count];
}

// int FindEmptyDoor(ruangan room) {
//     for (int i = 0; i < MAX_DOORS; i++) {
//         if (room->doors[i] == NULL) return true;
//     }
//     return false; // ini klo penuh dia
// }

void FindAvailableRoom(ruangan current, ruangan* list, int* count) {
    if (current == NULL) return;
    if (HasEmptyDoor(current)) {
        list[(*count)++] = current;
    }
    for (int i = 0; i < MAX_DOORS; i++) {
        if (current->doors[i] != NULL) {
            FindAvailableRoom(current->doors[i], list, count);
        }
    }
}

void BuildRandomRoom(ruangan* root) {
    srand(time(NULL));

    *root = CreateRoom('A');
    int roomCount = 1;

    while (roomCount < MAX_ROOMS) {
        ruangan candidates[100];  // sementara, hanya untuk proses
        int count = 0;

        FindAvailableRoom(*root, candidates, &count);
        if (count == 0) break;

        ruangan parent = candidates[rand() % count];
        int doorIndex = FindEmptyDoor(parent);

        if (doorIndex == -1) continue;

        ruangan newRoom = CreateRoom('A' + roomCount);
        parent->doors[doorIndex] = newRoom;
        roomCount++;
    }

    // tandai ruangan exit secara acak dari ruangan yang punya pintu kosong
    ruangan availableExitRooms[100];
    int availableCount = 0;
    FindAvailableRoom(*root, availableExitRooms, &availableCount);

    if (availableCount > 0) {
        ruangan exitRoom = availableExitRooms[rand() % availableCount];
        int i = 0;
        while (i < 3)
        {
            if (exitRoom->doors[i] == NULL)
            {break;}
            else{i++;}
        }
        exitRoom->doors[i] = CreateRoom('~');
    }
}

// void BuildRandomRoom(ruangan rooms[]) {
//     ruangan available[MAX_ROOMS];
//     int availableCount = 0;

//     // untuk membuat   semmua ruangan ieu
//     for (int i = 0; i < MAX_ROOMS; i++) {
//         rooms[i] = CreateRoom('A' + i);
//     }

//     // bikin A jadi root
//     available[availableCount++] = rooms[0];

//     for (int i = 1; i < MAX_ROOMS; i++) {
//         ruangan newRoom = rooms[i];

//         // search parent nu    punya pintu kosong
//         int parentIndex;
//         do {
//             parentIndex = rand() % availableCount;
//         } while (!HasEmptyDoor(available[parentIndex]));

//         ruangan parent = available[parentIndex];
//         int doorIndex = FindEmptyDoor(parent);
//         parent->doors[doorIndex] = newRoom;
        
//         if (HasEmptyDoor(newRoom)) {
//             available[availableCount++] = newRoom;
//         }
//     }
// }

void printRoom(ruangan roomm){
    if (roomm->isExit)
    {
        printf("\n\n");
        printf("    ##     ## ######## ##    ##    ###    ##    ##  ######   \n");
        printf("    ###   ### ##       ###   ##   ## ##   ###   ## ##    ##  \n");
        printf("    #### #### ##       ####  ##  ##   ##  ####  ## ##        \n");
        printf("    ## ### ## ######   ## ## ## ##     ## ## ## ## ##   #### \n");
        printf("    ##     ## ##       ##  #### ######### ##  #### ##    ##  \n");
        printf("    ##     ## ##       ##   ### ##     ## ##   ### ##    ##  \n");
        printf("    ##     ## ######## ##    ## ##     ## ##    ##  ######   \n\n");
        printf("    ########   #######  ##    ## \n");
        printf("    ##     ## ##     ##  ##  ##  \n");
        printf("    ##     ## ##     ##   ####   \n");
        printf("    ########  ##     ##    ##    \n");
        printf("    ##     ## ##     ##    ##    \n");
        printf("    ##     ## ##     ##    ##    \n");
        printf("    ########   #######     ##    \n");
    }
    else{
            printf("    ===================    \n");
            printf("    ||    ruangan    ||    \n");
            printf("    ||       %c       ||    \n",roomm->id);

        // gambar pintu 1
        if (roomm->doors[0] != NULL){
            if (roomm->doors[0]->isExit)
            {
                printf("EXIT! <<== ");
            }else{
                printf("     %c<<== ",roomm->doors[0]->id);
            }
        }else{
            printf("    ||     ");
        }

        // gambar pintu 3
        if (roomm->doors[2] != NULL)
        {
            if (roomm->doors[2]->isExit)
            {
                printf("       ==>> EXIT!\n");
            }
            else{
                printf("      ==>>%c\n",roomm->doors[2]->id);
            }
        }else{
            printf("          ||\n");
        }
        
        // gambar pintu 3
        if (roomm->doors[1] != NULL)
        {
            if (roomm->doors[1]->isExit)
            {
                printf("    ||       |       ||    \n");
                printf("    ||       V       ||    \n");
                printf("    =====  EXIT!  =====    \n");
            }
            else{
                printf("    ||       |       ||    \n");
                printf("    ||       V       ||    \n");
                printf("    ======== %c ========    \n",roomm->doors[1]->id);
            }
        }else{
        printf("    ||               ||    \n");
        printf("    ||               ||    \n");
        printf("    ===================    \n");
        }
        printf("                           \n");
    }
}

void MasukPintu(ruangan rooms){
    ruangan Room_Saat_ini = rooms , RoomRoot = rooms; 
    
    StackRoom historyroom;
    createEmpty(&historyroom);
    
    char input;
    do
    {
        if (kbhit())
        {
            input = getch();
            if (input == 'A' || input == 'a')
            {
                system("cls");
                if (Room_Saat_ini->doors[0] == NULL)
                {
                    printRoom(Room_Saat_ini);
                    printf("tidak ada ruangan di pintu itu\n\n");
                }
                else{
                    PushHistory(&historyroom, Room_Saat_ini);
                    Room_Saat_ini = Room_Saat_ini->doors[0];
                    printRoom(Room_Saat_ini);
                    printf("\nsekarang di ruangan : %c\n",Room_Saat_ini->id);
                }
            }
            else if (input == 'D' || input == 'd')
            {
                system("cls");
                if (Room_Saat_ini->doors[2] == NULL)
                {
                    printRoom(Room_Saat_ini);
                    printf("tidak ada ruangan di pintu itu\n\n");
                }
                else{
                    PushHistory(&historyroom, Room_Saat_ini);
                    Room_Saat_ini = Room_Saat_ini->doors[2];
                    printRoom(Room_Saat_ini);
                    printf("\nsekarang di ruangan : %c\n",Room_Saat_ini->id);
                }
            }
            else if (input == 'S' || input == 's')
            {
                system("cls");
                if (Room_Saat_ini->doors[1] == NULL)
                {
                    printRoom(Room_Saat_ini);
                    printf("tidak ada ruangan di pintu itu\n\n");
                }
                else{
                    PushHistory(&historyroom, Room_Saat_ini);
                    Room_Saat_ini = Room_Saat_ini->doors[1];
                    printRoom(Room_Saat_ini);
                    printf("\nsekarang di ruangan : %c\n",Room_Saat_ini->id);
                }            
            }
            else if (input == 'W' || input == 'w')
            {
                system("cls");
                 if (!IsEmpty(&historyroom)) {
                    Room_Saat_ini = Pop(&historyroom);
                    printRoom(Room_Saat_ini);
                    printf("\nKembali ke ruangan %c\n\n", Room_Saat_ini->id);
                } else {
                    printRoom(Room_Saat_ini);
                    printf("\nSudah di ruangan awal, tidak bisa kembali.\n\n");
                }
            }
            else if (input == 'H' || input == 'h')
            {
                printf("\n--- Riwayat Room_Saat_ini ---\n");
                PrintHistory(historyroom);
                printf("\n");
            }
            else if (input == 'M' || input == 'm')
            {
                temukanExit(Room_Saat_ini , RoomRoot);
            }
            else{
                printf("\n");
                printRoom(Room_Saat_ini);
                printf("pintu tidak valid");
            }
        }
    } while (1);
}

void createEmpty(StackRoom *s){
    s->top = NULL;
}

void PushHistory(StackRoom* s, ruangan Room){
    riwayat *newRiwayatRoom = (riwayat*)malloc(sizeof(riwayat));
    if (newRiwayatRoom != NULL)
    {
        newRiwayatRoom->Rooms = Room;
        newRiwayatRoom->next = s->top;
        s->top = newRiwayatRoom;
    }
}

bool IsEmpty (StackRoom* S)
{
	return (S->top == NULL);
}

ruangan Pop(StackRoom* s) {
    if (IsEmpty(s)) return NULL;

    riwayat* temp = s->top;
    ruangan room = temp->Rooms;
    s->top = temp->next;
    free(temp);
    return room;
}

void PrintHistory(StackRoom s) {
    riwayat* temp = s.top;

    while (temp != NULL) {
        printf("-> %c\n", temp->Rooms->id);
        temp = temp->next;
    }
}

// ==================================== MENCARI JALUR DARI POSISI SKRG KE PINTU EXIT  =============================================
char jalur[MAX_ROOMS], jalur_Ke_PosisiSKrg[MAX_ROOMS], jalur_ke_Exit[MAX_ROOMS];
int panjangJalur;

// Fungsi pencarian exit - SANGAT SEDERHANA!
bool cariRuangan(ruangan awal, bool sudahDikunjungi[], char idroom) {
    // Jika ini adalah exit, selesai!
    if (awal->id == idroom) {
        jalur[panjangJalur++] = awal->id;
        return true;
    }
    
    // Tandai sudah dikunjungi
    sudahDikunjungi[awal->id] = true;
    jalur[panjangJalur++] = awal->id;
    
    // Coba semua pintu
    for (int i = 0; i < MAX_DOORS; i++) {
        if (awal->doors[i] != NULL && !sudahDikunjungi[awal->doors[i]->id]) {
            if (cariRuangan(awal->doors[i], sudahDikunjungi, idroom)) {
                return true; // Ketemu exit!
            }
        }
    }
    
    // Backtrack
    panjangJalur--;
    return false;
}

// Fungsi utama - diperbaiki untuk menampilkan jalur yang benar
void temukanExit(ruangan posisiSekarang, ruangan rootnya) {
    // Reset semua variabel
    bool dikunjungi1[256] = {false}; 
    bool dikunjungi2[256] = {false}; 
    panjangJalur = 0;
    
    // Cari jalur dari root ke posisi sekarang
    cariRuangan(rootnya, dikunjungi1, posisiSekarang->id);
    int pnjgJalurKe_skrg = panjangJalur;
    for (int i = 0; i < panjangJalur; i++) {
        jalur_Ke_PosisiSKrg[i] = jalur[i];
    }
    
    // Reset untuk pencarian kedua
    panjangJalur = 0;
    
    // Cari jalur dari root ke exit
    cariRuangan(rootnya, dikunjungi2, '~');
    int pnjgJalurExit = panjangJalur;
    for (int i = 0; i < panjangJalur; i++) {
        jalur_ke_Exit[i] = jalur[i];
    }

    printf("Path menuju pintu exit: \n");
    
    // Cari titik pertemuan terakhir (LCA - Lowest Common Ancestor)
    int titikTemu = -1;
    int maxCheck = (pnjgJalurKe_skrg < pnjgJalurExit) ? pnjgJalurKe_skrg : pnjgJalurExit;
    
    for (int i = 0; i < maxCheck; i++) {
        if (jalur_Ke_PosisiSKrg[i] == jalur_ke_Exit[i]) {
            titikTemu = i;
        } else {
            break;
        }
    }
    
    // Buat array untuk menyimpan jalur lengkap
    char jalurLengkap[MAX_ROOMS * 2];
    int panjangJalurLengkap = 0;
    
    // 1. Mundur dari posisi sekarang ke titik pertemuan (TERMASUK titik pertemuan)
    for (int i = pnjgJalurKe_skrg - 1; i >= titikTemu; i--) {
        jalurLengkap[panjangJalurLengkap++] = jalur_Ke_PosisiSKrg[i];
    }
    
    // 2. Maju dari setelah titik pertemuan ke exit (tidak termasuk titik pertemuan)
    for (int i = titikTemu + 1; i < pnjgJalurExit; i++) {
        jalurLengkap[panjangJalurLengkap++] = jalur_ke_Exit[i];
    }
    
    // Print hasil
    if (panjangJalurLengkap > 0) {
        for (int i = 0; i < panjangJalurLengkap; i++) {
            printf("%c", jalurLengkap[i]);
            if (i < panjangJalurLengkap - 1) {
                printf(" => ");
            }
        }
    } else {
        // Jika tidak ada jalur (berarti sudah di exit)
        printf("Sudah di exit!");
    }
    
    printf("\n");
}