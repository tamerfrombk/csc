#include "cbitset.h"
#include <assert.h>
#include <string.h>

#ifdef CSC_64
    typedef uint_fast64_t bitset_type;
#else
    typedef uint_fast32_t bitset_type;
#endif

#define CSC_BITSIZE ((sizeof(bitset_type)) * (8))

struct cbitset {
    bitset_type* data;
    size_t nbits;
    size_t size;
};

cbitset* csc_cbitset_create(size_t nbits)
{
    // zero sized bitset is not allowed.
    if (nbits == 0) {
        return NULL;
    }

    cbitset* b = calloc(1, sizeof(*b));
    if (b == NULL) {
        return NULL;
    }

    // find the number of elements needed to store the number of bits.
    int n_elems = 0;
    if ((nbits % CSC_BITSIZE) == 0) {
        n_elems = nbits / CSC_BITSIZE;
    } else {
        n_elems = (nbits / CSC_BITSIZE) + 1;
    }

    b->data = calloc(n_elems, sizeof(bitset_type));
    if (b->data == NULL) {
        free(b);
        return NULL;
    }
    b->nbits = nbits;
    b->size = n_elems;

    return b;
}

void csc_cbitset_destroy(cbitset* b)
{
    assert(b != NULL);
    free(b->data);
    free(b);
}

size_t csc_cbitset_size(const cbitset* b)
{
    assert(b != NULL);
    return b->nbits;
}

CSCError csc_cbitset_set(cbitset* b, size_t bit)
{
    assert(b != NULL);
    if (bit >= b->nbits) {
        return E_OUTOFRANGE;
    }
    
    bitset_type* elem = &(b->data[bit / CSC_BITSIZE]);
    const bitset_type shift = bit % CSC_BITSIZE;
    *elem |= 1 << shift;

    return E_NOERR;
}

CSCError csc_cbitset_clear(cbitset* b, size_t bit)
{
    assert(b != NULL);
    if (bit >= b->nbits) {
        return E_OUTOFRANGE;
    }

    bitset_type* elem = &(b->data[bit / CSC_BITSIZE]);
    const bitset_type shift = bit % CSC_BITSIZE;
    *elem &= ~(1 << shift);

    return E_NOERR;
}

CSCError csc_cbitset_flip(cbitset* b, size_t bit)
{
    assert(b != NULL);
    if (bit >= b->nbits) {
        return E_OUTOFRANGE;
    }

    bitset_type* elem = &(b->data[bit / CSC_BITSIZE]);
    const bitset_type shift = bit % CSC_BITSIZE;
    *elem ^= (1 << shift);

    return E_NOERR;
}

bool csc_cbitset_at(const cbitset* b, size_t bit, CSCError* e)
{
    assert(b != NULL);
    if (bit >= b->nbits) {
        if (e != NULL) {
            *e = E_OUTOFRANGE;
        }
        return false;
    }

    // bit 0 to 63 = elem 0
    // bit 64 to 127 = elem 1
    const bitset_type elem = b->data[bit / CSC_BITSIZE];
    const bitset_type shift = bit % CSC_BITSIZE;
    return (elem & (1 << shift)) != 0;
}

void csc_cbitset_set_all(cbitset* b)
{
    assert(b != NULL);
    memset(b->data, ~0, b->size);
}

void csc_cbitset_clear_all(cbitset* b)
{
    assert(b != NULL);
    memset(b->data, 0, b->size);
}