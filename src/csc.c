/**
 * @file csc.c
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief the implementation file for csc.h.
 *
 * @see csc.h
 */

#include "csc.h"

/**
 * @brief implements a builtin type comparison function
 * 
 * When defined with a type, this macro will implement the function signature
 * that the @c CSC_DECLARE_BUILTIN_CMP defines. Note that the function signature
 * @b must be declared first using @c CSC_DECLARE_BUILTIN_CMP in the header file.
 * 
 * @see csc.h
 */ 
#define CSC_DEFINE_BUILTIN_CMP(type) \
int csc_cmp_##type(const void* a, const void* b) \
{\
    type vA = *(type*)a;\
    type vB = *(type*)b;\
    if (vA == vB) { return 0; }\
    else if (vA < vB) { return -1; }\
    else { return 1; }\
}

CSC_DEFINE_BUILTIN_CMP(int)

void csc_swap(void** a, void** b)
{
    void* c = *a;
    *a = *b;
    *b = c;
}