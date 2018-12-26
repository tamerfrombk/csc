#pragma once

#include "csc.h"

typedef struct cvector cvector;

typedef void (*cvector_foreach)(void*, void*);

cvector* csc_cvector_create();

void csc_cvector_destroy(cvector* v);

CSCError csc_cvector_add(cvector* v, void* elem);

void csc_cvector_rm(cvector* v, const void* elem, csc_compare cmp);

CSCError csc_cvector_rm_at(cvector* v, size_t idx);

void* csc_cvector_find(const cvector* v, const void* elem, csc_compare comp);

size_t csc_cvector_size(const cvector* v);

size_t csc_cvector_capacity(const cvector* v);

void csc_cvector_foreach(cvector* v, cvector_foreach fn, void* context);

void* csc_cvector_at(const cvector* v, size_t idx);

bool csc_cvector_empty(const cvector* v);

