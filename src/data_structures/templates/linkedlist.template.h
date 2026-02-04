
#ifndef LL_{{TYPE_NAME}}_H
#define LL_{{TYPE_NAME}}_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
{{TYPE_INCLUDES}}

typedef struct LLNode_{{TYPE_NAME}} {
    {{TYPE}} data;
    struct LLNode_{{TYPE_NAME}} *next;
} LLNode_{{TYPE_NAME}};

typedef struct LinkedList_{{TYPE_NAME}}{
    LLNode_{{TYPE_NAME}} *head;
    size_t size;
} LinkedList_{{TYPE_NAME}};

static inline LinkedList_{{TYPE_NAME}} *ll_{{TYPE_NAME}}_create(void) {
    LinkedList_{{TYPE_NAME}} *list = malloc(sizeof(*list));
    if (!list) { perror("malloc"); exit(EXIT_FAILURE); }
    list->head = NULL;
    list->size = 0;
    return list;
}

static inline void ll_{{TYPE_NAME}}_destroy(LinkedList_{{TYPE_NAME}} *list) {
    LLNode_{{TYPE_NAME}} *curr = list->head;
    while (curr) {
        LLNode_{{TYPE_NAME}} *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(list);
}

static inline void ll_{{TYPE_NAME}}_push_front(
    LinkedList_{{TYPE_NAME}} *list, {{TYPE}} value
) {
    LLNode_{{TYPE_NAME}} *node = malloc(sizeof(*node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = value;
    node->next = list->head;
    list->head = node;
    list->size++;
}

static inline {{TYPE}} ll_{{TYPE_NAME}}_pop_front(
    LinkedList_{{TYPE_NAME}} *list
) {
    if (!list->head) {
        fprintf(stderr, "LinkedList empty\n");
        exit(EXIT_FAILURE);
    }
    LLNode_{{TYPE_NAME}} *node = list->head;
    {{TYPE}} val = node->data;
    list->head = node->next;
    free(node);
    list->size--;
    return val;
}

static inline {{TYPE}} ll_{{TYPE_NAME}}_peek_front(
    LinkedList_{{TYPE_NAME}} *list
) {
    if (!list->head) {
        fprintf(stderr, "LinkedList empty\n");
        exit(EXIT_FAILURE);
    }
    return list->head->data;
}

static inline size_t ll_{{TYPE_NAME}}_size(
    LinkedList_{{TYPE_NAME}} *list
) {
    return list->size;
}

static inline int ll_{{TYPE_NAME}}_empty(
    LinkedList_{{TYPE_NAME}} *list
) {
    return list->size == 0;
}

static inline void ll_{{TYPE_NAME}}_delete_value(LinkedList_{{TYPE_NAME}} *list, {{TYPE}} value) {
    LLNode_{{TYPE_NAME}} *curr = list->head;
    LLNode_{{TYPE_NAME}} *prev = NULL;

    while (curr) {
        if (curr->data == value) {
            LLNode_{{TYPE_NAME}} *to_free = curr;
            if (prev == NULL) {
                list->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            curr = curr->next;
            free(to_free);
            list->size--;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}


static inline void ll_{{TYPE_NAME}}_insert_relative(
    LinkedList_{{TYPE_NAME}} *list, {{TYPE}} target, {{TYPE}} new_value, bool after
) {
    LLNode_{{TYPE_NAME}} *curr = list->head;
    LLNode_{{TYPE_NAME}} *prev = NULL;

    while (curr) {
        if (curr->data == target) {
            LLNode_{{TYPE_NAME}} *new_node = malloc(sizeof(*new_node));
            if (!new_node) { perror("malloc"); exit(EXIT_FAILURE); }
            new_node->data = new_value;

            if (after) {
                new_node->next = curr->next;
                curr->next = new_node;
            } else {
                new_node->next = curr;
                if (prev == NULL) {
                    list->head = new_node;
                } else {
                    prev->next = new_node;
                }
            }
            list->size++;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

static inline {{TYPE}} ll_{{TYPE_NAME}}_get_at(LinkedList_{{TYPE_NAME}} *list, int index) {
    if (index < 0 || (size_t)index >= list->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    LLNode_{{TYPE_NAME}} *curr = list->head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

#endif
