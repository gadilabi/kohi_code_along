#pragma once

#include <cstdint>

#include "defines.h"

#define KASSERTIONS_ENABLE

#ifdef KASSERTIONS_ENABLE
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

KAPI void report_assertion_failure(const char* expression, const char* msg, const char* file, uint32_t line);

#define KASSERT_MSG(exp, msg)                                         \
{                                                            \
	if (exp)                                                 \
	{                                                        \
	}                                                        \
	else                                                     \
	{                                                        \
		report_assertion_failure(#exp, msg, __FILE__, __LINE__); \
		debugBreak();                                          \
	}                                                          \
}

#define KASSERT(exp) KASSERT_MSG(exp, "") 


#ifdef _DEBUG
#define KASSERT_DEBUG(exp, msg)                                         \
{                                                            \
	if (exp)                                                 \
	{                                                        \
	}                                                        \
	else                                                     \
	{                                                        \
		report_assertion_failure(#exp, msg, __FILE__, __LINE__); \
		debugBreak();                                          \
	}                                                          \
}
#else
#define KASSERT_DEBUG(exp, msg)
#endif

#else
#define KASSERT(exp)
#define KASSERT_MSG(exp)
#define KASSERT_DEBUG(exp)

#endif
