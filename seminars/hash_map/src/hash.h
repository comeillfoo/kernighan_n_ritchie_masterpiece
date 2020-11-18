#ifndef HASH_H
#define HASH_H

#include "common.h"

typedef uint64_t hash;

hash hash_compute(const void* addr, size_t sz);


#endif

