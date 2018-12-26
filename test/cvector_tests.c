#include "CuTest.h"
#include "cvector.h"

void TestVectorInitNullAlloc(CuTest *c)
{
    cvector* v = csc_cvector_create(NULL);

    CuAssertTrue(c, 0 == csc_cvector_size(v));
    CuAssertTrue(c, 0 == csc_cvector_capacity(v));

    csc_cvector_destroy(v);
}