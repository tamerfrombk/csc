#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define CSC_UNUSED(x) (void)x

typedef enum CSCError {
    E_NOERR = 0,
    E_OUTOFMEM,
    E_OUTOFRANGE,
    E_ERR_N // This is __always__ the last error. Add errors before here.
} CSCError;

typedef bool (*csc_compare)(const void*, const void*);

#define CSC_DECLARE_BUILTIN_CMP(type) bool csc_cmp_##type(const void* a, const void* b)

CSC_DECLARE_BUILTIN_CMP(int);