#include "csc.h"

#define CSC_DEFINE_BUILTIN_CMP(type) \
bool csc_cmp_##type(const void* a, const void* b) \
{\
    return (*(type*)a) == (*(type*)b);\
}

CSC_DEFINE_BUILTIN_CMP(int)

void csc_swap(void** a, void** b)
{
    void* c = *a;
    *a = *b;
    *b = c;
}