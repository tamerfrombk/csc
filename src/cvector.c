/**
 * @file cvector.c
 * @author Tamer Aly
 * @date 27 Dec 2018
 * @brief contains the implementation of the cvector structure.
 *
 */

#include "cvector.h"
#include <assert.h>

struct cvector {
    void** data; /**< The internal data store of the vector. */
    size_t size; /**< The number of elements currently in the vector. */
    size_t capacity; /**< The number of elements the vector is capable of storing before needing to resize. */
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

void csc_cvector_destroy(cvector* v)
{
    assert(v != NULL);
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
        if (cmp(v->data[i], elem) == 0) {
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