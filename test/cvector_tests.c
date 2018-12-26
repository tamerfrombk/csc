#include "CuTest.h"
#include "cvector.h"

void TestVectorInitNullAlloc(CuTest *c)
{
    cvector* v = csc_cvector_create();

    CuAssertIntEquals(c, 0, csc_cvector_size(v));
    CuAssertIntEquals(c, 0, csc_cvector_capacity(v));

    csc_cvector_destroy(v);
}

void TestVectorAddElem(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int *i = malloc(sizeof(*i));
    
    CSCError e = csc_cvector_add(v, i);
    
    CuAssertTrue(c, e == E_NOERR);
    CuAssertIntEquals(c, 1, csc_cvector_size(v));

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

    CuAssertIntEquals(c, 1, counter);

    csc_cvector_destroy(v);
}

void TestVectorAt(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int *i = malloc(sizeof(*i));
    *i = 1;

    csc_cvector_add(v, i);
    
    int* ret = csc_cvector_at(v, 0);

    CuAssertIntEquals(c, 1, *ret);

    csc_cvector_destroy(v);
}

void TestVectorFindElementExists(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    csc_cvector_add(v, x);

    CuAssertPtrEquals(c, x, csc_cvector_find(v, x, csc_cmp_int));

    csc_cvector_destroy(v);
}

void TestVectorFindElementDoesNotExist(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    CuAssertPtrEquals(c, NULL, csc_cvector_find(v, x, csc_cmp_int));

    free(x);
    csc_cvector_destroy(v);
}

void TestVectorRmEmpty(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int x = 0;
    csc_cvector_rm(v, &x, csc_cmp_int);

    CuAssertIntEquals(c, 0, csc_cvector_size(v));

    csc_cvector_destroy(v);
}

void TestVectorRmNotEmptyAndExists(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    csc_cvector_add(v, x);

    csc_cvector_rm(v, x, csc_cmp_int);

    CuAssertIntEquals(c, 0, csc_cvector_size(v));
    CuAssertPtrEquals(c, NULL, csc_cvector_find(v, x, csc_cmp_int));

    csc_cvector_destroy(v);
}

void TestVectorRmNotEmptyAndDoesNotExist(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    csc_cvector_add(v, x);

    int *y = malloc(sizeof(*y));
    *y = 2;

    csc_cvector_rm(v, y, csc_cmp_int);

    CuAssertIntEquals(c, 1, csc_cvector_size(v));
    CuAssertPtrEquals(c, NULL, csc_cvector_find(v, y, csc_cmp_int));

    free(y);
    csc_cvector_destroy(v);
}

void TestVectorRmAtEmpty(CuTest *c)
{
    cvector* v = csc_cvector_create();

    CuAssertTrue(c, csc_cvector_rm_at(v, 0) == E_OUTOFRANGE);
    CuAssertIntEquals(c, 0, csc_cvector_size(v));

    csc_cvector_destroy(v);
}

void TestVectorRmAtNotEmptyAndExists(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    csc_cvector_add(v, x);

    CuAssertTrue(c, E_NOERR == csc_cvector_rm_at(v, 0));
    CuAssertIntEquals(c, 0, csc_cvector_size(v));
    CuAssertPtrEquals(c, NULL, csc_cvector_find(v, x, csc_cmp_int));

    csc_cvector_destroy(v);
}

void TestVectorRmAtNotEmptyAndDoesNotExist(CuTest *c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    csc_cvector_add(v, x);

    CuAssertTrue(c, E_OUTOFRANGE == csc_cvector_rm_at(v, 1));
    CuAssertIntEquals(c, 1, csc_cvector_size(v));
    CuAssertPtrEquals(c, x, csc_cvector_find(v, x, csc_cmp_int));

    csc_cvector_destroy(v);
}

void TestVectorEmptyOnEmpty(CuTest* c)
{
    cvector* v = csc_cvector_create();

    CuAssertTrue(c, csc_cvector_empty(v));

    csc_cvector_destroy(v);
}

void TestVectorEmptyOnNonEmpty(CuTest* c)
{
    cvector* v = csc_cvector_create();

    int* x = malloc(sizeof(*x));
    *x = 1;

    csc_cvector_add(v, x);

    CuAssertTrue(c, !csc_cvector_empty(v));

    csc_cvector_destroy(v);
}