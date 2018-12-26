#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define CSC_UNUSED(x) (void)x

typedef enum CSCError {
    E_NOERR = 0,
    E_OUTOFMEM = 1,
    E_ERR_N // This is __always__ the last error. Add errors before here.
} CSCError;