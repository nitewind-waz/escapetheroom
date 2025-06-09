#ifndef BAG_H
#define BAG_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BAG_SIZE 3

typedef enum {
    exitKey,
    roomKey,
} Item;

typedef struct Bag {
    Item items;
    struct Bag *next;
} Bag;

typedef struct bagStack
{
    Bag *head;
} bagList;

void initBagList(bagList *list);
void insertInventory(bagList *list, Item item);
void deleteBag(bagList *list, Item item);
void printBag(bagList *list);
void setInventory (bagList *list);
bool pHasDoor(bagList *list);

#endif