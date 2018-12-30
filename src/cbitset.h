#pragma once

#include "csc.h"

typedef struct cbitset cbitset;

cbitset* csc_cbitset_create(size_t nbits);

void csc_cbitset_destroy(cbitset* b);

size_t csc_cbitset_size(const cbitset* b);

CSCError csc_cbitset_set(cbitset* b, size_t bit);

CSCError csc_cbitset_clear(cbitset* b, size_t bit);

CSCError csc_cbitset_flip(cbitset* b, size_t bit);

bool csc_cbitset_at(const cbitset* b, size_t bit, CSCError* e);

void csc_cbitset_set_all(cbitset* b);

void csc_cbitset_clear_all(cbitset* b);