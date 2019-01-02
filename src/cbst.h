#pragma once

#include "csc.h"

typedef struct cbst cbst;

cbst* csc_cbst_create();

void csc_cbst_destroy(cbst* b);

CSCError csc_cbst_add(cbst* b, void* elem, csc_compare cmp);

void* csc_cbst_rm(cbst* b, const void* elem, csc_compare cmp);

void* csc_cbst_find(const cbst* b, const void* elem, csc_compare cmp);

size_t csc_cbst_size(const cbst* b);

bool csc_cbst_empty(const cbst* b);

void csc_cbst_foreach(cbst* b, csc_foreach fn, void* context);