//
// Created by pafnu on 12/28/2024.
//

#include "../headers/lumb_list.h"
#include <stdlib.h>

void init_limb_list(LimbList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Add a limb to the limb list
void add_limb(LimbList *list, unsigned int value) {
    Limb *new_limb = malloc(sizeof(Limb));
    if (!new_limb) {
        perror("Failed to allocate memory for new limb");
        exit(EXIT_FAILURE);
    }
    new_limb->value = value;
    new_limb->next = NULL;

    // If the list is empty (both head and tail are NULL)
    if (list->head == NULL) {
        // Set both head and tail to the new limb
        list->head = new_limb;
        list->tail = new_limb;
    } else {
        // List is not empty, append to tail
        list->tail->next = new_limb;
        list->tail = new_limb;
    }
    list->size++;
}
// Free the memory allocated for the limb list
void free_limb_list(LimbList *list) {
    Limb *current = list->head;
    Limb *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Print all limbs in the limb list
void print_limb_list(const LimbList *list) {
    if (!list->head) {
        printf("Value: 0\n");
        return;
    }

    long long value = 0;
    Limb *current = list->head;
    int shift = 0;
    int is_negative = 0;

    // Process all limbs
    while (current) {
        if (current->next == NULL && (current->value & 0x80000000)) {
            // Handle sign bit in the last limb
            is_negative = 1;
            value |= ((long long)(current->value & 0x7FFFFFFF) << shift);
        } else {
            value |= ((long long)current->value << shift);
        }
        shift += 32;
        current = current->next;
    }

    if (is_negative) {
        value = -value;
    }

    printf("Value: %lld\n", value);
}

// Add two limb lists and store the result in a third list
void add_limb_lists(const LimbList *a, const LimbList *b, LimbList *result) {
    Limb *current_a = a->head;
    Limb *current_b = b->head;
    long long carry = 0;  // Changed to signed for handling negative numbers

    while (current_a || current_b || carry) {
        long long sum = carry;
        if (current_a) {
            // Handle sign bit if it's the last limb
            if (current_a->next == NULL && (current_a->value & 0x80000000)) {
                sum -= (long long)(current_a->value & 0x7FFFFFFF);
            } else {
                sum += current_a->value;
            }
            current_a = current_a->next;
        }
        if (current_b) {
            // Handle sign bit if it's the last limb
            if (current_b->next == NULL && (current_b->value & 0x80000000)) {
                sum -= (long long)(current_b->value & 0x7FFFFFFF);
            } else {
                sum += current_b->value;
            }
            current_b = current_b->next;
        }

        add_limb(result, (unsigned int)(sum & 0xFFFFFFFF));
        carry = sum >> 32;
    }
}
// Convert a long long sum to a limb list
void convert_to_limb_list(long long sum, LimbList *limb_list) {
    // Handle case when sum is zero
    if (sum == 0) {
        add_limb(limb_list, 0);
        return;
    }

    // Store sign and work with absolute value
    int is_negative = (sum < 0);
    unsigned long long abs_sum = (is_negative) ? -sum : sum;

    // Convert to limbs
    do {
        add_limb(limb_list, (unsigned int)(abs_sum & 0xFFFFFFFF));
        abs_sum >>= 32;
    } while (abs_sum > 0);

    // Store sign in the highest limb if negative
    if (is_negative) {
        // Set the sign bit in the highest limb
        Limb *last = limb_list->tail;
        if (last) {
            last->value |= 0x80000000;
        }
    }
}
