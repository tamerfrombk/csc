#include "CuTest.h"
#include "cvector.h"

void TestVectorInitNullAlloc(CuTest *c)
{
    cvector* v = csc_cvector_create();

    CuAssertTrue(c, 0 == csc_cvector_size(v));
    CuAssertTrue(c, 0 == csc_cvector_capacity(v));

    csc_cvector_destroy(v);
}

void TestVectorAddElem(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int *i = malloc(sizeof(*i));
    
    CSCError e = csc_cvector_add(v, i);
    
    CuAssertTrue(c, e == E_NOERR);
    CuAssertTrue(c, 1 == csc_cvector_size(v));

    csc_cvector_destroy(v);
}

static void _for_each_fxn(void* elem, void* context)
{
    CSC_UNUSED(elem);
    int* i = (int*)context;
    ++*i;
}

void TestVectorForEach(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int *i = malloc(sizeof(*i));
    
    csc_cvector_add(v, i);
    
    int counter = 0;
    csc_cvector_foreach(v, _for_each_fxn, &counter);

    CuAssertTrue(c, counter == 1);

    csc_cvector_destroy(v);
}