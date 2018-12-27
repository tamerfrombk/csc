#include "cvector.h"
#include <assert.h>

struct cvector {
    void** data;
    size_t size, capacity;
};

cvector* csc_cvector_create()
{
    return calloc(1, sizeof(cvector));
}

size_t csc_cvector_size(const cvector* v)
{
    assert(v != NULL);
    return v->size;
}

size_t csc_cvector_capacity(const cvector* v)
{
    assert(v != NULL);
    return v->capacity;
}

static void _csc_free_elem(void* elem, void* context)
{
    CSC_UNUSED(context);
    assert(elem != NULL);
    free(elem);
}

void csc_cvector_destroy(cvector* v)
{
    assert(v != NULL);
    csc_cvector_foreach(v, _csc_free_elem, NULL);
    free(v);
}

void csc_cvector_foreach(cvector* v, cvector_foreach fn, void* context)
{
    assert(v != NULL);
    if (v->data == NULL) {
        return;
    }

    for (size_t i = 0; i < v->size; ++i) {
        fn(v->data[i], context);
    }
}

CSCError csc_cvector_add(cvector* v, void* elem)
{
    assert(v != NULL);
    if (v->size >= v->capacity) {
        const size_t new_capacity = v->capacity == 0 ? 10 : v->capacity * 1.5;
        CSCError e = csc_cvector_reserve(v, new_capacity);
        if (e != E_NOERR) {
            return e;
        }
    }
    v->data[v->size] = elem;
    ++v->size;

    return E_NOERR;
}

void* csc_cvector_at(const cvector* v, size_t idx)
{
    assert(v != NULL);
    if (idx < v->size) {
        return v->data[idx];
    }
    return NULL;
}

void csc_cvector_rm(cvector* v, const void* elem, csc_compare cmp)
{
    assert(v != NULL);
    void* ret = csc_cvector_find(v, elem, cmp);
    if (ret == NULL) {
        return; // if the vector is empty or the element isn't there.
    }

    if (v->size > 1) {
        csc_swap(&ret, &(v->data[v->size - 1]));
    }
    --v->size;
}

CSCError csc_cvector_rm_at(cvector* v, size_t idx)
{
    assert(v != NULL);

    void* ret = csc_cvector_at(v, idx);
    if (ret == NULL) {
        return E_OUTOFRANGE;
    }

    if (v->size > 1) {
        csc_swap(&ret, &(v->data[v->size - 1]));
    }
    --v->size;
    
    return E_NOERR;
}

void* csc_cvector_find(const cvector* v, const void* elem, csc_compare cmp)
{
    assert(v != NULL);

    for (size_t i = 0; i < v->size; ++i) {
        if (cmp(v->data[i], elem)) {
            return v->data[i];
        }
    }
    return NULL;
}

bool csc_cvector_empty(const cvector* v)
{
    assert(v != NULL);
    return v->size == 0;
}

CSCError csc_cvector_reserve(cvector* v, size_t num_elems)
{
    assert(v != NULL);
    if (num_elems < v->size) {
        return E_INVALIDOPERATION; // no information loss allowed
    }

    void** data = realloc(v->data, num_elems * sizeof(*(v->data)));
    if (data == NULL) {
        return E_OUTOFMEM;
    }

    v->data = data;
    v->capacity = num_elems;

    return E_NOERR;
}

CSCError csc_cvector_shrink_to_fit(cvector* v)
{
    assert(v != NULL);
    return csc_cvector_reserve(v, v->size);
}