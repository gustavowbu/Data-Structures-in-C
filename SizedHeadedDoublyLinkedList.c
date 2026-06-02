#include <stdio.h>
#include <stdlib.h>
#include "SizedHeadedDoublyLinkedList.h"

/*
Initializes and returns a new Node.
Returns NULL if fails.
O(1)
*/
Node *Node_initialize(int value) {
    Node *node = malloc(sizeof(Node));
    if (node != NULL) {
        node->data = value;
        node->prev = NULL;
        node->next = NULL;
    }
    return node;
}

LinkedList *LinkedList_initialize() {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list != NULL) {
        list->head = Node_initialize(0);
        list->size = 0;
        if (list->head == NULL) {
            free(list);
            return NULL;
        }
    }
    return list;
}

/*
Returns the Node of the LinkedList at index 'index'.
Returns the head if index is -1.
Returns NULL if fails.
O(n)
*/
Node *LinkedList_find_node_headed(LinkedList *l, int index) {
    Node *node = l->head;
    int i = -1;
    while (node != NULL) {
        if (i == index) {
            break;
        }
        node = node->next;
        i++;
    }
    return node;
}

/*
Returns the Node of the LinkedList at index 'index'.
Returns the head if index is -1.
Returns NULL if fails.
O(n)
*/
Node *LinkedList_find_node_headed(LinkedList *l, int index) {
    Node *node = l->head;
    int i = -1;
    while (node != NULL) {
        if (i == index) {
            break;
        }
        node = node->next;
        i++;
    }
    return node;
}

/*
Returns the Node of the LinkedList at the given index.
Returns the Node of the reversed LinkedList at -(index + 1) if index < 0.
Returns the head if index is -(size + 1).
Returns NULL if fails.
O(n)
*/
Node *LinkedList_find_node(LinkedList *l, int index) {
    // Add the size to negative indices so that they access the list backwards
    if (index < 0) {
        index += l->size;
        if (index < 0) return NULL;
    }

    Node *node = l->head->next;
    int i = 0;
    while (node != NULL) {
        if (i == index) {
            break;
        }
        node = node->next;
        i++;
    }
    return node;
}

int LinkedList_is_empty(LinkedList *l) {
    return l->size == 0;
}

int LinkedList_insert_beginning(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    if (!LinkedList_is_empty(l)) l->head->next->prev = new;
    new->next = l->head->next;
    new->prev = l->head;
    l->head->next = new;
    l->size++;

    return 1;
}

int LinkedList_insert_end(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    Node *last = LinkedList_find_node_headed(l, -1);
    last->next = new;
    new->prev = last;
    l->size++;

    return 1;
}

int LinkedList_insert_at(LinkedList *l, int index, int value) {
    Node *prev_node;
    if (index >= 0) prev_node = LinkedList_find_node_headed(l, index - 1);
    else prev_node = LinkedList_find_node(l, index);
    if (prev_node == NULL) return 0;

    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    new->prev = prev_node;
    new->next = prev_node->next;
    if (prev_node->next != NULL) prev_node->next->prev = new;
    prev_node->next = new;
    l->size++;

    return 1;
}

int LinkedList_remove_beginning(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *removed = l->head->next;
    *value = removed->data;

    l->head->next = removed->next;
    l->head->next->prev = l->head;
    free(removed);
    l->size--;

    return 1;
}

int LinkedList_remove_end(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *removed = LinkedList_find_node(l, -1);
    *value = removed->data;

    removed->prev->next = NULL;
    free(removed);
    l->size--;

    return 1;
}

int LinkedList_remove_at(LinkedList *l, int index, int *value) {
    Node *removed = LinkedList_find_node(l, index);
    if (removed == NULL) return 0;
    *value = removed->data;

    if (removed->next != NULL) removed->next->prev = removed->prev;
    if (removed->prev != NULL) removed->prev->next = removed->next;
    free(removed);
    l->size--;

    return 1;
}

int LinkedList_remove_value(LinkedList *l, int value, int *index) {
    Node *node = l->head->next;
    int i = 0;
    while (node != NULL) {
        if (node->data == value) {
            *index = i;

            if (node->next != NULL) node->next->prev = node->prev;
            if (node->prev != NULL) node->prev->next = node->next;
            free(node);
            l->size--;

            return 1;
        }

        node = node->next;
        i++;
    }

    return 0;
}

int LinkedList_size(LinkedList *l) {
    return l->size;
}

int LinkedList_get(LinkedList *l, int index, int *value) {
    Node *node = LinkedList_find_node(l, index);
    if (node == NULL) return 0;

    *value = node->data;
    return 1;
}

int LinkedList_set(LinkedList *l, int index, int value) {
    Node *node = LinkedList_find_node(l, index);
    if (node == NULL) return 0;

    node->data = value;
    return 1;
}

int LinkedList_index(LinkedList *l, int value, int *index) {
    Node *node = l->head->next;
    int i = 0;
    while (node != NULL) {
        if (node->data == value) {
            *index = i;
            return 1;
        }
        node = node->next;
        i++;
    }
    return 0;
}

int LinkedList_contains(LinkedList *l, int value) {
    Node *node = l->head->next;
    while (node != NULL) {
        if (node->data == value) {
            return 1;
        }
        node = node->next;
    }

    return 0;
}

int LinkedList_count(LinkedList *l, int value) {
    Node *node = l->head->next;
    int count = 0;
    while (node != NULL) {
        if (node->data == value) {
            count++;
        }
        node = node->next;
    }

    return count;
}

void LinkedList_clear(LinkedList *l) {
    Node *node = l->head->next;
    while (node != NULL) {
        Node *removed = node;
        node = node->next;
        free(removed);
    }
    l->head->next = NULL;
}

int LinkedList_extend(LinkedList *l, LinkedList *other) {
    Node *last = LinkedList_find_node_headed(l, -1);
    Node *original_last = last;
    Node *node = other->head->next;
    while (node != NULL) {
        Node *new = Node_initialize(node->data);
        if (new == NULL) { // If fails to initialize a new node, remove all added nodes.
            node = original_last->next;
            while (node != NULL) {
                Node *removed = node;
                node = node->next;
                free(removed);
            }
            original_last->next = NULL;

            return 0;
        }
        last->next = new;
        new->prev = last;

        node = node->next;
        last = last->next;
    }

    l->size += other->size;
    return 1;
}

void LinkedList_combine(LinkedList *l, LinkedList *other) {
    Node *last = LinkedList_find_node_headed(l, -1);
    last->next = other->head->next;
    other->head->next->prev = last;

    l->size += other->size;
    free(other);
}

LinkedList *LinkedList_copy(LinkedList *l) {
    LinkedList *copy = LinkedList_initialize();
    if (copy == NULL) return NULL;

    Node *node_copy = copy->head;
    Node *node = l->head->next;
    while (node != NULL) {
        Node *new = Node_initialize(node->data);
        if (new == NULL) {
            LinkedList_clear(copy);
            free(copy);
            return NULL;
        }
        node_copy->next = new;
        new->prev = node_copy;

        node_copy = node_copy->next;
        node = node->next;
    }

    copy->size = l->size;
    return copy;
}

void LinkedList_print(LinkedList *l) {
    printf("[");
    if (!LinkedList_is_empty(l)) {
        Node *node = l->head->next;
        while (node->next != NULL) {
            printf("%d, ", node->data);
            node = node->next;
        }
        printf("%d", node->data);
    }
    printf("]");
}

void LinkedList_free(LinkedList *l) {
    LinkedList_clear(l);
    free(l);
}
