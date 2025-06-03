#ifndef ROOM_H
#define ROOM_H

#include "../raylib/include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "time.h"

#define MAX_DOORS 3
#define MAX_ROOMS 26

typedef struct Room *ruangan;

typedef struct Room {
    char id;
    ruangan doors[MAX_DOORS];
    bool hasKey;
    bool isExit;
} Room;

// extern ruangan allRooms[MAX_ROOMS];

ruangan CreateRoom(char id);
bool HasEmptyDoor(ruangan room);
int FindEmptyDoor(ruangan room);
void BuildRandomRoom(ruangan rooms[]);
void printRoom();

#endif