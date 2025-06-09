#include "../include/room.h"
#include "../include/lockedroom.h"


extern bool visited[MAX_ROOMS];

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

bool HasExitRoom(ruangan room) {
    return room != NULL && room->isExit;
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
        ruangan candidates[100];
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

    // Pilih ruangan secara acak untuk menjadi Exit
    ruangan availableExitRooms[100];
    int availableCount = 0;
    FindAvailableRoom(*root, availableExitRooms, &availableCount);

    ruangan exitRoom = NULL;
    if (availableCount > 0) {
        exitRoom = availableExitRooms[rand() % availableCount];
        exitRoom->isExit = true;
    }

    // Pilih ruangan secara acak untuk menjadi Exit
    ruangan allRooms[100];
    int allRoomCount = 0;
    resetVisitedAll(*root);
    FindAllRooms(*root, allRooms, &allRoomCount);

    if (allRoomCount > 0) {
        ruangan exitRoom = allRooms[rand() % allRoomCount];
        exitRoom->isExit = true;

        // Pilih ruangan lain untuk simpan exit key
        ruangan keyRoom = NULL;
        do {
            keyRoom = allRooms[rand() % allRoomCount];
        } while (keyRoom == exitRoom);

        keyRoom->hasExitKey = true;
    }
}


void FindAllRooms(ruangan current, ruangan* list, int* count) {
    if (current == NULL || visited[current->id - 'A']) return;

    visited[current->id - 'A'] = true;
    list[(*count)++] = current;

    for (int i = 0; i < MAX_DOORS; i++) {
        FindAllRooms(current->doors[i], list, count);
    }
}

