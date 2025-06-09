#ifndef ROOM_H
#define ROOM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "bag.h"

#define MAX_DOORS 3
#define MAX_ROOMS 26

typedef struct Room *ruangan;

typedef struct Room {
    char id;
    ruangan doors[MAX_DOORS];
    bool hasExitKey;
    bool visited;
    bool isExit;
} Room;

typedef struct Player {
    bool hasExit;
    bool hasDoor;
} Player;

// extern ruangan allRooms[MAX_ROOMS];
ruangan FindExitRoom(ruangan current); 
bool HasExitKey(ruangan room);
bool HasExitRoom(ruangan room);
ruangan CreateRoom(char id);
bool HasEmptyDoor(ruangan room);
int FindEmptyDoor(ruangan room);
void BuildRandomRoom(ruangan *root);
void printRoom(ruangan roomm);
void MasukPintu(ruangan rooms, bagList *inventory, Player *player);
void FindAvailableRoom(ruangan current, ruangan* list, int* count);
int getKey(ruangan room);

bool cariRuangan(ruangan awal, bool sudahDikunjungi[], char idroom);
ruangan findRoomById(ruangan root, char targetId);
void temukanExit(ruangan posisiSekarang, ruangan rootnya);
void FindAllRooms(ruangan current, ruangan* list, int* count);
void ResetVisited(ruangan current);
void TemukanKunciExit(ruangan current);
void resetVisitedAll(ruangan root);

#endif
