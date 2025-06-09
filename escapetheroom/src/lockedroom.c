#include "../include/lockedroom.h"
#include <stdlib.h>
#include <stdio.h>

// Inisialisasi antrian kosong
void initLockedQueue(LockedQueue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Menambahkan ruangan terkunci ke antrian (enqueue)
void enqueueLockedRoom(LockedQueue *queue, char roomID) {
    // Alokasi memori untuk node baru
    LockedRoom *newRoom = (LockedRoom *)malloc(sizeof(LockedRoom));
    if (newRoom == NULL) {
        fprintf(stderr, "Gagal alokasi memori\n");
        return;
    }
    
    // Set nilai node baru
    newRoom->roomID = roomID;
    newRoom->next = NULL;
    
    // Jika antrian kosong, front dan rear menunjuk ke node baru
    if (queue->rear == NULL) {
        queue->front = queue->rear = newRoom;
    } else {
        // Tambahkan node baru di belakang antrian
        queue->rear->next = newRoom;
        queue->rear = newRoom;
    }
}

// Menghapus ruangan terkunci dari antrian (dequeue)
char dequeueLockedRoom(LockedQueue *queue) {
    // Cek jika antrian kosong
    if (isLockedQueueEmpty(queue)) {
        fprintf(stderr, "Antrian kosong, tidak bisa dequeue\n");
        return '\0'; // Return karakter null sebagai penanda error
    }
    
    // Simpan node depan dan ID ruangannya
    LockedRoom *temp = queue->front;
    char roomID = temp->roomID;
    
    // Pindahkan front ke node berikutnya
    queue->front = queue->front->next;
    
    // Jika antrian menjadi kosong, set rear ke NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    // Bebaskan memori node yang dihapus
    free(temp);
    return roomID;
}

// Mengecek apakah antrian kosong
bool isLockedQueueEmpty(LockedQueue *queue) {
    return queue->front == NULL;
}

// Mengecek apakah ruangan tertentu terkunci
bool isRoomLocked(LockedQueue *queue, char roomID) {
    LockedRoom *current = queue->front;
    
    // Iterasi melalui antrian untuk mencari ruangan
    while (current != NULL) {
        if (current->roomID == roomID) {
            return true;  // Ruangan ditemukan dalam antrian terkunci
        }
        current = current->next;
    }
    return false;  // Ruangan tidak terkunci
}

// Mengosongkan seluruh antrian
void clearLockedQueue(LockedQueue *queue) {
    while (!isLockedQueueEmpty(queue)) {
        dequeueLockedRoom(queue);
    }
}