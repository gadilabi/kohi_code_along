// includes
#include "darray.h"

#include "defines.h"
#include "kmemory.h"
#include "assert.h"

// defines
#define KALLOCATE(num_bytes) (memory_allocate(num_bytes, MEMORY_TAG_DARRAY))
#define KFREE(block, size) (memory_free(block, size, MEMORY_TAG_DARRAY))
#define MIN(a, b) ((a > b) ? b : a)

#define RESIZE_FACTOR 2

// structs
typedef struct dynamic_array
{
	void* container;
	u64 capacity;
	u64 size;
	u64 elem_size;
} darray_t;

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
		if (!resize(darr, darr->capacity * RESIZE_FACTOR))
		{
			return false;
		}
	}

	memory_copy(darr + darr->size, data, darr->elem_size);

	++(darr->size);

	return true;
}

KAPI b8 darray_pop(darray_t* darr, void* out)
{
	KASSERT(darr != NULL);
	KASSERT(out != NULL);

	if (darr->size == 0)
	{
		return false;
	}

	memory_copy(out, darr + darr->size, darr->elem_size);
	--darr->size;

	return true;
}

KAPI b8 darray_pop_at(darray_t* darr, u64 idx, void* out)
{
	KASSERT(darr != NULL);
	KASSERT(idx >= 0);

	if (darr->size == 0)
	{
		return false;
	}

	if (out != NULL)
	{
		void* src = (char*)darr->container + idx * darr->elem_size;
		memory_copy(out, src, darr->elem_size);
	}

	if (idx == darr->size - 1)
	{
		return true;
	}

	for (u64 i = idx + 1; i < darr->size; ++i)
	{
		void* src = (char*)darr->container + idx * darr->elem_size;
		memory_copy(darr + i - 1, (char*)darr->container + i, darr->elem_size);
	}

	--darr->size;

	return true;
}

KAPI void darray_destroy(darray_t* darr)
{
	free(darr->container);
	free(darr);
}

// static function definitions
KAPI b8 resize(darray_t* darr, u64 new_capacity)
{
	KASSERT(darr);

	void* buffer = KALLOCATE(new_capacity * darr->elem_size);

	if (!buffer)
	{
		return false;
	}

	darr->size = MIN(new_capacity, darr->size);
	u64 size_in_bytes = darr->size * darr->elem_size;

	memory_copy(buffer, darr->container, size_in_bytes);

	KFREE(darr->container, darr->capacity * darr->elem_size);

	darr->container = buffer;

	return true;
}

KAPI void darray_get(darray_t* darr, u64 idx, void* out)
{
	KASSERT(darr != NULL);
	KASSERT(out != NULL);
	KASSERT(idx >= 0);
	KASSERT(idx < darr->size);

	void* src = (char*)darr->container + idx * darr->elem_size;
	memory_copy(out, src, darr->elem_size);
}
