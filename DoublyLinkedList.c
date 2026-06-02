#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"

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
    if (list != NULL) list->first = NULL;
    return list;
}

/*
Returns the Node of the LinkedList at the given index.
Returns NULL if fails.
O(n)
*/
Node *LinkedList_find_node(LinkedList *l, int index) {
    if (index >= 0) { // index >= 0
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
    } else { // index < 0. Access the list backwards
        // setup two Node pointers (-index) apart
        Node *result = l->first;
        Node *node = l->first;
        int pos_index = -index;
        for (int i = 0; i < pos_index; i++) {
            if (node->next == NULL && i != pos_index - 1) return NULL;
            node = node->next;
        }

        // walk both until the front pointer reaches the end. The other is the result
        while (node != NULL) {
            node = node->next;
            result = result->next;
        }
        return result;
    }
} /* Equivalent but faster than:
Node *LinkedList_find_node(LinkedList *l, int index) {
    // Add the size to negative indices so that they access the list backwards
    if (index < 0) {
        index += LinkedList_size(l);
        if (index < 0) return NULL;
    }

    // Find the node and return NULL if the index is too big
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
} */

int LinkedList_is_empty(LinkedList *l) {
    return l->first == NULL;
}

int LinkedList_insert_beginning(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    if (!LinkedList_is_empty(l)) l->first->prev = new;
    new->next = l->first;
    l->first = new;

    return 1;
}

int LinkedList_insert_end(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    if (LinkedList_is_empty(l)) l->first = new;
    else {
        Node * last = LinkedList_find_node(l, -1);
        last->next = new;
        new->prev = last;
    }

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

    new->prev = prev_node;
    new->next = prev_node->next;
    if (prev_node->next != NULL) prev_node->next->prev = new;
    prev_node->next = new;

    return 1;
}

int LinkedList_remove_beginning(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *removed = l->first;
    *value = removed->data;

    l->first = removed->next;
    l->first->prev = NULL;
    free(removed);

    return 1;
}

int LinkedList_remove_end(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *removed = LinkedList_find_node(l, -1);
    *value = removed->data;

    if (removed->prev != NULL) removed->prev->next = NULL;
    else l->first = NULL;
    free(removed);

    return 1;
}

int LinkedList_remove_at(LinkedList *l, int index, int *value) {
    Node *removed = LinkedList_find_node(l, index);
    if (removed == NULL) return 0;
    *value = removed->data;

    if (removed->next != NULL) removed->next->prev = removed->prev;
    if (removed->prev != NULL) removed->prev->next = removed->next;
    free(removed);

    return 1;
}

int LinkedList_remove_value(LinkedList *l, int value, int *index) {
    Node *node = l->first;
    int i = 0;
    while (node != NULL) {
        if (node->data == value) {
            *index = i;

            if (node->next != NULL) node->next->prev = node->prev;
            if (node->prev != NULL) node->prev->next = node->next;
            free(node);

            return 1;
        }

        node = node->next;
        i++;
    }

    return 0;
}

int LinkedList_size(LinkedList *l) {
    Node *node = l->first;
    int size = 0;
    while (node != NULL) {
        node = node->next;
        size++;
    }

    return size;
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
        new->prev = last;

        node = node->next;
        last = last->next;
    }
    return 1;
}

void LinkedList_combine(LinkedList *l, LinkedList *other) {
    if (LinkedList_is_empty(l)) {
        if (LinkedList_is_empty(other)) return;
        l->first = other->first;
    } else {
        Node *last = LinkedList_find_node(l, -1);
        last->next = other->first;
        other->first->prev = last;
    }

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
        new->prev = node_copy;

        node_copy = node_copy->next;
        node = node->next;
    }

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
