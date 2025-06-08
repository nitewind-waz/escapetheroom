#ifndef LOCKEDROOM_H
#define LOCKEDROOM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LockedRoom {
    char roomId;
    struct LockedRoom *next;
} LockedRoom;

typedef struct {
    LockedRoom *front, *rear;
} LockedQueue;

void initLockedQueue(LockedQueue *q);



#endif // LOCKEDROOM_H