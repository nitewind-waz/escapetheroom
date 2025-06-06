#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "conio.h"

#define MAX_DOORS 3
#define MAX_ROOMS 26

typedef struct Room *ruangan;

typedef struct Room {
    char id;
    ruangan doors[MAX_DOORS];
    bool hasDoorKey;
    bool hasExitKey;
    bool isExit;
} Room;

typedef struct riwayat {
    ruangan Rooms;
    struct riwayat *next;
} riwayat;

typedef struct {
    riwayat *top;
} StackRoom;


// extern ruangan allRooms[MAX_ROOMS];
bool HasExitKey(ruangan room);
bool HasDoorKey(ruangan room);
ruangan CreateRoom(char id);
bool HasEmptyDoor(ruangan room);
int FindEmptyDoor(ruangan room);
void BuildRandomRoom(ruangan *root);
void printRoom();
void MasukPintu(ruangan rooms);
void FindAvailableRoom(ruangan current, ruangan* list, int* count);
int getKey(ruangan room);
void createEmpty(StackRoom* s);
void PushHistory(StackRoom* s, ruangan Room);
ruangan Pop(StackRoom* s);
bool IsEmpty (StackRoom* S);
void PrintHistory(StackRoom s);

#endif