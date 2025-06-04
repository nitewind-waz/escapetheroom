#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BAG_SIZE 3

#include "room.h"

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
    Bag *top;
} bagStack;

void initBagStack(bagStack *stack);
void pushInventory(bagStack *stack, Item item);
Item popBag(bagStack *stack);
Item getItem(bagStack *stack);
void setItem(bagStack *stack, ruangan room);
void printBag(bagStack *stack);
