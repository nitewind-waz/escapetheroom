#include "../include/bag.h"
#include "../include/room.h"

void initBagList(bagList *list) {
    list->head = NULL;
    setInventory(list);
}

void insertInventory(bagList *list, Item item) {
    Bag *newBag = (Bag *)malloc(sizeof(Bag));
    if (newBag == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newBag->items = item;
    newBag->next = list->head;
    list->head = newBag;
}

void deleteBag(bagList *list, Item item) {
    if (list->head == NULL) {
        fprintf(stderr, "Bag is empty, nothing to delete\n");
        return;
    }

    Bag *temp = list->head;
    Bag *prev = NULL;

    while (temp != NULL && temp->items != item) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        fprintf(stderr, "Item not found in the bag\n");
        return;
    }

    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
}

void printBag(bagList *list) {
    Bag *current = list->head;
    if (current == NULL) {
        printf("Bag is empty.\n");
        return;
    }
    printf("Items in the bag:\n");
    while (current != NULL) {
        if (current->items == exitKey) {
            printf("- Exit Key\n");
        } else if (current->items == roomKey) {
            printf("- Room Key\n");
        }
        current = current->next;
    }
}

void setInventory(bagList *list){
    for (int i = 0; i < 5; i++) {
        insertInventory(list, roomKey);
    }
}
