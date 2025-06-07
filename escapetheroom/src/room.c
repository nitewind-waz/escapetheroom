// Room.c
#include "../include/room.h"

ruangan CreateRoom(char id) {
    ruangan room = (ruangan)malloc(sizeof(Room));
    if (room != NULL) {
        room->id = id;
        room->hasDoorKey = false;
        room->hasExitKey = false;
        room->isExit = false;
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
        exitRoom->isExit = true;
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

void printRoom(){
    system("cls");
    printf("    ===================    \n");
    printf("    ||               ||    \n");
    printf("    ||               ||    \n");
    printf("      <<==   A   ==>>      \n");
    printf("    ||       |       ||    \n");
    printf("    ||       V       ||    \n");
    printf("    ======== S ========    \n");
    printf("                           \n");
    printf("                             ");
}

void MasukPintu(ruangan rooms){
    ruangan Ruangan = rooms; 
    
    char input;

    do
    {
        if (kbhit())
        {
            input = getch();
            if (input == 'A' || input == 'a')
            {
                if (Ruangan->doors[0] == NULL)
                {   
                    printRoom();
                    printf("tidak ada ruangan di pintu itu");
                }
                else{
                    printRoom();
                    Ruangan = Ruangan->doors[0];
                    printf("\n%c",Ruangan->id);
                }
            }
            else if (input == 'D' || input == 'd')
            {
                if (Ruangan->doors[2] == NULL)
                {   
                    printRoom();
                    printf("tidak ada ruangan di pintu itu");
                }
                else{
                    printRoom();
                    Ruangan = Ruangan->doors[2];
                    printf("\n%c",Ruangan->id);
                }
                /* code */
            }
            else if (input == 'S' || input == 's')
            {
                if (Ruangan->doors[1] == NULL)
                {   
                    printRoom();
                    printf("tidak ada ruangan di pintu itu");
                }
                else{
                    printRoom();
                    Ruangan = Ruangan->doors[1];
                    printf("\n%c",Ruangan->id);
                }            
                /* code */
            }
            else if (input == 'W' || input == 'w')
            {
                if (Ruangan->doors[0] == NULL)
                {   
                    printRoom();
                    printf("tidak ada ruangan di pintu itu");
                }
                else{
                    printRoom();
                    Ruangan = Ruangan->doors[0];
                    printf("\n%c",Ruangan->id);
                }
                /* code */
            }
            else if (input == 'p' || input == 'P')
            {
                break;
            }
            
            else{
                printRoom();
                printf("pintu tidak valid");
            }
            /* code */
        }
    } while (1);
}