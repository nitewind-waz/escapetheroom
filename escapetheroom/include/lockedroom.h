#ifndef LOCKEDROOM_H
#define LOCKEDROOM_H

#include <stdbool.h>

// Struktur node untuk ruangan terkunci
typedef struct LockedRoom {
    char roomID;             
    struct LockedRoom *next;  
} LockedRoom;

// Struktur antrian untuk ruangan terkunci
typedef struct {
    LockedRoom *front;  
    LockedRoom *rear;   
} LockedQueue;

// Fungsi untuk menginisialisasi antrian
void initLockedQueue(LockedQueue *queue);
void enqueueLockedRoom(LockedQueue *queue, char roomID);
char dequeueLockedRoom(LockedQueue *queue);
bool isLockedQueueEmpty(LockedQueue *queue);
bool isRoomLocked(LockedQueue *queue, char roomID);
void clearLockedQueue(LockedQueue *queue);

#endif