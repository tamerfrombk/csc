#include "cvector.h"

typedef struct CVector {
    void** data;
    size_t size, capacity;
} CVector;