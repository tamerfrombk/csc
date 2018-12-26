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
        void** data = realloc(v->data, new_capacity * sizeof(*(v->data)));
        if (data == NULL) {
            return E_OUTOFMEM;
        }
        v->data = data;
        v->capacity = new_capacity;
    }
    v->data[v->size] = elem;
    ++v->size;

    return E_NOERR;
}