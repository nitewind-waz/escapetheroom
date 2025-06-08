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

Item popBag(bagStack *stack) {
    if (stack->top == NULL) {
        fprintf(stderr, "Stack is empty, cannot pop\n");
        return -1; // Return -1 as error indicator (outside enum range)
    }
    Bag *temp = stack->top;
    Item current = temp->items;
    stack->top = stack->top->next;
    free(temp);

    return current;
}

Item getItem(bagStack *stack) {
    Item current = popBag(stack);
    if (current == -1) {
        fprintf(stderr, "No items in the bag\n");
        return -1; // Return -1 for error
    }
    return current;
}


void printBag(bagStack *stack) {
    Bag *current = stack->top;
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
