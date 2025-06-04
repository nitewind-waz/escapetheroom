#include "../include/bag.h"
#include "../include/room.h"

void initBagStack(bagStack *stack) {
    stack->top = NULL;
}

void pushInventory(bagStack *stack, Item item) {
    Bag *newBag = (Bag *)malloc(sizeof(Bag));
    if (newBag == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    newBag->items = item;
    newBag->next = stack->top;
    stack->top = newBag;
}

int popBag(bagStack *stack) {
    Item current;
    if (stack->top == NULL) {
        fprintf(stderr, "Stack is empty, cannot pop\n");
        return;
    }
    Bag *temp = stack->top;
    current = temp->items;
    stack->top = stack->top->next;
    free(temp);

    return current;
}

int getItem(bagStack *stack) {
    Item current = popBag(stack);
    if (current == NULL) {
        fprintf(stderr, "No items in the bag\n");
        return -1; // Indicating no item was found
    }
    return current;
}

void setItem(bagStack *stack, ruangan room) {
    Item item = getKey(room);
    pushInventory(stack, item);
}
