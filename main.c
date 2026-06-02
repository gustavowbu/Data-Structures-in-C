#include <stdio.h>
#include "HeadedLinkedList.h"

int main() {
    // LinkedList *l = LinkedList_initialize();

    // printf("\n");
    // LinkedList_print(l); printf("\n");
    // LinkedList_insert_end(l, 2);
    // LinkedList_insert_end(l, 5);
    // LinkedList_insert_beginning(l, 3);
    // LinkedList_print(l); printf("\n");
    // printf("List size: %d\n", LinkedList_size(l));

    // int value;
    // LinkedList_get(l, 1, &value);
    // printf("Index 1: %d\n", value);

    // LinkedList_set(l, 2, 6);
    // LinkedList_print(l); printf("\n");
    // LinkedList_print(LinkedList_copy(l));

    int x = 0;
    int *x1 = &x;
    int **x2 = &x1;

    printf("%d\n", x);
    printf("%p\n", &x);
    printf("\n");
    printf("%d\n", *x1);
    printf("%p\n", x1);
    printf("%p\n", &x1);
    printf("\n");
    printf("%d\n", **x2);
    printf("%p\n", *x2);
    printf("%p\n", x2);

    return 0;
}
