#pragma once

#include "csc.h"

typedef struct cbitset cbitset;

cbitset* csc_cbitset_create();

void csc_cbitset_destroy(cbitset* b);