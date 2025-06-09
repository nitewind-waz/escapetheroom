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

// Fungsi untuk mengumpulkan kandidat ruangan
void FindRuanganListRooms(ruangan currentRoom, ruangan* RuanganListList, int* RuanganListCount, LockedQueue* lockedQueue, ruangan root) {
    *RuanganListCount = 0;
    
    // Kandidat awal: Node di bawah posisi saat ini (doors[0-2])
    for (int i = 0; i < 3; i++) {
        if (currentRoom->doors[i] != NULL) {
            RuanganListList[(*RuanganListCount)++] = currentRoom->doors[i];
        }
    }
    
    // Cek apakah ada node terkunci di kandidat awal
    bool hasLockedInRuanganLists = false;
    for (int i = 0; i < *RuanganListCount; i++) {
        if (isRoomLocked(lockedQueue, RuanganListList[i]->id)) {
            hasLockedInRuanganLists = true;
            break;
        }
    }
    
    if (hasLockedInRuanganLists) {
        // Reset kandidat
        *RuanganListCount = 0;
        
        // Tambahkan node di bawah posisi saat ini yang TIDAK terkunci
        for (int i = 0; i < 3; i++) {
            if (currentRoom->doors[i] != NULL && !isRoomLocked(lockedQueue, currentRoom->doors[i]->id)) {
                RuanganListList[(*RuanganListCount)++] = currentRoom->doors[i];
            }
        }
        
        // Tambahkan node di bawah setiap node terkunci
        LockedRoom* lockedNode = lockedQueue->front;
        while (lockedNode != NULL) {
            ruangan lockedRoom = findRoomById(root,lockedNode->roomID);
            if (lockedRoom != NULL) {
                for (int i = 0; i < 3; i++) {
                    if (lockedRoom->doors[i] != NULL) {
                        RuanganListList[(*RuanganListCount)++] = lockedRoom->doors[i];
                    }
                }
            }
            lockedNode = lockedNode->next;
        }
    }
}

// Fungsi utama untuk mengunci ruangan
void LockRandomRoom(ruangan currentRoom, LockedQueue* lockedQueue, ruangan root) {
    ruangan RuanganListRooms[MAX_ROOMS];
    int RuanganListCount = 0;
    
    FindRuanganListRooms(currentRoom, RuanganListRooms, &RuanganListCount, lockedQueue, root);
    
    if (RuanganListCount > 0) {
        ruangan roomToLock = RuanganListRooms[rand() % RuanganListCount];
        
        if (!HasExitRoom(roomToLock) && !isRoomLocked(lockedQueue, roomToLock->id)) {
            enqueueLockedRoom(lockedQueue, roomToLock->id);
            printf("PERINGATAN: Ruangan %c terkunci!\n", roomToLock->id);
        }
    }
}

// Mencetak semua ruangan yang terkunci dalam antrian
void printLockedQueue(LockedQueue queue) {
    if (queue.front == NULL) {
        printf("Tidak ada ruangan yang terkunci.\n");
        return;
    }

    printf("Daftar ruangan yang terkunci: ");
    LockedRoom *current = queue.front;
    while (current != NULL) {
        printf("%c ", current->roomID);
        current = current->next;
    }
    printf("\n");
}