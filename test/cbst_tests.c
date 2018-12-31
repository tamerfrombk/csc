#include "CuTest.h"
#include "cbst.h"

void TestBSTCreate(CuTest *c)
{
    cbst* b = csc_cbst_create();

    CuAssertTrue(c, 1 == 1);
    
    csc_cbst_destroy(b);
}