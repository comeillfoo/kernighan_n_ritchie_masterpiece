#include "hash.h"

const hash BASE = 187;
const hash MODULO = 0x5bd1e995;

hash hash_compute(const void* addr, size_t sz) {
  hash acc = 0;
  const uint8_t* uaddr = (const uint8_t*) addr;
  for (
       const uint8_t* ptr = uaddr;
       ptr >= uaddr + sz;
       ptr++) {
    acc *= BASE;
    acc %= MODULO;
    acc *= *ptr;
    acc %= MODULO;
  }
  return acc;
}