void ResetVisited(ruangan current) {
    if (current == NULL || !current->visited) return;
    current->visited = false;

    for (int i = 0; i < 4; i++) {
        if (current->doors[i]) {
            ResetVisited(current->doors[i]);
        }
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

// Perbaikan untuk fungsi MasukPintu dengan win condition yang lebih jelas
// Perbaikan untuk fungsi MasukPintu dengan win condition yang lebih jelas
void MasukPintu(ruangan rooms, bagStack *inventory, Player *player) {
    ruangan Ruangan = rooms; 
    
    StackRoom historyroom;
    createEmpty(&historyroom);
    
    // Inisialisasi antrian ruangan terkunci dan penghitung langkah
    LockedQueue lockedRooms;
    initLockedQueue(&lockedRooms);
    int stepCount = 0;
    
    char input;
    do {
        if (kbhit()) {
            input = getch();
            stepCount++; // Tambah penghitung langkah setiap input
            
            // Setiap 10 langkah, kunci ruangan acak
            if (stepCount % 10 == 0) {
                ruangan allRooms[100];
                int allRoomCount = 0;
                resetVisitedAll(Ruangan);
                FindAllRooms(Ruangan, allRooms, &allRoomCount);
                
                if (allRoomCount > 0) {
                    ruangan roomToLock = allRooms[rand() % allRoomCount];
                    // Pastikan ruangan exit tidak dikunci
                    if (!HasExitRoom(roomToLock)) {
                        enqueueLockedRoom(&lockedRooms, roomToLock->id);
                        printf("\nPERINGATAN: Ruangan %c terkunci otomatis!\n", roomToLock->id);
                    }
                }
            }
            
            if (input == 'A' || input == 'a') {
                system("cls");
                if (Ruangan->doors[0] == NULL) {
                    printRoom(Ruangan);
                    printf("tidak ada ruangan di pintu itu\n\n");
                } else {
                    // Cek apakah ruangan terkunci
                    if (isRoomLocked(&lockedRooms, Ruangan->doors[0]->id)) {
                        printRoom(Ruangan);
                        printf("Pintu terkunci! Gunakan kunci ruangan (tekan 'K') untuk membuka.\n\n");
                    } 
                    // Cek apakah ruangan exit dan belum punya kunci
                    else if (HasExitRoom(Ruangan->doors[0])) {
                        if (!player->hasExit) {
                            printRoom(Ruangan);
                            printf("Pintu terkunci! Anda perlu mencari kunci exit terlebih dahulu.\n\n");
                        } else {
                            // Masuk ke ruangan exit jika punya kunci
                            PushHistory(&historyroom, Ruangan);
                            Ruangan = Ruangan->doors[0];
                            printRoom(Ruangan);
                            printf("\nsekarang di ruangan: %c\n", Ruangan->id);
                        }
                    } else {
                        // Masuk ke ruangan normal
                        PushHistory(&historyroom, Ruangan);
                        Ruangan = Ruangan->doors[0];
                        printRoom(Ruangan);
                        printf("\nsekarang di ruangan: %c\n", Ruangan->id);
                        
                        // Cek kunci exit di ruangan baru
                        if (HasExitKey(Ruangan)) {
                            player->hasExit = true;
                            printf("Anda menemukan kunci exit!\n");
                        }
                    }
                }
            } 
            else if (input == 'D' || input == 'd') {
                // [Logika yang sama seperti di atas untuk pintu kanan]
                system("cls");
                if (Ruangan->doors[2] == NULL) {
                    printRoom(Ruangan);
                    printf("tidak ada ruangan di pintu itu\n\n");
                } else {
                    if (isRoomLocked(&lockedRooms, Ruangan->doors[2]->id)) {
                        printRoom(Ruangan);
                        printf("Pintu terkunci! Gunakan kunci ruangan (tekan 'K') untuk membuka.\n\n");
                    } else if (HasExitRoom(Ruangan->doors[2]) && !player->hasExit) {
                        printRoom(Ruangan);
                        printf("Pintu terkunci! Anda perlu mencari kunci exit terlebih dahulu.\n\n");
                    } else {
                        PushHistory(&historyroom, Ruangan);
                        Ruangan = Ruangan->doors[2];
                        printRoom(Ruangan);
                        printf("\nsekarang di ruangan: %c\n", Ruangan->id);
                        
                        if (HasExitKey(Ruangan)) {
                            player->hasExit = true;
                            printf("Anda menemukan kunci exit!\n");
                        }
                    }
                }
            }
            else if (input == 'S' || input == 's') {
                // [Logika yang sama seperti di atas untuk pintu bawah]
                system("cls");
                if (Ruangan->doors[1] == NULL) {
                    printRoom(Ruangan);
                    printf("tidak ada ruangan di pintu itu\n\n");
                } else {
                    if (isRoomLocked(&lockedRooms, Ruangan->doors[1]->id)) {
                        printRoom(Ruangan);
                        printf("Pintu terkunci! Gunakan kunci ruangan (tekan 'K') untuk membuka.\n\n");
                    } else if (HasExitRoom(Ruangan->doors[1]) && !player->hasExit) {
                        printRoom(Ruangan);
                        printf("Pintu terkunci! Anda perlu mencari kunci exit terlebih dahulu.\n\n");
                    } else {
                        PushHistory(&historyroom, Ruangan);
                        Ruangan = Ruangan->doors[1];
                        printRoom(Ruangan);
                        printf("\nsekarang di ruangan: %c\n", Ruangan->id);
                        
                        if (HasExitKey(Ruangan)) {
                            player->hasExit = true;
                            printf("Anda menemukan kunci exit!\n");
                        }
                    }
                }
            }
            else if (input == 'W' || input == 'w') {
                system("cls");
                if (!IsEmpty(&historyroom)) {
                    Ruangan = Pop(&historyroom);
                    printRoom(Ruangan);
                    printf("\nKembali ke ruangan %c\n\n", Ruangan->id);
                } else {
                    printRoom(Ruangan);
                    printf("\nSudah di ruangan awal, tidak bisa kembali.\n\n");
                }
            }
            else if (input == 'H' || input == 'h') {
                printRoom(Ruangan);
                printf("\n--- Riwayat Ruangan ---\n");
                PrintHistory(historyroom);
                printf("\n");
            }
            else if (input == 'I' || input == 'i') {
                system("cls");
                printRoom(Ruangan);
                printf("\n--- Inventory ---\n");
                printBag(inventory);
            }
            else if (input == 'K' || input == 'k') {
                // Fitur baru: Gunakan kunci untuk membuka ruangan
                if (!isLockedQueueEmpty(&lockedRooms)) {
                    char unlockedRoom = dequeueLockedRoom(&lockedRooms);
                    printf("\nAnda menggunakan kunci untuk membuka ruangan %c!\n", unlockedRoom);
                } else {
                    printf("\nTidak ada ruangan yang terkunci saat ini.\n");
                }
            }
            else {
                printf("\n");
                printRoom(Ruangan);
                printf("Input tidak valid");
            }

            // Win condition
            if (HasExitRoom(Ruangan) && player->hasExit) {
                printf("Anda telah menemukan pintu keluar dan memiliki kunci!\n");
                printf("Tekan 'E' untuk keluar dan menang!\n");
                if (input == 'E' || input == 'e') {
                    system("cls");
                    printf("\n");
                    printRoom(Ruangan);
                    printf("         SELAMAT! ANDA MENANG BOI!\n");
                    printf("    Anda berhasil keluar dari dungeon!\n\n");
                    printf("         Tekan tombol apa saja untuk keluar...\n");
                    getch();
                    break;
                }
            }
        }
    } while (1);
}

// Perbaikan fungsi printRoom untuk tidak langsung mengambil kunci
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
            printf("    ||       %C       ||    \n",roomm->id);
            printf("    ||               ||    \n");

        // gambar pintu 1
        if (roomm->doors[0] != NULL){
            if (roomm->doors[0]->isExit)
            {
                printf("EXIT! <<== ");
            }else{
                printf("      <<== ");
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
                printf("       ==>>\n");
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
                printf("    ========   ========    \n");
            }
        }else{
        printf("    ||               ||    \n");
        printf("    ||               ||    \n");
        printf("    ===================    \n");
        }
        printf("                           \n");
        
        // Tampilkan info kunci exit tanpa langsung mengambilnya
        if (HasExitKey(roomm)) {
            printf("*** ADA KUNCI EXIT DI RUANGAN INI! ***\n");
            printf("Masuk ke ruangan ini untuk mengambilnya!\n");
        } 
    }
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

bool visited[MAX_ROOMS]; // definisi global

ruangan FindExitRoom(ruangan current) {
    if (current == NULL) return NULL;

    if (HasExitRoom(current)) {
        return current;
    }

    visited[current->id - 'A'] = true;

    for (int i = 0; i < MAX_DOORS; i++) {
        ruangan next = current->doors[i];
        if (next != NULL && !visited[next->id - 'A']) {
            ruangan found = FindExitRoom(next);
            if (found != NULL) {
                return found;
            }
        }
    }

    return NULL;
}

void TemukanKunciExit(ruangan current) {
    if (current == NULL) return;

    int idx = current->id - 'A';
    if (idx < 0 || idx >= MAX_ROOMS || visited[idx]) return;

    visited[idx] = true;

    if (current->hasExitKey) {
        printf("Kunci exit ditemukan di ruangan %c\n", current->id);
    }

    for (int i = 0; i < MAX_DOORS; i++) {
        TemukanKunciExit(current->doors[i]);
    }
}


void resetVisitedAll(ruangan root) {
    for (int i = 0; i < MAX_ROOMS; i++) visited[i] = false;
}