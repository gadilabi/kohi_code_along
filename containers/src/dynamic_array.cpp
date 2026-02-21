// includes
#include "dynamic_array.h"

#include "defines.h"
#include "kmemory.h"
#include "assert.h"

// defines
#define KALLOCATE(num_bytes) (memory_allocate(num_bytes, MEMORY_TAG_DARRAY))
#define KFREE(block, size) (memory_free(block, size, MEMORY_TAG_DARRAY))
#define RESIZE_FACTOR 2

// structs
typedef struct dynamic_array
{
	void* container;
	u64 capacity;
	u64 size;
	u64 elem_size;
} darray_t;

// function declarations 
static b8 resize(darray_t* darr);

// API definitions
KAPI darray_t* darray_create(u64 initial_capacity, u64 elem_size)
{
	darray_t* darray = (darray_t*)KALLOCATE(initial_capacity * sizeof(darray_t));

	if (!darray)
	{
		return NULL;
	}

	darray->capacity = initial_capacity;
	darray->size = 0;
	darray->elem_size = elem_size;

	return darray;
}

KAPI b8 darray_push(darray_t* darr, void* data)
{
	KASSERT(darr != NULL);
	KASSERT(data != NULL);

	if (darr->size == darr->capacity)
	{
		if (!resize(darr))
		{
			return false;
		}
	}

	memory_copy(darr + darr->size, data, darr->elem_size);

	++(darr->size);

	return true;
}

KAPI b8 darray_pop(darray_t* darr)
{
	return KAPI b8();
}

KAPI darray_t* darray_destroy(darray_t* darr)
{
	return nullptr;
}

// static function definitions
static b8 resize(darray_t* darr)
{
	u64 size_in_bytes = darr->size * darr->elem_size;
	void* buffer = KALLOCATE(size_in_bytes * RESIZE_FACTOR);

	if (!buffer)
	{
		return false;
	}

	memory_copy(buffer, darr->container, size_in_bytes);

	KFREE(darr->container, size_in_bytes);

	darr->container = buffer;

	return true;
}

