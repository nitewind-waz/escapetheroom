#include "../include/lockedroom.h"

void initLockedQueue(LockedQueue *q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueueLockedRoom(LockedQueue *q, char roomId) {
    LockedRoom *newRoom = (LockedRoom *)malloc(sizeof(LockedRoom));
    if (newRoom == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newRoom->roomId = roomId;
    newRoom->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newRoom;
    } else {
        q->rear->next = newRoom;
        q->rear = newRoom;
    }
}