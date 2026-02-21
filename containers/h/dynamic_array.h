#pragma once

#include "defines.h"

typedef struct dynamic_array darray_t;

KAPI darray_t* darray_create(u64 initial_capacity, u64 elem_size);
KAPI b8 darray_push(darray_t* darr, void* data);
KAPI b8 darray_pop(darray_t* darr);
KAPI darray_t* darray_destroy(darray_t* darr);
