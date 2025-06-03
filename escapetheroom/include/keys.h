#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BAG_SIZE 3
#define NULL Nil

typedef struct Item {
    bool isA;
    bool isB;
    bool isC;
} Item;

typedef Item infotype;

typedef struct Bag {
    infotype items;
    struct Bag *next;
} Bag;

typedef struct bagStack
{
    Bag *top;
} bagStack;

void initBagStack(bagStack *stack);
