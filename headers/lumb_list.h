//
// Created by pafnu on 12/28/2024.
//

#ifndef MULTITHREAD_SUM_LUMB_LIST_H
#define MULTITHREAD_SUM_LUMB_LIST_H

#define LIMB_BITS 32 // Define the number of bits per limb

#include <stdio.h>

typedef struct Limb {
    unsigned int value;
    struct Limb *next;
} Limb;

// Define the linked list structure for limbs
typedef struct {
    Limb *head;
    Limb *tail;
    size_t size;
} LimbList;

void init_limb_list(LimbList *list);
void add_limb(LimbList *list, unsigned int value);
void free_limb_list(LimbList *list);
void print_limb_list(const LimbList *list);

void add_limb_lists(const LimbList *a, const LimbList *b, LimbList *result);
void convert_to_limb_list(long long sum, LimbList *limb_list);

#endif //MULTITHREAD_SUM_LUMB_LIST_H
