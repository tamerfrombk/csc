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

static void _csc_free_elem(void* e, void* context) 
{
    CSC_UNUSED(context);
    free(e);
}

void csc_cvector_destroy(cvector* v)
{
    assert(v != NULL);
    csc_cvector_foreach(v, _csc_free_elem);
    free(v);
}

void csc_cvector_foreach(cvector* v, cvector_foreach fn)
{
    assert(v != NULL);
    if (v->data == NULL) {
        return;
    }

    for (size_t i = 0; i < v->size; ++i) {
        fn(v->data[i], NULL);
    }
}