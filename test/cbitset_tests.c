#include "CuTest.h"
#include "cbitset.h"

void TestBitSet(CuTest *c)
{
    cbitset* v = csc_cbitset_create();

    CuAssertIntEquals(c, 1, 1);

    csc_cbitset_destroy(v);
}