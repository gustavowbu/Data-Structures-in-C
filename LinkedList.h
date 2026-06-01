#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *first;
} LinkedList;

/*
Initializes and returns a new LinkedList.
Returns NULL if fails.
O(1)
*/
LinkedList *LinkedList_initialize();

/*
Returns 1 if LinkedList is empty, 0 otherwise.
O(1)
*/
int LinkedList_is_empty(LinkedList *l);

/*
Inserts a new element at the beginning of the LinkedList.
Returns 1 if successful, 0 otherwise.
O(1)
*/
int LinkedList_insert_beginning(LinkedList *l, int value);

/*
Inserts a new element at the end of LinkedList.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_insert_end(LinkedList *l, int value);

/*
Inserts a new element before the element at the given index of the LinkedList.
For example, index=0 inserts at the beginning.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_insert_at(LinkedList *l, int index, int value);

/*
Removes the first element of the LinkedList.
Assigns its value to the parameter value.
Returns 1 if successful, 0 otherwise.
O(1)
*/
int LinkedList_remove_beginning(LinkedList *l, int *value);

/*
Removes the last element of the LinkedList.
Assigns its value to the parameter value.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_remove_end(LinkedList *l, int *value);

/*
Removes the element at the given index of the LinkedList.
Assigns its value to the parameter value.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_remove_at(LinkedList *l, int index, int *value);

/*
Removes the first element of the LinkedList that has the given value.
Assigns its index to the parameter index.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_remove_value(LinkedList *l, int value, int *index);

/*
Returns the length of the LinkedList.
O(n)
*/
int LinkedList_length(LinkedList *l);

/*
Assigns the value at the given index of the LinkedList to the parameter value.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_get(LinkedList *l, int index, int *value);

/*
Assigns the given value to the element at the given index of the LinkedList.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_set(LinkedList *l, int index, int value);

/*
Assigns the index of the first element of the LinkedList that has the given value to the parameter index.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_index(LinkedList *l, int value, int *index);

/*
Returns 1 if the LinkedList contains the given value, 0 otherwise.
O(n)
*/
int LinkedList_contains(LinkedList *l, int value);

/*
Returns the number of elements in the LinkedList with the given value.
Returns 0 if there are none.
O(n)
*/
int LinkedList_count(LinkedList *l, int value);

/*
Clears the LinkedList.
O(n)
*/
void LinkedList_clear(LinkedList *l);

/*
Inserts the elements of the other LinkedList to the end of the LinkedList.
Returns 1 if successful, 0 otherwise.
O(n)
*/
int LinkedList_extend(LinkedList *l, LinkedList *other);

/*
Inserts the elements of the other LinkedList to the end of the LinkedList
and clears and frees the other LinkedList.
O(n)
*/
void LinkedList_combine(LinkedList *l, LinkedList *other);

/*
Returns a copy of the LinkedList.
Returns NULL if fails.
O(n)
*/
LinkedList *LinkedList_copy(LinkedList *l);

/*
Prints the LinkedList.
O(n)
*/
void LinkedList_print(LinkedList *l);

/*
Functions and their complixities:
- LinkedList_initialize       - O(1)
- LinkedList_is_empty         - O(1)
- LinkedList_insert_beginning - O(1)
- LinkedList_insert_end       - O(n)
- LinkedList_insert_at        - O(n)
- LinkedList_remove_beginning - O(1)
- LinkedList_remove_end       - O(n)
- LinkedList_remove_at        - O(n)
- LinkedList_remove_value     - O(n)
- LinkedList_length           - O(n)
- LinkedList_get              - O(n)
- LinkedList_set              - O(n)
- LinkedList_index            - O(n)
- LinkedList_contains         - O(n)
- LinkedList_count            - O(n)
- LinkedList_clear            - O(n)
- LinkedList_extend           - O(n)
- LinkedList_combine          - O(n)
- LinkedList_copy             - O(n)
- LinkedList_print            - O(n)

More generally:
- is_empty - O(1)
- length   - O(n)
- insert   - O(n)
- remove   - O(n)
- search   - O(n)
- print    - O(n)
*/

#endif
