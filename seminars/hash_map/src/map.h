#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "list.h"

typedef const char* key;
typedef const char* value;

typedef void (kvp_action)(struct entry);

/*
 * Programmer doesn't have 
 * any rights to name your own types
 * with suffix "_t" because of 
 * they're reserved by C standard
 */

#define MAP_SIZE 65537

struct map {
  struct list** buckets;
};

/*
 * less pointers - better programming
 */

struct map map_create(void);
void map_destroy(struct map);

void map_add(struct map, key, value);
void map_foreach_kvp(struct map, kvp_action);


const value map_get(struct map, const key);

#endif
