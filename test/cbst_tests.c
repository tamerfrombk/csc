#include "CuTest.h"
#include "cbst.h"

void TestBSTCreate(CuTest *c)
{
    cbst* b = csc_cbst_create();

    CuAssertIntEquals(c, 0, csc_cbst_size(b));
    CuAssertTrue(c, csc_cbst_empty(b));
    
    csc_cbst_destroy(b);
}

void TestBSTAdd(CuTest *c)
{
    cbst* b = csc_cbst_create();

    int x = 1;
    CSCError e = csc_cbst_add(b, &x, csc_cmp_int);

    CuAssertTrue(c, e == E_NOERR);
    CuAssertIntEquals(c, 1, csc_cbst_size(b));
    CuAssertTrue(c, csc_cbst_empty(b) == false);
    
    csc_cbst_destroy(b);
}

void TestBSTAddSameElement(CuTest *c)
{
    cbst* b = csc_cbst_create();

    int x = 1;
    CSCError e = csc_cbst_add(b, &x, csc_cmp_int);
    e = csc_cbst_add(b, &x, csc_cmp_int);

    CuAssertTrue(c, e == E_INVALIDOPERATION);
    CuAssertIntEquals(c, 1, csc_cbst_size(b));
    CuAssertTrue(c, csc_cbst_empty(b) == false);
    
    csc_cbst_destroy(b);
}

void TestBSTFindElement(CuTest *c)
{
    cbst* b = csc_cbst_create();

    int x = 1;
    csc_cbst_add(b, &x, csc_cmp_int);
    
    CuAssertPtrEquals(c, &x, csc_cbst_find(b, &x, csc_cmp_int));

    csc_cbst_destroy(b);
}

void TestBSTFindElementThatDoesNotExist(CuTest *c)
{
    cbst* b = csc_cbst_create();

    int x = 1;
    csc_cbst_add(b, &x, csc_cmp_int);
    
    int y = 2;
    CuAssertPtrEquals(c, NULL, csc_cbst_find(b, &y, csc_cmp_int));

    csc_cbst_destroy(b);
}

void TestBSTFindElementOnEmptyContainer(CuTest *c)
{
    cbst* b = csc_cbst_create();

    int y = 2;
    CuAssertPtrEquals(c, NULL, csc_cbst_find(b, &y, csc_cmp_int));

    csc_cbst_destroy(b);
}

typedef struct _test {
    int* elems;
    int idx;
} _test;

static void _cbst_foreach(void* elem, void* context)
{
    _test* t = (_test*)context;
    t->elems[t->idx] = *(int*)elem;
    ++t->idx;
}

void TestBSTForEach(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int input[] = {2, 1, 3};
    for (unsigned i = 0; i < sizeof(input) / sizeof(int); i++) {
        csc_cbst_add(b, &input[i], csc_cmp_int);
    }

    int output[3];
    _test t = {.elems = output, .idx = 0 };
    csc_cbst_foreach(b, _cbst_foreach, &t);

    CuAssertIntEquals(c, 1, output[0]);
    CuAssertIntEquals(c, 2, output[1]);
    CuAssertIntEquals(c, 3, output[2]);

    csc_cbst_destroy(b);
}

void TestBSTForEachInOrder(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int input[] = {1, 2, 3};
    for (unsigned i = 0; i < sizeof(input) / sizeof(int); i++) {
        csc_cbst_add(b, &input[i], csc_cmp_int);
    }

    int output[3];
    _test t = {.elems = output, .idx = 0 };
    csc_cbst_foreach(b, _cbst_foreach, &t);

    CuAssertIntEquals(c, 1, output[0]);
    CuAssertIntEquals(c, 2, output[1]);
    CuAssertIntEquals(c, 3, output[2]);

    csc_cbst_destroy(b);
}

void TestBSTForEachReverseOrder(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int input[] = {3, 2, 1};
    for (unsigned i = 0; i < sizeof(input) / sizeof(int); i++) {
        csc_cbst_add(b, &input[i], csc_cmp_int);
    }

    int output[3];
    _test t = {.elems = output, .idx = 0 };
    csc_cbst_foreach(b, _cbst_foreach, &t);

    CuAssertIntEquals(c, 1, output[0]);
    CuAssertIntEquals(c, 2, output[1]);
    CuAssertIntEquals(c, 3, output[2]);

    csc_cbst_destroy(b);
}

void TestBSTRemoveNodeEmptyTree(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int i = 1;
    void* ret = csc_cbst_rm(b, &i, csc_cmp_int);
    
    CuAssertIntEquals(c, 0, csc_cbst_size(b));
    CuAssertPtrEquals(c, NULL, ret);

    TestBSTForEach(c);
}

void TestBSTRemoveNodeNoChildren(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int i = 1;
    csc_cbst_add(b, &i, csc_cmp_int);
    void* ret = csc_cbst_rm(b, &i, csc_cmp_int);
    
    CuAssertIntEquals(c, 0, csc_cbst_size(b));
    CuAssertPtrEquals(c, &i, ret);

    TestBSTForEach(c);
}

void TestBSTRemoveNodeOnlyLeftChild(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int i = 3;
    csc_cbst_add(b, &i, csc_cmp_int);

    int j = 1;
    csc_cbst_add(b, &j, csc_cmp_int);

    void* ret = csc_cbst_rm(b, &i, csc_cmp_int);
    
    CuAssertIntEquals(c, 1, csc_cbst_size(b));
    CuAssertPtrEquals(c, &i, ret);

    TestBSTForEach(c);
}

void TestBSTRemoveNodeOnlyRightChild(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int i = 3;
    csc_cbst_add(b, &i, csc_cmp_int);

    int j = 4;
    csc_cbst_add(b, &j, csc_cmp_int);

    void* ret = csc_cbst_rm(b, &i, csc_cmp_int);
    
    CuAssertIntEquals(c, 1, csc_cbst_size(b));
    CuAssertPtrEquals(c, &i, ret);

    TestBSTForEach(c);
}

void TestBSTRemoveNodeWithTwoChildren(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int i = 3;
    csc_cbst_add(b, &i, csc_cmp_int);

    int j = 4;
    csc_cbst_add(b, &j, csc_cmp_int);

    int k = 2;
    csc_cbst_add(b, &k, csc_cmp_int);

    void* ret = csc_cbst_rm(b, &i, csc_cmp_int);
    
    CuAssertIntEquals(c, 2, csc_cbst_size(b));
    CuAssertPtrEquals(c, &i, ret);

    TestBSTForEach(c);
}

void TestBSTRemoveLeafNode(CuTest* c)
{
    cbst* b = csc_cbst_create();

    int i = 3;
    csc_cbst_add(b, &i, csc_cmp_int);

    int j = 4;
    csc_cbst_add(b, &j, csc_cmp_int);

    void* ret = csc_cbst_rm(b, &j, csc_cmp_int);
    
    CuAssertIntEquals(c, 1, csc_cbst_size(b));
    CuAssertPtrEquals(c, &j, ret);

    TestBSTForEach(c);
}

void TestBSTRemoveNull(CuTest* c)
{
    cbst* b = csc_cbst_create();

    void* ret = csc_cbst_rm(b, NULL, csc_cmp_int);
    
    CuAssertIntEquals(c, 0, csc_cbst_size(b));
    CuAssertPtrEquals(c, NULL, ret);

    TestBSTForEach(c);
}