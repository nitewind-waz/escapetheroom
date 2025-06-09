#include "../include/stack.h"

void PushHistory(StackRoom* s, ruangan Room){
    riwayat *newRiwayatRoom = (riwayat*)malloc(sizeof(riwayat));
    if (newRiwayatRoom != NULL)
    {
        newRiwayatRoom->Rooms = Room;
        newRiwayatRoom->next = s->top;
        s->top = newRiwayatRoom;
    }
}

ruangan Pop(StackRoom* s) {
    if (IsEmpty(s)) return NULL;

    riwayat* temp = s->top;
    ruangan room = temp->Rooms;
    s->top = temp->next;
    free(temp);
    return room;
}

bool IsEmpty (StackRoom* S)
{
	return (S->top == NULL);
}

void createEmpty(StackRoom *s){
    s->top = NULL;
}

void PrintHistory(StackRoom s) {
    riwayat* temp = s.top;

    while (temp != NULL) {
        printf("-> %c\n", temp->Rooms->id);
        temp = temp->next;
    }
}