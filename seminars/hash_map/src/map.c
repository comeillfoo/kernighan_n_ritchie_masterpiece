#include "map.h"
#include <string.h>
#include "hash.h"

struct map map_create(void) {
  return (struct map) { 
    .buckets = calloc(MAP_SIZE, sizeof(struct list*))
  };
}

void map_destroy(struct map m) {
  free(m.buckets);
}

static struct list** map_find_list(struct map m, key k) {
  const size_t sz = strlen(k);
  const hash h = hash_compute(k, sz);
  return m.buckets + h % MAP_SIZE;
}


void map_add(struct map m, key k, value v) {
  struct list** l = map_find_list(m, k);
  /* struct list* [] */
  list_add_back(l, (struct entry) { .key = k, .value = v});
}

void map_foreach_kvp(
                struct map m,
                kvp_action action) {
  for (size_t i = 0; i < MAP_SIZE; ++i) {
    if (m.buckets[i])
      list_foreach(m.buckets[i], action);
  }
}

const value map_get(struct map m, const key k) {
  struct list** l = map_find_list(m, k);
  struct entry const* e = list_find_key(*l, k);
  return e->value;
}
