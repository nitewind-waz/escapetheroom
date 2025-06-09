#include "room.h"

typedef struct riwayat {
    ruangan Rooms;
    struct riwayat *next;
} riwayat;

typedef struct {
    riwayat *top;
} StackRoom;

void createEmpty(StackRoom* s);
void PushHistory(StackRoom* s, ruangan Room);
ruangan Pop(StackRoom* s);
bool IsEmpty (StackRoom* S);
void PrintHistory(StackRoom s);