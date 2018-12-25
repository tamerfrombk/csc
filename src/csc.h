#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum CGCError {
    E_NOERR = 0,
    E_ERR_N // This is __always__ the last error. Add errors before here.
} CGCError;