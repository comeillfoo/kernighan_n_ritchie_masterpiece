#include "common.h"

void print_int64(int64_t i) {
  printf("%" PRId64, i);
}

/**
 *
 * Function that doesn't get any arguments
 * must include "void" keyword because of
 * considering empty brackets as vararg
 *
 */
void print_newline(void) {
  printf("\n");
}
