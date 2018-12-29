#include "cbitset.h"

struct cbitset {
    int foo;
};

cbitset* csc_cbitset_create()
{
    return calloc(1, sizeof(cbitset));
}

void csc_cbitset_destroy(cbitset* b)
{
    free(b);
}