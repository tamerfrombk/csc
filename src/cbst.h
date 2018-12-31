#pragma once

#include "csc.h"

typedef struct cbst cbst;

cbst* csc_cbst_create();

void csc_cbst_destroy(cbst* c);