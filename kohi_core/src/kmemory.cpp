#include "kmemory.h"

#include "logger.h"
#include "platform.h"

// TODO: make our own string lib
#include <string.h>
#include <stdio.h>

#define MEMORY_STR_BUFFER_SIZE 8000

f32 set_unit(char unit[], u64 num_bytes);

static const char* tags_str_rep[]
{
	"UNKNOWN           ",
	"ARRAY             ",
	"DARRAY            ",
	"DICT              ",
	"RING_QUEUE        ",
	"BST               ",
	"STRING            ",
	"APPLICATION       ",
	"JOB               ",
	"TEXTURE           ",
	"MATERICAL_INSTANCE",
	"RENDERER          ",
	"GAME              ",
	"TRANSFORM         ",
	"ENTITY            ",
	"ENTITY_NODE       ",
	"SCENE             "
};

typedef struct memory_stats
{
	u64 total_allocated;
	u64 tagged_allocations[MEMORY_TAG_NUM_TAGS];
} memory_stats_t;

static struct memory_stats stats;

void memory_initialize()
{
	platform_zero_memory(&stats, sizeof(stats));
}

void memory_shutdown()
{
}

void* memory_allocate(u64 size, memory_tag_t tag)
{
	if (tag == MEMORY_TAG_UNKNOWN)
	{
		KWARN("memory_allocate called with a MEMORY_TAG_UNKNOWN tag, reclass the allocation");
	}

	stats.total_allocated += size;
	stats.tagged_allocations[tag] += size;

	// TODO: revisit memory alignment
	void* block = platform_allocate(size, false);
	platform_zero_memory(block, size);

	return block;
}

KAPI void memory_free(void* block, u64 size, memory_tag_t tag)
{
	stats.total_allocated -= size;
	stats.tagged_allocations[tag] -= size;
}

KAPI void* memory_zero(void* block, u64 size)
{
	return platform_zero_memory(block, size);
}

KAPI void* memory_copy(void* dst, void* src, u64 num_bytes)
{
	return platform_copy_memory(dst, src, num_bytes);
}

KAPI void* memory_set(void* dst, char val, u64 num_bytes)
{
	return platform_set_memory(dst, val, num_bytes);
}

KAPI char* memory_get_usage_str()
{
	char* str = (char *)platform_allocate(MEMORY_STR_BUFFER_SIZE, false);
	i32 offset = snprintf(str, MEMORY_STR_BUFFER_SIZE, "system memory use tagged:\n");

	for (u32 i = 0; i < MEMORY_TAG_NUM_TAGS; ++i)
	{
		i32 num_bytes = stats.tagged_allocations[i];
		char unit[4] = {};
		f32 amount = set_unit(unit, num_bytes);
		offset += snprintf(str + offset, MEMORY_STR_BUFFER_SIZE - offset, "%s: %.2f%s\n", tags_str_rep[i], amount, unit);
	}

	return str;
}

f32 set_unit(char unit[], u64 num_bytes)
{
	const u64 kb = 1024;
	const u64 mb = 1024 * kb;
	const u64 gb = 1024 * mb;

	f32 amount = (f32)num_bytes;

	if (num_bytes > gb)
	{
		unit[0] = 'g';
		unit[1] = 'b';
		unit[2] = '\0';

		amount /= gb;
	}
	else if (num_bytes > mb)
	{
		unit[0] = 'm';
		unit[1] = 'b';
		unit[2] = '\0';

		amount /= mb;
	}
	else if (num_bytes > kb)
	{
		unit[0] = 'k';
		unit[1] = 'b';
		unit[2] = '\0';

		amount /= kb;
	}
	else
	{
		unit[0] = 'b';
		unit[1] = '\0';
	}

	return amount;
}


