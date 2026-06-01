#include <stdio.h>
#include <stdlib.h>
#include "HeadedLinkedList.h"

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
    if (list != NULL) {
        list->head = Node_initialize(0);
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
    Node *current = l->head;
    int i = -1;
    while (current != NULL) {
        if (i == index) {
            break;
        }
        current = current->next;
        i++;
    }
    return current;
}

/*
Returns the Node of the LinkedList at the given index.
Returns the Node of the reversed LinkedList at -(index + 1) if index < 0.
Returns the head if index is -(length + 1).
Returns NULL if fails.
O(n)
*/
Node *LinkedList_find_node(LinkedList *l, int index) {
    if (index >= 0) {
        Node *current = l->head;
        int i = -1;
        while (current != NULL) {
            if (i == index) {
                break;
            }
            current = current->next;
            i++;
        }
        return current;
    } else {
        Node *result = l->head;
        Node *current = l->head;
        for (int i = 0; i < -index; i++) {
            if (current->next == NULL) return NULL;
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
    Node *current = l->head;
    int i = -1;
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
    return l->head->next == NULL;
}

int LinkedList_insert_beginning(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    new->next = l->head->next;
    l->head->next = new;

    return 1;
}

int LinkedList_insert_end(LinkedList *l, int value) {
    Node *new = Node_initialize(value);
    if (new == NULL) return 0;

    LinkedList_find_node_headed(l, -1)->next = new;

    return 1;
}

int LinkedList_insert_at(LinkedList *l, int index, int value) {
    Node *prev_node;
    if (index >= 0) prev_node = LinkedList_find_node_headed(l, index - 1);
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

    Node *removed = l->head->next;
    *value = removed->data;

    l->head->next = removed->next;
    free(removed);

    return 1;
}

int LinkedList_remove_end(LinkedList *l, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *prev_node = LinkedList_find_node(l, -2);
    Node *removed = prev_node->next;
    *value = removed->data;

    free(removed);
    prev_node->next = NULL;

    return 1;
}

int LinkedList_remove_at(LinkedList *l, int index, int *value) {
    if (LinkedList_is_empty(l)) return 0;

    Node *prev_node;
    if (index >= 0) prev_node = LinkedList_find_node_headed(l, index - 1);
    else prev_node = LinkedList_find_node(l, index - 1);
    if (prev_node == NULL) return 0;

    Node *removed = prev_node->next;
    *value = removed->data;

    prev_node->next = removed->next;
    free(removed);
    
    return 1;
}

int LinkedList_remove_value(LinkedList *l, int value, int *index) {
    Node *current = l->head;
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
    Node *current = l->head->next;
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
    Node *current = l->head->next;
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
    Node *current = l->head->next;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int LinkedList_count(LinkedList *l, int value) {
    Node *current = l->head->next;
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
    Node *current = l->head->next;
    while (current != NULL) {
        Node *removed = current;
        current = current->next;
        free(removed);
    }
    l->head->next = NULL;
}

int LinkedList_extend(LinkedList *l, LinkedList *other) {
    Node *last = LinkedList_find_node_headed(l, -1);
    Node *original_last = last;
    Node *current = other->head->next;
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
            return 0;
        }
        last->next = new;

        current = current->next;
        last = last->next;
    }
    return 1;
}

void LinkedList_combine(LinkedList *l, LinkedList *other) {
    LinkedList_find_node_headed(l, -1)->next = other->head->next;

    LinkedList_clear(other);
    free(other);
}

LinkedList *LinkedList_copy(LinkedList *l) {
    LinkedList *copy = LinkedList_initialize();
    if (copy == NULL) return NULL;

    Node *current_copy = copy->head;
    Node *current = l->head->next;
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
        Node *current = l->head->next;
        while (current->next != NULL) {
            printf("%d, ", current->data);
            current = current->next;
        }
        printf("%d", current->data);
    }
    printf("]");
}
