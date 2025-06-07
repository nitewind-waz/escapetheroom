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

void printRoom(ruangan roomm){    
    printf("    ===================    \n");

    printf("    ||       %C       ||    \n",roomm->id);
    printf("    ||               ||    \n");

    if (roomm->doors[0] != NULL){
    printf("      <<== ");
    }else{
    printf("    ||     ");
    } 
    if (roomm->doors[2] != NULL)
    {
    printf("       ==>>\n");
    }else{
    printf("          ||\n");
    }
    if (roomm->doors[1] != NULL)
    {
    printf("    ||       |       ||    \n");
    printf("    ||       V       ||    \n");
    printf("    ========   ========    \n");
    }else{
    printf("    ||               ||    \n");
    printf("    ||               ||    \n");
    printf("    ===================    \n");
    }
    printf("                           \n");
}

void MasukPintu(ruangan rooms){
    ruangan Ruangan = rooms; 
    
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
                if (Ruangan->doors[0] == NULL)
                {
                    printRoom(Ruangan);
                    printf("tidak ada ruangan di pintu itu\n\n");
                }
                else{
                    PushHistory(&historyroom, Ruangan);
                    Ruangan = Ruangan->doors[0];
                    printf("\nsekarang di ruangan : %c\n",Ruangan->id);
                    printRoom(Ruangan);
                }
            }
            else if (input == 'D' || input == 'd')
            {
                system("cls");
                if (Ruangan->doors[2] == NULL)
                {
                    printRoom(Ruangan);
                    printf("tidak ada ruangan di pintu itu\n\n");
                }
                else{
                    PushHistory(&historyroom, Ruangan);
                    Ruangan = Ruangan->doors[2];
                    printf("\nsekarang di ruangan : %c\n",Ruangan->id);
                    printRoom(Ruangan);
                }
            }
            else if (input == 'S' || input == 's')
            {
                system("cls");
                if (Ruangan->doors[1] == NULL)
                {
                    printRoom(Ruangan);
                    printf("tidak ada ruangan di pintu itu\n\n");
                }
                else{
                    printRoom(Ruangan);
                    PushHistory(&historyroom, Ruangan);
                    Ruangan = Ruangan->doors[1];
                    printf("\nsekarang di ruangan : %c\n",Ruangan->id);
                }            
            }
            else if (input == 'W' || input == 'w')
            {
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
            else if (input == 'H' || input == 'h')
            {
                printRoom(Ruangan);
                printf("\n--- Riwayat Ruangan ---\n");
                PrintHistory(historyroom);
                printf("\n");
            }
            else{
                printf("\n");
                printRoom(Ruangan);
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