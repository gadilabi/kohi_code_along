#pragma once

#include "defines.h"

typedef enum memory_tag
{
	MEMORY_TAG_UNKNOWN,
	MEMORY_TAG_ARRAY,
	MEMORY_TAG_DARRAY,
	MEMORY_TAG_DICT,
	MEMORY_TAG_RING_QUEUE,
	MEMORY_TAG_BST,
	MEMORY_TAG_STRING,
	MEMORY_TAG_APPLICATION,
	MEMORY_TAG_JOB,
	MEMORY_TAG_TEXTURE,
	MEMORY_TAG_MATERICAL_INSTANCE,
	MEMORY_TAG_RENDERER,
	MEMORY_TAG_GAME,
	MEMORY_TAG_TRANSFORM,
	MEMORY_TAG_ENTITY,
	MEMORY_TAG_ENTITY_NODE,
	MEMORY_TAG_SCENE,

	MEMORY_TAG_NUM_TAGS


} memory_tag_t;

void memory_initialize();
void memory_shutdown();

KAPI void* memory_allocate(u64 size, memory_tag_t tag);
KAPI void memory_free(void* block, u64 size, memory_tag_t tag);
KAPI void* memory_zero(void* block, u64 size);
KAPI void* memory_copy(void* dst, void* src, u64 num_bytes);
KAPI void* memory_set(void* dst, char val, u64 num_bytes);
KAPI char* memory_get_usage_str();

