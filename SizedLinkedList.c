#include <stdio.h>
#include <stdlib.h>
#include "SizedLinkedList.h"

/*
Initializes and returns a new Node.
Returns NULL if fails.
O(1)
*/
Node *Node_initialize(int value) {
    Node *node = malloc(sizeof(Node));
    if (node != NULL) {
        node->data = value;
        node->next = NULL;
    }
    return node;
}

LinkedList *LinkedList_initialize() {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list != NULL) {
        list->first = NULL;
        list->size = 0;
    }
    return list;
}

/*
Returns the Node of the LinkedList at the given index.
Returns NULL if fails.
O(n)
*/
Node *LinkedList_find_node(LinkedList *l, int index) {
    // Add the size to negative indices so that they access the list backwards
    if (index < 0) {
        index += l->size;
        if (index < 0) return NULL;
    }

    Node *node = l->first;
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

    new->next = l->first;
    l->first = new;
    l->size++;

    return 1;
}

int LinkedList_insert_end(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    if (LinkedList_is_empty(l)) l->first = new;
    else LinkedList_find_node(l, -1)->next = new;
    l->size++;

    return 1;
}

int LinkedList_insert_at(LinkedList *l, int index, int value) {
    if (index == 0) return LinkedList_insert_beginning(l, value);

    Node *prev_node;
    if (index > 0) prev_node = LinkedList_find_node(l, index - 1);
    else prev_node = LinkedList_find_node(l, index);
    if (prev_node == NULL) return 0;

    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    new->next = prev_node->next;
    prev_node->next = new;
    l->size++;

    return 1;
}

int LinkedList_remove_beginning(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *removed = l->first;
    *value = removed->data;
    l->first = removed->next;
    free(removed);
    l->size--;

    return 1;
}

int LinkedList_remove_end(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    if (l->first->next == NULL) return LinkedList_remove_beginning(l, value);

    Node *prev_node = LinkedList_find_node(l, -2);
    Node *removed = prev_node->next;
    *value = removed->data;

    free(removed);
    prev_node->next = NULL;
    l->size--;

    return 1;
}

int LinkedList_remove_at(LinkedList *l, int index, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    // Add the size to negative indices so that they access the list backwards
    if (index < 0) {
        index += l->size;
        if (index < 0) return NULL;
    }

    if (index == 0) return LinkedList_remove_beginning(l, value);

    Node *prev_node = LinkedList_find_node(l, index - 1);
    if (prev_node == NULL) return 0;
    Node *removed = prev_node->next;
    *value = removed->data;

    prev_node->next = removed->next;
    free(removed);
    l->size--;

    return 1;
}

int LinkedList_remove_value(LinkedList *l, int value, int *index) {
    if (LinkedList_is_empty(l)) return 0;

    if (l->first->data == value) {
        *index = 0;
        return LinkedList_remove_beginning(l, &value);
    }

    Node *node = l->first;
    int i = 0;
    while (node->next != NULL) {
        if (node->next->data == value) {
            Node *removed = node->next;
            *index = i;

            node->next = removed->next;
            free(removed);
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
    Node *node = l->first;
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
    Node *node = l->first;
    while (node != NULL) {
        if (node->data == value) {
            return 1;
        }
        node = node->next;
    }

    return 0;
}

int LinkedList_count(LinkedList *l, int value) {
    Node *node = l->first;
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
    Node *node = l->first;
    while (node != NULL) {
        Node *removed = node;
        node = node->next;
        free(removed);
    }
    l->first = NULL;
    l->size = 0;
}

int LinkedList_extend(LinkedList *l, LinkedList *other) {
    int list_started_empty = LinkedList_is_empty(l);

    if (list_started_empty) {
        if (LinkedList_is_empty(other)) return 1;
        if (LinkedList_insert_beginning(l, other->first->data) == 0) return 0;
    }

    Node *last = LinkedList_find_node(l, -1);
    Node *original_last = last;
    Node *node = other->first;
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
            if (list_started_empty) {
                free(original_last);
                l->first = NULL;
            }
            return 0;
        }
        last->next = new;

        node = node->next;
        last = last->next;
    }

    l->size += other->size;
    return 1;
}

void LinkedList_combine(LinkedList *l, LinkedList *other) {
    if (LinkedList_is_empty(l)) {
        if (LinkedList_is_empty(other)) return;
        l->first = other->first;
    } else LinkedList_find_node(l, -1)->next = other->first;

    l->size += other->size;
    free(other);
}

LinkedList *LinkedList_copy(LinkedList *l) {
    if (LinkedList_is_empty(l)) return LinkedList_initialize();

    LinkedList *copy = LinkedList_initialize();
    if (copy == NULL) return NULL;

    copy->first = Node_initialize(l->first->data);
    Node *node_copy = copy->first;
    Node *node = l->first->next;
    while (node != NULL) {
        Node *new = Node_initialize(node->data);
        if (new == NULL) {
            LinkedList_clear(copy);
            free(copy);
            return NULL;
        }
        node_copy->next = new;

        node_copy = node_copy->next;
        node = node->next;
    }

    copy->size = l->size;
    return copy;
}

void LinkedList_print(LinkedList *l) {
    printf("[");
    if (!LinkedList_is_empty(l)) {
        Node *node = l->first;
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
