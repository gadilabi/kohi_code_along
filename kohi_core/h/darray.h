#pragma once

#include "defines.h"

typedef struct dynamic_array darray_t;

KAPI darray_t* darray_create(u64 initial_capacity, u64 elem_size);
KAPI void darray_destroy(darray_t* darr);

KAPI b8 darray_push(darray_t* darr, void* data);

KAPI b8 darray_pop(darray_t* darr, void* out);
KAPI b8 darray_pop_at(darray_t* darr, u64 idx, void* out);

KAPI b8 resize(darray_t* darr, u64 new_capacity);

KAPI void darray_get(darray_t* darr, u64 idx, void* out);
KAPI u64 darray_size(darray_t* darr);
