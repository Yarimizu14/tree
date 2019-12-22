#pragma once

#include <stdint.h>

typedef struct node_ {
    int_fast16_t value;
    int_fast8_t height;
    struct node_ *left;
    struct node_ *right;
} node;

int_fast8_t bias(node* n);

