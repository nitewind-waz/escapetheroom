// Room.c
#include "../include/room.h"

ruangan CreateRoom(char id) {
    ruangan room = (ruangan)malloc(sizeof(Room));
    if (room != NULL) {
        room->id = id;
        room->hasKey = false;
        room->isExit = false;
        for (int i = 0; i < MAX_DOORS; i++) {
            room->doors[i] = NULL;
        }
    }
    return room;
}

bool HasEmptyDoor(ruangan room) {
    return FindEmptyDoor(room) != -1;
}

// int FindEmptyDoor(ruangan room) {
//     for (int i = 0; i < MAX_DOORS; i++) {
//         if (room->doors[i] == NULL) return i;
//     }
//     return -1; // ini klo penuh dia
// }

int FindEmptyDoor(ruangan room) {
    for (int i = 0; i < MAX_DOORS; i++) {
        if (room->doors[i] == NULL) return i;
    }
    return -1; // ini klo penuh dia
}

void BuildRandomRoom(ruangan rooms[]) {
    ruangan available[MAX_ROOMS];
    int availableCount = 0;

    // untuk membuat   semmua ruangan ieu
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i] = CreateRoom('A' + i);
    }

    // bikin A jadi root
    available[availableCount++] = rooms[0];

    for (int i = 1; i < MAX_ROOMS; i++) {
        ruangan newRoom = rooms[i];

        // search parent nu    punya pintu kosong
        int parentIndex;
        do {
            parentIndex = GetRandomValue(0, availableCount - 1);
        } while (!HasEmptyDoor(available[parentIndex]));

        ruangan parent = available[parentIndex];
        int doorIndex = FindEmptyDoor(parent);
        parent->doors[doorIndex] = newRoom;

        if (HasEmptyDoor(newRoom)) {
            available[availableCount++] = newRoom;
        }
    }
}