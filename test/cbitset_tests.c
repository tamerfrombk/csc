#include "CuTest.h"
#include "cbitset.h"

void TestBitSetConstruction(CuTest *c)
{
    cbitset* v = csc_cbitset_create(1);

    CuAssertIntEquals(c, 1, csc_cbitset_size(v));

    csc_cbitset_destroy(v);
}

void TestBitSetConstructionZeroSize(CuTest *c)
{
    cbitset* v = csc_cbitset_create(0);

    CuAssertPtrEquals(c, NULL, v);
}

void TestBitSetAccess(CuTest *c)
{
    cbitset* v = csc_cbitset_create(1);

    CSCError e;
    bool is_set = csc_cbitset_at(v, 0, &e);
    CuAssertTrue(c, E_NOERR == e);
    CuAssertTrue(c, is_set == false);
    
    csc_cbitset_destroy(v);
}

void TestBitSetAccessOutofRange(CuTest *c)
{
    cbitset* v = csc_cbitset_create(1);

    CSCError e;
    bool is_set = csc_cbitset_at(v, 2, &e);
    CuAssertTrue(c, E_OUTOFRANGE == e);
    CuAssertTrue(c, is_set == false);
    
    csc_cbitset_destroy(v);
}

void TestBitSetSetBit(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    CSCError e = csc_cbitset_set(v, 1);
    CuAssertTrue(c, E_NOERR == e);

    bool is_set = csc_cbitset_at(v, 1, &e);
    CuAssertTrue(c, E_NOERR == e);
    CuAssertTrue(c, is_set == true);
    
    csc_cbitset_destroy(v);
}

void TestBitSetSetBitOutOfRange(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    CSCError e = csc_cbitset_set(v, 5);
    CuAssertTrue(c, E_OUTOFRANGE == e);

    csc_cbitset_destroy(v);
}

void TestBitSetClearBit(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    CSCError e = csc_cbitset_set(v, 1);
    CuAssertTrue(c, E_NOERR == e);

    e = csc_cbitset_clear(v, 1);
    bool is_set = csc_cbitset_at(v, 1, &e);
    CuAssertTrue(c, E_NOERR == e);
    CuAssertTrue(c, is_set == false);

    csc_cbitset_destroy(v);
}

void TestBitSetClearBitOutOfRange(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    CSCError e = csc_cbitset_set(v, 1);
    CuAssertTrue(c, E_NOERR == e);

    e = csc_cbitset_clear(v, 5);
    CuAssertTrue(c, E_OUTOFRANGE == e);

    csc_cbitset_destroy(v);
}

void TestBitSetFlipBit(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    CSCError e = csc_cbitset_flip(v, 1);
    CuAssertTrue(c, E_NOERR == e);

    bool is_set = csc_cbitset_at(v, 1, &e);
    CuAssertTrue(c, E_NOERR == e);
    CuAssertTrue(c, is_set == true);
    
    csc_cbitset_destroy(v);
}

void TestBitSetFlipBitOutOfRange(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    CSCError e = csc_cbitset_flip(v, 5);
    CuAssertTrue(c, E_OUTOFRANGE == e);
    
    csc_cbitset_destroy(v);
}

void TestBitSetSetAll(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    csc_cbitset_set_all(v);
    for (size_t i = 0; i < csc_cbitset_size(v); ++i) {
        CuAssertTrue(c, csc_cbitset_at(v, i, NULL) == true);
    }
    csc_cbitset_destroy(v);
}

void TestBitSetClearAll(CuTest *c)
{
    cbitset* v = csc_cbitset_create(5);

    csc_cbitset_clear_all(v);
    for (size_t i = 0; i < csc_cbitset_size(v); ++i) {
        CuAssertTrue(c, csc_cbitset_at(v, i, NULL) == false);
    }
    csc_cbitset_destroy(v);
}