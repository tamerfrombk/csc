#include "csc.h"

#define CSC_DEFINE_BUILTIN_CMP(type) \
bool csc_cmp_##type(const void* a, const void* b) \
{\
    return (*(type*)a) == (*(type*)b);\
}

CSC_DEFINE_BUILTIN_CMP(int)