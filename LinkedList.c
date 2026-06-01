#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/*
Initializes and returns a new Node.
Returns NULL if fails.
O(1)
*/
Node *Node_initialize(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = value;
        new_node->next = NULL;
    }
    return new_node;
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
    if (index >= 0) {
        Node *current = l->first;
        int i = 0;
        while (current != NULL) {
            if (i == index) {
                break;
            }
            current = current->next;
            i++;
        }
        return current;
    } else {
        Node *result = l->first;
        Node *current = l->first;
        int pos_index = -index;
        for (int i = 0; i < pos_index; i++) {
            if (current->next == NULL && i != pos_index - 1) return NULL;
            current = current->next;
        }
        while (current != NULL) {
            current = current->next;
            result = result->next;
        }
        return result;
    }
} /* Equivalent but faster than:
Node *LinkedList_find_node(LinkedList *l, int index) {
    // Add the length to negative indices so that they access the list backwards
    if (index < 0) {
        index += LinkedList_length(l);
        if (index < 0) {
            return NULL;
        }
    }

    // Find the node and return NULL if the index is too big
    Node *current = l->first;
    int i = 0;
    while (current != NULL) {
        if (i == index) {
            break;
        }
        current = current->next;
        i++;
    }
    return current;
} */

int LinkedList_is_empty(LinkedList *l) {
    return l->first == NULL;
}

int LinkedList_insert_beginning(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    new->next = l->first;
    l->first = new;

    return 1;
}

int LinkedList_insert_end(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    if (LinkedList_is_empty(l)) l->first = new;
    else LinkedList_find_node(l, -1)->next = new;

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

    return 1;
}

int LinkedList_remove_beginning(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *removed = l->first;
    *value = removed->data;
    l->first = removed->next;
    free(removed);

    return 1;
}

int LinkedList_remove_end(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    if (l->first->next == NULL) {
        *value = l->first->data;
        free(l->first);
        l->first = NULL;
    } else {
        Node *prev_node = LinkedList_find_node(l, -2);
        Node *removed = prev_node->next;
        *value = removed->data;

        free(removed);
        prev_node->next = NULL;
    }

    return 1;
}

int LinkedList_remove_at(LinkedList *l, int index, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    if (index < 0) {
        index += LinkedList_length(l);
        if (index < 0) {
            return 0;
        }
    }

    if (index == 0) return LinkedList_remove_beginning(l, value);
    else {
        Node *prev_node = LinkedList_find_node(l, index - 1);
        if (prev_node == NULL) return 0;
        Node *removed = prev_node->next;
        *value = removed->data;

        prev_node->next = removed->next;
        free(removed);
    }
    
    return 1;
}

int LinkedList_remove_value(LinkedList *l, int value, int *index) {
    if (LinkedList_is_empty(l)) return 0;

    Node *current = l->first;
    int i = 0;
    while (current->next != NULL) {
        if (current->next->data == value) {
            Node *removed = current->next;
            *index = i;

            current->next = removed->next;
            free(removed);
            return 1;
        }

        current = current->next;
        i++;
    }

    return 0;
}

int LinkedList_length(LinkedList *l) {
    Node *current = l->first;
    int length = 0;
    while (current != NULL) {
        current = current->next;
        length++;
    }

    return length;
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
    Node *current = l->first;
    int i = 0;
    while (current != NULL) {
        if (current->data == value) {
            *index = i;
            return 1;
        }
        current = current->next;
        i++;
    }
    return 0;
}

int LinkedList_contains(LinkedList *l, int value) {
    Node *current = l->first;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int LinkedList_count(LinkedList *l, int value) {
    Node *current = l->first;
    int count = 0;
    while (current != NULL) {
        if (current->data == value) {
            count++;
        }
        current = current->next;
    }

    return count;
}

void LinkedList_clear(LinkedList *l) {
    Node *current = l->first;
    while (current != NULL) {
        Node *removed = current;
        current = current->next;
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
    Node *current = other->first;
    while (current != NULL) {
        Node *new = Node_initialize(current->data);
        if (new == NULL) { // If fails to initialize a new node, remove all added nodes.
            current = original_last->next;
            while (current != NULL) {
                Node *removed = current;
                current = current->next;
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

        current = current->next;
        last = last->next;
    }
    return 1;
}

void LinkedList_combine(LinkedList *l, LinkedList *other) {
    if (LinkedList_is_empty(l)) {
        if (LinkedList_is_empty(other)) return;
        l->first = other->first;
    } else LinkedList_find_node(l, -1)->next = other->first;

    LinkedList_clear(other);
    free(other);
}

LinkedList *LinkedList_copy(LinkedList *l) {
    LinkedList *copy = LinkedList_initialize();
    if (copy == NULL) return NULL;

    copy->first = Node_initialize(l->first->data);
    Node *current_copy = copy->first;
    Node *current = l->first->next;
    while (current != NULL) {
        Node *new = Node_initialize(current->data);
        if (new == NULL) {
            LinkedList_clear(copy);
            free(copy);
            return NULL;
        }
        current_copy->next = new;

        current_copy = current_copy->next;
        current = current->next;
    }

    return copy;
}

void LinkedList_print(LinkedList *l) {
    printf("[");
    if (!LinkedList_is_empty(l)) {
        Node *current = l->first;
        while (current->next != NULL) {
            printf("%d, ", current->data);
            current = current->next;
        }
        printf("%d", current->data);
    }
    printf("]");
}
